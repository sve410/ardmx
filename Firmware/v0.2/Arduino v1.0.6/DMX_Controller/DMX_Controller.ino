// includes
	#include <lib_dmx.h>  		// libreria DMX 4 universos deskontrol four universes DMX library  - http://www.deskontrol.net/blog
	#include <LiquidCrystal.h>	// libreria para LCD
		
// DMX Library
	#define      DMX512	    (0)    // (250 kbaud - 2 to 512 channels) Standard USITT DMX-512
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
		// GUI
			byte Cursor_Pos_X_Y = 0;			// para calcular posicion de cursor
			byte Cursor_EN;						// saber si escribir 1 o borrar 0 el cursor
			byte Cursor_Set[79];				// saber que posiciones disonibles hay para mostrar el cursor
			
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
				lcd.begin(20, 4);				//tamaño de LCD
		// DMX
			ArduinoDmx0.set_tx_address(1);      // poner aqui la direccion de inicio de DMX 
			ArduinoDmx0.set_tx_channels(512);   // poner aqui el numero de canales a transmitir 
			ArduinoDmx0.init_tx(DMX512);        // iniciar transmision universo 0, modo estandar DMX512
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
		lcd.setCursor (1,0);
		lcd.print("Bac Nex Mem 000-000");
		for (byte Conteo = 1; Conteo < 4; Conteo ++)
			{
				lcd.setCursor (1, Conteo);
				lcd.print("000 000 000 000 000"); 
			}
		// posicionar cursor
			Cursor_Pos_X_Y = 12;	// posicion de cursor
			Cursor_EN = 1;			// escribir cursor
			Cursor_Calc();			// calcular y escribir cursor
		// Cursores disponibles
			Cursor_Set_Clear();		// limpiar array
			Cursor_Set[0] = 1;
			Cursor_Set[4] = 1;
			Cursor_Set[8] = 1;
			Cursor_Set[12] = 1;
			Cursor_Set[20] = 1;
			Cursor_Set[24] = 1;
			Cursor_Set[28] = 1;
			Cursor_Set[32] = 1;
			Cursor_Set[36] = 1;
			Cursor_Set[40] = 1;
			Cursor_Set[44] = 1;
			Cursor_Set[48] = 1;
			Cursor_Set[52] = 1;
			Cursor_Set[56] = 1;
			Cursor_Set[60] = 1;
			Cursor_Set[64] = 1;
			Cursor_Set[68] = 1;
			Cursor_Set[72] = 1;
			Cursor_Set[76] = 1;
	}
	
void Cursor_Calc()
	{		
		byte Cursor_Pos_X = 0;		// posicion calculada LCD X
		byte Cursor_Pos_Y = 0;		// posicion calculada LCD Y
		
		// Columna 00
			if (Cursor_Pos_X_Y <= 19)
				{
					Cursor_Pos_Y = 0;
					Cursor_Pos_X = Cursor_Pos_X_Y; 
				}
		// Columna 01
			if (Cursor_Pos_X_Y >= 20 && Cursor_Pos_X_Y <= 39)
				{
					Cursor_Pos_Y = 1;
					Cursor_Pos_X = Cursor_Pos_X_Y - 20; 
				}
		// Columna 02
			if (Cursor_Pos_X_Y >= 40 && Cursor_Pos_X_Y <= 59)
				{
					Cursor_Pos_Y = 2;
					Cursor_Pos_X = Cursor_Pos_X_Y - 40; 
				}
		// Columna 03
			if (Cursor_Pos_X_Y >= 60 && Cursor_Pos_X_Y <= 79)
				{
					Cursor_Pos_Y = 3;
					Cursor_Pos_X = Cursor_Pos_X_Y - 60; 
				}	
		// Escribir o borrar cursor
			lcd.setCursor(Cursor_Pos_X, Cursor_Pos_Y);
			if (Cursor_EN == 1)
				{
					lcd.print(">");
				}
			else
				{
					lcd.print(" ");
				}
	}
	
	void Cursor_Set_Clear()
		{	
			for (byte Conteo = 0; Conteo <= 79; Conteo ++)
				{
					Cursor_Set[Conteo] = 0;
				}
		}

