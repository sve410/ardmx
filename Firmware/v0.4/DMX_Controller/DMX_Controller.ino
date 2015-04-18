// include
	#include <LiquidCrystal.h>	// libreria para LCD
	#include <Wire.h>
	#include <EEPROM.h>
	#include <string.h>
	#include <lib_dmx.h>  		// libreria DMX 4 universos deskontrol four universes DMX library  - http://www.deskontrol.net/blog
		
// DMX Library
	#define    DMX512	  (0)    // (250 kbaud - 2 to 512 channels) Standard USITT DMX-512
	//#define  DMX1024    (1)    // (500 kbaud - 2 to 1024 channels) Completely non standard - TESTED ok
	//#define  DMX2048    (2)    // (1000 kbaud - 2 to 2048 channels) called by manufacturers DMX1000K, DMX 4x or DMX 1M ???

// Simbols
	// DMX
		int DMX_Data_Flux = 38;		// control de flujo de datos para dmx, 0 por default 
		byte DMX_Values [515];      //array de valores actuales DMX
	// Botones cursor
		int Boton_Up     = 33; 
		int Boton_Down   = 34;	
		int Boton_Left   = 35;	
		int Boton_Right  = 36;	
		int Boton_Center = 37;	
	// Botones Numerico Array
		int Boton_Array_1	= 49;
		int Boton_Array_2	= 48;
		int Boton_Array_3	= 47;
		int Boton_Array_4	= 46;
		int Boton_Array_A	= 50;	
		int Boton_Array_B	= 51;
		int Boton_Array_C   = 52;
		int Boton_Array_D   = 53;
		byte Boton_Calc 	= 17;	// valor calculado	# E * F, 17 sin valor calculado
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
			const byte Firm_Ver_Dec = 4;
			const byte Hard_Ver_Ent = 0;
			const byte Hard_Ver_Dec = 0;
			const byte ID = 20;
		// Navegacion
			byte LCD_Col_Pos = 0;				// posicion en tiempo real de lcd
			byte LCD_Row_Pos = 0;				// posicion en tiempo real de lcd
 
			byte Cursor_Conf[4][20] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},		// config de posiciones de lcd Col Row
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};		
		// Botones	
			const long Boton_Delay = 200;		// delay de lectura de boton
				
void setup() 
	{
		// IO
			// DMX
				pinMode(DMX_Data_Flux, OUTPUT);
			// Botones cursor
				pinMode(Boton_Up,     INPUT_PULLUP);
				pinMode(Boton_Down,   INPUT_PULLUP);
				pinMode(Boton_Left,   INPUT_PULLUP);
				pinMode(Boton_Right,  INPUT_PULLUP);
				pinMode(Boton_Center, INPUT_PULLUP);
			// Botones numerico
				pinMode(Boton_Array_1, OUTPUT);
				pinMode(Boton_Array_2, OUTPUT);
				pinMode(Boton_Array_3, OUTPUT);
				pinMode(Boton_Array_4, OUTPUT);
				pinMode(Boton_Array_A, INPUT_PULLUP);
				pinMode(Boton_Array_B, INPUT_PULLUP);
				pinMode(Boton_Array_C, INPUT_PULLUP);
				pinMode(Boton_Array_D, INPUT_PULLUP);
				digitalWrite(Boton_Array_1, HIGH);
				digitalWrite(Boton_Array_2, HIGH);
				digitalWrite(Boton_Array_3, HIGH);
				digitalWrite(Boton_Array_4, HIGH);
			// LCD
				pinMode(LCD_RS, OUTPUT);
				pinMode(LCD_E,  OUTPUT);
				pinMode(LCD_D7, OUTPUT);
				pinMode(LCD_D6, OUTPUT);
				pinMode(LCD_D5, OUTPUT);
				pinMode(LCD_D4, OUTPUT);
				lcd.begin(20, 4);				  //tamaño de LCD				
		// DMX
			ArduinoDmx0.set_tx_address(1);      // poner aqui la direccion de inicio de DMX 
			ArduinoDmx0.set_tx_channels(512);   // poner aqui el numero de canales a transmitir 
			ArduinoDmx0.init_tx(DMX512);        // iniciar transmision universo 0, modo estandar DMX512
	}    

void loop()
	{
		GUI_Init();
		GUI_Memory();
	}
	
void GUI_Init()
	{
		lcd.clear ();
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
		delay(1000);  			//retardo de muestra de mensaje
	}
	
void GUI_Control_Multi()
	{
		lcd.clear();
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
				Cursor_Conf[0][0]  = 1;	// Back
				Cursor_Conf[0][4]  = 1;	// Next
				Cursor_Conf[0][8]  = 1;	// Memoria
				Cursor_Conf[0][12] = 1;	// Banco
			// Row 1
				Cursor_Conf[1][0]  = 1;
				Cursor_Conf[1][4]  = 1;
				Cursor_Conf[1][8]  = 1;
				Cursor_Conf[1][12] = 1;
				Cursor_Conf[1][16] = 1;
			// Row 2
				Cursor_Conf[2][0]  = 1;
				Cursor_Conf[2][4]  = 1;
				Cursor_Conf[2][8]  = 1;
				Cursor_Conf[2][12] = 1;
				Cursor_Conf[2][16] = 1;
			// Row 3
				Cursor_Conf[3][0]  = 1;
				Cursor_Conf[3][4]  = 1;
				Cursor_Conf[3][8]  = 1;
				Cursor_Conf[3][12] = 1;
				Cursor_Conf[3][16] = 1;
		// navegar
			GUI_Navegar();
		// Acciones
			
	}
	
void Cursor_Conf_Clear()
	{
		for (byte Conteo_Col = 0; Conteo_Col <= 19; Conteo_Col ++)
			{
				for (byte Conteo_Row = 0; Conteo_Row <= 3; Conteo_Row ++)
					{
						Cursor_Conf[Conteo_Row][Conteo_Col] = 0;
					}
			}
	}
	
void GUI_Navegar()
	{
		byte LCD_Col_Pos_Ant;	// saber el estado anterior para borrar cursor
		byte LCD_Row_Pos_Ant;	// saber el estado anterior para borrar cursor
		
		// guardar valor anterior de row col
			LCD_Col_Pos_Ant = LCD_Col_Pos;
			LCD_Row_Pos_Ant = LCD_Row_Pos;
		// Dibujar cursor
			lcd.setCursor (LCD_Col_Pos, LCD_Row_Pos);
			lcd.print(">"); 
			
			lcd.setCursor (11, 0);
			lcd.print("Col");
			lcd.setCursor (11, 1);
			lcd.print("Row");
																					
		// navegacion
			Dibujar:
				byte Salida_Navegar = 0;		// salida de lectura de botones
				byte Dibujar_Cursor = 0;		// saber si dibujar cursor para evitar repeticiones en lcd, 0 no dibujar, 1 dibujar >, 2 dibujar +
						
						// Left
							if (digitalRead(Boton_Left) == LOW)
								{
									delay (Boton_Delay);
									byte Salida_Left = 0;
									byte LCD_Col_Pos_Temp = 0;
									LCD_Col_Pos_Temp = LCD_Col_Pos;
								
									while (Salida_Left == 0)
										{
											LCD_Col_Pos_Temp = LCD_Col_Pos_Temp - 1;
											if (Cursor_Conf[LCD_Row_Pos][LCD_Col_Pos_Temp] == 1)
												{
													if (LCD_Col_Pos_Temp <= 0)
														{
															LCD_Col_Pos_Temp = 20;
														}
													LCD_Col_Pos = LCD_Col_Pos_Temp;
													Dibujar_Cursor = 1;
													
													lcd.setCursor (15, 0);
													lcd.print("  ");
													lcd.setCursor (15, 0);
													lcd.print(LCD_Col_Pos_Temp);
													
													lcd.setCursor (15, 1);
													lcd.print("  ");
													lcd.setCursor (15, 1);
													lcd.print(LCD_Row_Pos);
			
													Salida_Left = 1;
												}
											if (LCD_Col_Pos_Temp == 0)
												{
													LCD_Col_Pos_Temp = 20;
												}
										}
									goto Salida;
								}
						// Right
							if (digitalRead(Boton_Right) == LOW)
								{
									delay(Boton_Delay);
									byte Salida_Right = 0;
									byte LCD_Col_Pos_Temp = 0;
									LCD_Col_Pos_Temp = LCD_Col_Pos;
									while (Salida_Right == 0)
										{
											LCD_Col_Pos_Temp = LCD_Col_Pos_Temp + 1;
											if (LCD_Col_Pos_Temp >= 20)
													{
														LCD_Col_Pos_Temp = 0;	// regresar al cero
													}
											if (Cursor_Conf[LCD_Row_Pos][LCD_Col_Pos_Temp] == 1)
												{
													LCD_Col_Pos = LCD_Col_Pos_Temp;
													Dibujar_Cursor = 1;
													
													lcd.setCursor (15, 0);
													lcd.print("  ");
													lcd.setCursor (15, 0);
													lcd.print(LCD_Col_Pos_Temp);
													
													lcd.setCursor (15, 1);
													lcd.print("  ");
													lcd.setCursor (15, 1);
													lcd.print(LCD_Row_Pos);
													
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
									byte LCD_Row_Pos_Temp = 0;
									LCD_Row_Pos_Temp = LCD_Row_Pos;
									while (Salida_Down == 0)
										{
											LCD_Row_Pos_Temp = LCD_Row_Pos_Temp + 1;
											if (LCD_Row_Pos_Temp >= 4)
													{
														LCD_Row_Pos_Temp = 0;	// regresar al cero
													}
											if (Cursor_Conf[LCD_Row_Pos_Temp][LCD_Col_Pos] == 1)
												{
													LCD_Row_Pos = LCD_Row_Pos_Temp;
													Dibujar_Cursor = 1;
													
													lcd.setCursor (15, 0);
													lcd.print("  ");
													lcd.setCursor (15, 0);
													lcd.print(LCD_Col_Pos);
													
													lcd.setCursor (15, 1);
													lcd.print("  ");
													lcd.setCursor (15, 1);
													lcd.print(LCD_Row_Pos_Temp);
													
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
									byte LCD_Row_Pos_Temp;
									LCD_Row_Pos_Temp = LCD_Row_Pos;
									while (Salida_Up == 0)
										{
											LCD_Row_Pos_Temp = LCD_Row_Pos_Temp - 1;
											if (Cursor_Conf[LCD_Row_Pos_Temp][LCD_Col_Pos] == 1)
												{
													if (LCD_Row_Pos_Temp <= 0)
														{
															LCD_Row_Pos_Temp = 4;
														}
													Dibujar_Cursor = 1;
													
													lcd.setCursor (15, 0);
													lcd.print("  ");
													lcd.setCursor (15, 0);
													lcd.print(LCD_Col_Pos);
													
													lcd.setCursor (15, 1);
													lcd.print("  ");
													lcd.setCursor (15, 1);
													lcd.print(LCD_Row_Pos_Temp);
													
													LCD_Row_Pos = LCD_Row_Pos_Temp;
													Salida_Up = 1;
												}
											if (LCD_Row_Pos_Temp == 0)
												{
													LCD_Row_Pos_Temp = 4;
												}
										}
									goto Salida;
								}
						// Center
							if (digitalRead(Boton_Center) == LOW)
								{
									delay(Boton_Delay);
									byte Salida_Center = 0;
									while (Salida_Center == 0)
										{
											if (Cursor_Conf[LCD_Row_Pos][LCD_Col_Pos] == 1)
												{
													Dibujar_Cursor = 2;	// dibujar +
													Salida_Center = 1;
												}
										}
								}
			Salida:
				// Dibujar Cursor
					if (Dibujar_Cursor > 0)
						{
							if (Dibujar_Cursor == 1)
								{
									// borra el anterior
										lcd.setCursor (LCD_Col_Pos_Ant, LCD_Row_Pos_Ant);
										lcd.print(" "); 
									// escribir >
										lcd.setCursor (LCD_Col_Pos, LCD_Row_Pos);
										lcd.print(">");
								}
							else
								{
									// escribir +
										lcd.setCursor (LCD_Col_Pos, LCD_Row_Pos);
										lcd.print("+");
								}
			
							//salida
								LCD_Col_Pos_Ant = LCD_Col_Pos;
								LCD_Row_Pos_Ant = LCD_Row_Pos;
								if (Dibujar_Cursor == 2)
									{
										goto Salir;
									}
								else	
									{
										Dibujar_Cursor = 0;
									}
						}
			goto Dibujar;
			Salir: {}
	}

void GUI_Memory()
	{
		lcd.clear ();
		// Texto
			lcd.setCursor (0, 0);
			lcd.print("Memory:");
			lcd.setCursor (2, 2);
			lcd.print("Empty");
			lcd.setCursor (9, 2);
			lcd.print("Load");
			lcd.setCursor (15, 2);
			lcd.print("Clear");
		// Cursor
			LCD_Col_Pos = 1;		// posicion de cursor
			LCD_Row_Pos = 2;
		// configuracion de cursor	
			Cursor_Conf_Clear();	// limpiar array
			// Acciones
				Cursor_Conf[2][1]  = 1;	// Empty
				Cursor_Conf[2][8]  = 1; // Load
				Cursor_Conf[2][14] = 1;	// Clear
		// navegar
			GUI_Navegar();
		// Acciones
			// Load
				if (LCD_Col_Pos == 8 && LCD_Row_Pos == 2)
					{
						EEPROM_Load();
						GUI_Control_Options();
					}
			// Clear
				if (LCD_Col_Pos == 14 && LCD_Row_Pos == 2)
					{
						EEPROM_Clear();
						GUI_Control_Options();
					}
			// Empty
				if (LCD_Col_Pos == 1 && LCD_Row_Pos == 2)
					{
						GUI_Control_Options();
					}
	}
	
void EEPROM_Load()
	{
		lcd.clear ();
		lcd.setCursor (0, 1);
		lcd.print ("Memory Loading:");
		for(int Canal = 0; Canal <= 511; Canal ++)
			{
				DMX_Values[Canal] = EEPROM.read(Canal);          	// lectura desde EEPROM
				ArduinoDmx0.TxBuffer[Canal] = DMX_Values[Canal]; 	// salida a DMX
				lcd.setCursor (17, 1);
				lcd.print (Canal);
				delay (1);
			}
		lcd.clear ();
		lcd.setCursor (3, 1);
		lcd.print ("Memory Loaded!");
		delay (1000);
	}
	
void EEPROM_Clear()
	{
		lcd.clear ();
		lcd.setCursor (0, 1);
		lcd.print ("Memory Cleaning:");
		for(int Canal = 0; Canal <= 511; Canal ++)
			{
				DMX_Values[Canal] = 0;          		// lectura desde EEPROM
				ArduinoDmx0.TxBuffer[Canal] = 0; 		// salida a DMX
				EEPROM.write (Canal, 0);				// escritura EEPROM
				lcd.setCursor (17, 1);
				lcd.print (Canal);
			}
		lcd.clear ();
		lcd.setCursor (2, 1);
		lcd.print ("Memory Cleaned!");
		delay (1000);
	}
	
void GUI_Control_Options()
	{
		// LCD
			lcd.clear ();
			lcd.setCursor (0, 0);
			lcd.print ("Control Options:");
			lcd.setCursor (3, 2);
			lcd.print ("Unit    Multi");
		// Cursor
			LCD_Col_Pos = 2;		// posicion de cursor
			LCD_Row_Pos = 2;
		// configuracion de cursor	
			Cursor_Conf_Clear();	// limpiar array
			// Acciones
				Cursor_Conf[2][2]   = 1;	// Unit
				Cursor_Conf[2][10]  = 1; 	// Multi
		// navegar
			GUI_Navegar();
		// Acciones
			// Unit
				if (LCD_Col_Pos == 2 && LCD_Row_Pos == 2)
					{
						GUI_Control_Unit();
						delay(10000);
					}
			// Multi
				if (LCD_Col_Pos == 10 && LCD_Row_Pos == 2)
					{
						GUI_Control_Multi();
						delay(10000);
					}
			
	}
	
void GUI_Control_Unit()
	{
		// GUI
			lcd.clear ();
			lcd.setCursor (0, 0);
			lcd.print ("Control Unit:");
			lcd.setCursor (17, 0);
			lcd.print ("Bac");
			lcd.setCursor (17, 2);
			lcd.print ("Mem");
			lcd.setCursor (0, 2);
			lcd.print ("Channel:  000");
			lcd.setCursor (2, 3);
			lcd.print ("Value:  000");
			
	}

void Numerico_Calc()
	{
		long Num_Barrido_Time = 10;		// tiempo entre barrido de keys

		while (Boton_Calc == 17)		// valor calculado	# E * F, 17 sin valor calculado
			{
				// Letras	
					// Barrido
						// Linea 1
							digitalWrite(Boton_Array_1, LOW);	// lectura linea 1
							// Lectura 1A = 1
								if (digitalRead(Boton_Array_A) == LOW)
									{
										Boton_Calc = 1;
										delay(Num_Barrido_Time);
									}
								delay(Num_Barrido_Time);
							// Lectura 1B = 6
								if (digitalRead(Boton_Array_B) == LOW)
									{
										Boton_Calc = 6;
										delay(Num_Barrido_Time);
									}
								delay(Num_Barrido_Time);
							// Lectura 1C = 7
								if (digitalRead(Boton_Array_C) == LOW)
									{
										Boton_Calc = 7;
										delay(Num_Barrido_Time);
									}	
								delay(Num_Barrido_Time);
							// Lectura 1D = * = 15
								if (digitalRead(Boton_Array_D) == LOW)
									{
										Boton_Calc = 15;
										delay(Num_Barrido_Time);
									}
								delay(Num_Barrido_Time);
							digitalWrite(Boton_Array_1, HIGH);	// lectura linea 1
							
						// Linea 2
							digitalWrite(Boton_Array_2, LOW);	// lectura linea 2
							// Lectura 2A = 2
								if (digitalRead(Boton_Array_A) == LOW)
									{
										Boton_Calc = 2;
										delay(Num_Barrido_Time);
									}
								delay(Num_Barrido_Time);
							// Lectura 2B = 5
								if (digitalRead(Boton_Array_B) == LOW)
									{
										Boton_Calc = 5;
										delay(Num_Barrido_Time);
									}
								delay(Num_Barrido_Time);
							// Lectura 2C = 8
								if (digitalRead(Boton_Array_C) == LOW)
									{
										Boton_Calc = 8;
										delay(Num_Barrido_Time);
									}	
								delay(Num_Barrido_Time);
							// Lectura 2D = 0
								if (digitalRead(Boton_Array_D) == LOW)
									{
										Boton_Calc = 0;
										delay(Num_Barrido_Time);
									}
								delay(Num_Barrido_Time);
							digitalWrite(Boton_Array_2, HIGH);	// lectura linea 2
							
						// Linea 3
							digitalWrite(Boton_Array_3, LOW);	// lectura linea 3
							// Lectura 3A = 3
								if (digitalRead(Boton_Array_A) == LOW)
									{
										Boton_Calc = 3;
										delay(Num_Barrido_Time);
									}
								delay(Num_Barrido_Time);
							// Lectura 3B = 4
								if (digitalRead(Boton_Array_B) == LOW)
									{
										Boton_Calc = 4;
										delay(Num_Barrido_Time);
									}
								delay(Num_Barrido_Time);
							// Lectura 3C = 9
								if (digitalRead(Boton_Array_C) == LOW)
									{
										Boton_Calc = 9;
										delay(Num_Barrido_Time);
									}	
								delay(Num_Barrido_Time);
							// Lectura 3D = 14
								if (digitalRead(Boton_Array_D) == LOW)
									{
										Boton_Calc = 14;
										delay(Num_Barrido_Time);
									}
								delay(Num_Barrido_Time);
							digitalWrite(Boton_Array_3, HIGH);	// lectura linea 3
						
						// Linea 4
							digitalWrite(Boton_Array_4, LOW);	// lectura linea 4
							// Lectura 4A = 10
								if (digitalRead(Boton_Array_A) == LOW)
									{
										Boton_Calc = 10;
										delay(Num_Barrido_Time);
									}
								delay(Num_Barrido_Time);
							// Lectura 4B = 11
								if (digitalRead(Boton_Array_B) == LOW)
									{
										Boton_Calc = 11;
										delay(Num_Barrido_Time);
									}
								delay(Num_Barrido_Time);
							// Lectura 4C = 12
								if (digitalRead(Boton_Array_C) == LOW)
									{
										Boton_Calc = 12;
										delay(Num_Barrido_Time);
									}
								delay(Num_Barrido_Time);
							// Lectura 4D = 13
								if (digitalRead(Boton_Array_D) == LOW)
									{
										Boton_Calc = 13;
										delay(Num_Barrido_Time);
									}
								delay(Num_Barrido_Time);
							digitalWrite(Boton_Array_4, HIGH);	// lectura linea 4
			}	
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
