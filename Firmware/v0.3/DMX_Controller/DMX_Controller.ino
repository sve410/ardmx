// includes
	//#include <lib_dmx.h>  		// libreria DMX 4 universos deskontrol four universes DMX library  - http://www.deskontrol.net/blog
	#include <LiquidCrystal.h>	// libreria para LCD
	#include <Wire.h>
		
// DMX Library
	//#define    DMX512	    (0)    // (250 kbaud - 2 to 512 channels) Standard USITT DMX-512
	//#define    DMX1024    (1)    // (500 kbaud - 2 to 1024 channels) Completely non standard - TESTED ok
	//#define    DMX2048    (2)    // (1000 kbaud - 2 to 2048 channels) called by manufacturers DMX1000K, DMX 4x or DMX 1M ???

// Simbols
	// DMX
		int DMX_Data_Flux = 38;	// control de flujo de datos para dmx, 0 por default 
	// Botones
		int Boton_Up     = 33; 
		int Boton_Down   = 34;	
		int Boton_Left   = 35;	
		int Boton_Right  = 36;	
		int Boton_Center = 37;	
	// LCD
		int LCD_RS = 30;
		int LCD_E  = 31;
		int LCD_D4 = 26;
		int LCD_D5 = 27;
		int LCD_D6 = 28;
		int LCD_D7 = 29;
		LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);  //LCD setup
		
// Variables y constantes
		// Versiones
			const byte Firm_Ver_Ent = 0;
			const byte Firm_Ver_Dec = 2;
			const byte Hard_Ver_Ent = 0;
			const byte Hard_Ver_Dec = 0;
			const byte ID = 20;
		// LCD
			const long LCD_Init_Pause = 100;	// retardo de muestra de info inicial
			byte LCD_Col_Pos = 0;				// posicion en tiempo real de lcd
			byte LCD_Row_Pos = 0;				// posicion en tiempo real de lcd
			
			int mat[3][3] = {{2, 4, 9},
							 {33, 0, 1},
							 {-4, 55, 7}}; 
 
			byte Cursor_Conf[4][20] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},		// config de posiciones de lcd Col Row
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};		
		// Botones	
			const long Boton_Delay = 500;		// delay de lectura de boton
			
				
void setup() 
	{
		// IO
			// DMX
				pinMode(DMX_Data_Flux, OUTPUT);
			// Botones
				pinMode(Boton_Up,     INPUT_PULLUP);
				pinMode(Boton_Down,   INPUT_PULLUP);
				pinMode(Boton_Left,   INPUT_PULLUP);
				pinMode(Boton_Right,  INPUT_PULLUP);
				pinMode(Boton_Center, INPUT_PULLUP);
			// LCD
				pinMode(LCD_RS, OUTPUT);
				pinMode(LCD_E,  OUTPUT);
				pinMode(LCD_D7, OUTPUT);
				pinMode(LCD_D6, OUTPUT);
				pinMode(LCD_D5, OUTPUT);
				pinMode(LCD_D4, OUTPUT);
				lcd.begin(20, 4);				  //tamaño de LCD
				
				Serial.begin(9600);
				
		// DMX
			//ArduinoDmx0.set_tx_address(1);      // poner aqui la direccion de inicio de DMX 
			//ArduinoDmx0.set_tx_channels(512);   // poner aqui el numero de canales a transmitir 
			//ArduinoDmx0.init_tx(DMX512);        // iniciar transmision universo 0, modo estandar DMX512
	}    

void loop()
	{
		Init_LCD();
		LCD_Matrix();
		delay(5000); 
	}
	
void Init_LCD()
	{
		lcd.setCursor(1, 0);
		lcd.print("Tech Inside.com.mx");
		lcd.setCursor(0, 1);
		lcd.print("DMX-512");
		lcd.setCursor(10, 1);
		lcd.print("Controller");
		// Firmware
			lcd.setCursor(7, 2);
			lcd.print("Firmware v");
			lcd.print(Firm_Ver_Ent);
			lcd.print(".");
			lcd.print(Firm_Ver_Dec);
		// Hardware
			lcd.setCursor(7, 3);
			lcd.print("Hardware v");
			lcd.print(Hard_Ver_Ent);
			lcd.print(".");
			lcd.print(Hard_Ver_Dec);
		// ID
			lcd.setCursor(0, 3);
			lcd.print("ID ");
			lcd.print(ID);
		delay(LCD_Init_Pause);  //retardo de muestra de mensaje
		lcd.clear();			//limpiar LCD
	}
	
void LCD_Matrix()
	{
		lcd.setCursor (1, 0);
		lcd.print("Bac Nex Mem 000-000");
		for (byte Conteo = 1; Conteo < 4; Conteo ++)
			{
				lcd.setCursor (1, Conteo);
				lcd.print("000 000 000 000 000"); 
			}
		// Cursor
			LCD_Col_Pos = 12;		// posicion de cursor
			LCD_Row_Pos = 0;		// posicion e cursor
		// configuracion de cursor	
			Cursor_Conf_Clear();	// limpiar array
			// Row 0
				Cursor_Conf[0][0] = 1;
				Cursor_Conf[0][4] = 1;
				Cursor_Conf[0][8] = 1;
				Cursor_Conf[0][12] = 1;
			// Row 1
				Cursor_Conf[1][0] = 1;
				Cursor_Conf[1][4] = 1;
				Cursor_Conf[1][8] = 1;
				Cursor_Conf[1][12] = 1;
				Cursor_Conf[1][16] = 1;
			// Row 2
				Cursor_Conf[2][0] = 1;
				Cursor_Conf[2][4] = 1;
				Cursor_Conf[2][8] = 1;
				Cursor_Conf[2][12] = 1;
				Cursor_Conf[2][16] = 1;
			// Row 3
				Cursor_Conf[3][0] = 1;
				Cursor_Conf[3][4] = 1;
				Cursor_Conf[3][8] = 1;
				Cursor_Conf[3][12] = 1;
				Cursor_Conf[3][16] = 1;
		// navegar lcd
			LCD_Navegar();
	}
	
void Cursor_Conf_Clear()
	{
		for (byte Conteo_Col = 0; Conteo_Col <= 19; Conteo_Col ++)
			{
				for (byte Conteo_Row = 0; Conteo_Row <= 3; Conteo_Row ++)
					{
						Cursor_Conf[Conteo_Col][Conteo_Row] = 0;
					}
			}
	}
	
void LCD_Navegar()
	{
		byte LCD_Col_Pos_Ant;	// saber el estado anterior para borrar cursor
		byte LCD_Row_Pos_Ant;	// saber el estado anterior para borrar cursor
		
		// guardar valor anterior de row col
			LCD_Col_Pos_Ant = LCD_Col_Pos;
			LCD_Row_Pos_Ant = LCD_Row_Pos;
		// Dibujar cursor
			lcd.setCursor (LCD_Col_Pos, LCD_Row_Pos);
			lcd.print(">"); 
		// navegacion
			Dibujar:
				byte Salida_Navegar = 0;		// salida de lectura de botones
				byte Dibujar_Cursor = 0;		// saber si dibujar cursor para evitar repeticiones en lcd
				
						// Left
							if (digitalRead(Boton_Left) == LOW)
								{
									delay(Boton_Delay);
									byte Salida_Left = 0;
									while (Salida_Left == 0)
										{
											if (LCD_Col_Pos > 0)
												{
													LCD_Col_Pos = LCD_Col_Pos - 1;
												}
											else
												{
													LCD_Col_Pos = 0;
												}
												
											if (Cursor_Conf[LCD_Row_Pos][LCD_Col_Pos] == 1)
												{
													Dibujar_Cursor = 1;
													Salida_Left = 1;
												}
										}
									goto Salida;
								}
						// Right
							if (digitalRead(Boton_Right) == LOW)
								{
									delay(Boton_Delay);
									byte Salida_Right = 0;
									while (Salida_Right == 0)
										{
											if (LCD_Col_Pos < 19)
												{
													LCD_Col_Pos = LCD_Col_Pos + 1;
												}
											else
												{
													LCD_Col_Pos = 19;
												}
												
											if (Cursor_Conf[LCD_Row_Pos][LCD_Col_Pos] == 1)
												{
													Dibujar_Cursor = 1;
													Salida_Right = 1;
												}
										}
									goto Salida;
								}
						// Down
							if (digitalRead(Boton_Down) == LOW)
								{
									delay(Boton_Delay);
									byte Salida_Down = 0;
									while (Salida_Down == 0)
										{
											if (LCD_Row_Pos < 3)
												{
													LCD_Row_Pos = LCD_Row_Pos + 1;
												}
											else
												{
													LCD_Row_Pos = 3;
												}
												
											if (Cursor_Conf[LCD_Row_Pos][LCD_Col_Pos] == 1)
												{
													Dibujar_Cursor = 1;
													Salida_Down = 1;
												}
											
										}
									goto Salida;
								}
						// Up
							if (digitalRead(Boton_Up) == LOW)
								{
									delay(Boton_Delay);
									byte Salida_Up = 0;
									while (Salida_Up == 0)
										{
											if (LCD_Row_Pos > 0)
												{
													LCD_Row_Pos = LCD_Row_Pos - 1;
												}
											else
												{
													LCD_Row_Pos = 0;
												}
												
											if (Cursor_Conf[LCD_Row_Pos][LCD_Col_Pos] == 1)
												{
													Dibujar_Cursor = 1;
													Salida_Up = 1;
												}
											
										}
									goto Salida;
								}
			Salida:
				// Dibujar Cursor
					if (Dibujar_Cursor == 1)
						{
							lcd.setCursor (LCD_Col_Pos_Ant, LCD_Row_Pos_Ant);
							lcd.print(" "); 
							LCD_Col_Pos = LCD_Col_Pos;
							LCD_Row_Pos = LCD_Row_Pos;
							lcd.setCursor (LCD_Col_Pos, LCD_Row_Pos);
							lcd.print(">");
							LCD_Col_Pos_Ant = LCD_Col_Pos;
							LCD_Row_Pos_Ant = LCD_Row_Pos;
							Dibujar_Cursor = 0;
						}
					 
			goto Dibujar;
	}

