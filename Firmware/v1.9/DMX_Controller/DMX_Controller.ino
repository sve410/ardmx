// ***************************************************************************************************************************
// ***************************************************************************************************************************
// **				                                                                                                        **
// **											Arduino DMX-512 Tester Controller				                            **
// **																	                                                    **
// **	- Firmware v1.9																										**
// **	- Hardware v0.7																										**
// **																														**
// **	- Compilado en Arduino IDE v1.0.6																					**
// **		http://www.arduino.cc/en/Main/OldSoftwareReleases																**
// ** 	- Editado en Sublime Text																							**
// **		https://notepad-plus-plus.org/																					**
// **		Formato Windows ANSI																							**
// **	- Compilado para Arduino Mega 2560 R3																				**
// **		http://www.arduino.cc/en/Main/ArduinoBoardMega2560																**
// **	- Libreria Arduino cuatro universos DMX v0.3 - Deskontrol.net														**
// **		http://www.deskontrol.net/blog/libreria-arduino-cuatro-universos-dmx/)											**
// **	- Libreria LCD v1.2.1 - Francisco Malpartida																		**
// **		https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home													**
// **	- Libreria Encoder v1.2 - pjrc.com																					**
// **		http://www.pjrc.com/teensy/td_libs_Encoder.html																	**
// **																														**
// **	Autor:																												**
// **																														**
// **	Copyright (C) 2015 - Daniel Roberto Becerril Angeles																**
// **	daniel3514@gmail.com																								**
// **	https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki												**
// **																														**
// **	Licenciamiento:																										**
// **																														**
// **	Firmware:																											**
// **		GNU General Pubic Licence Version v3																			**
// **		https://www.gnu.org/copyleft/gpl.html																			**
// **																														**
// **	Hardware:																											**
// **		Open Source Hardware (OSHW) v1.0																				**
// **		http://freedomdefined.org/OSHW#Licenses_and_Hardware															**
// **		http://www.oshwa.org/definition/																				**
// **																														**
// **	Este programa es software libre: usted puede redistribuirlo y / o modificarlo bajo los términos de la 				**
// **	Licencia Pública General GNU publicada por la Free Software Foundation, bien de la versión 3 de la Licencia, 		**
// **	o (A su elección) cualquier versión posterior.																		**
// **																														**
// **	Este programa se distribuye con la esperanza de que sea útil, pero SIN NINGUNA GARANTIA; ni siquiera la garantía 	**
// **	implícita de COMERCIALIZACION o IDONEIDAD PARA UN PROPOSITO PARTICULAR. Vea el GNU General Public License 			**
// **	para más detalles.																									**
// **																														**
// ** 	Esto es software libre, y le invitamos a redistribuirlo bajo ciertas condiciones									**
// **																														**
// **	Deberá haber recibido una copia de la Licencia Pública General GNU													**
// **	junto con este programa. Si no es así, consulte <http://www.gnu.org/licenses/>.										**
// **																														**
// ***************************************************************************************************************************
// ***************************************************************************************************************************

	// Librerias
#include <LiquidCrystal.h>			// libreria para LCD - ttps://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home	
#include <Wire.h>
#include <EEPROM.h>
#include <string.h>
#include <lib_dmx.h>  				// libreria DMX 4 universos deskontrol four universes DMX library  - http://www.deskontrol.net/blog
#include <Encoder.h>				// libreria encoder - http://www.pjrc.com/teensy/td_libs_Encoder.html		

	// DMX Library
#define    DMX512	  		(0)  	// (250 kbaud  - 2 to 512 channels) Standard USITT DMX-512
//#define  DMX1024    		(1)   	// (500 kbaud  - 2 to 1024 channels) Completely non standard - TESTED ok
//#define  DMX2048    		(2)   	// (1000 kbaud - 2 to 2048 channels) called by manufacturers DMX1000K, DMX 4x or DMX 1M ???

	// DMX
int  	DMX_Values 			[515];  // array de valores actuales DMX
int  	Canal_Actual 		= 1;	// canal actual de dmx
byte 	Universo_Actual		= 0;	// universo actual de dmx

	// Encoder
byte  	Enc_Center			= 8;	// pin
byte 	Enc_CLK				= 7;	// pin
byte 	Enc_Data 			= 6;	// pin
Encoder myEnc				(Enc_CLK, Enc_Data);	// conexion de encoder

	// Cursor
int  Cursor_Index_Pos 		= 1;	// posicion en tiempo real de lcd
byte Cursor_Index[20][4] 	= 
						{	{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, }
						};

	// tecleado					
byte Keypad_A				= 30; 	
byte Keypad_B				= 32; 	
byte Keypad_C				= 34; 	
byte Keypad_D				= 36; 	
byte Keypad_1				= 38; 	
byte Keypad_2				= 40; 
byte Keypad_3				= 42;
byte Keypad_4				= 44;

	// LCD
byte LCD_RS 				= 43;	// pin
byte LCD_E  				= 45;	// pin
byte LCD_D4 				= 47;	// pin
byte LCD_D5 				= 49;	// pin
byte LCD_D6 				= 51;	// pin
byte LCD_D7					= 53;	// pin
byte Back_Light_PWM			= 13;	// salida para PWM de Back Light de LCD
byte Contrast_PWM			= 12;	// salida para pwm de contraste de LCD
byte Light_On_Off			= 0;	// saber si esta encendida o apagada, back y key
LiquidCrystal lcd			(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);  //LCD setup

	// Key Light
byte Key_Light_PWM			= 11;	// pin
byte Key_Light_SW			= 3;	// pin

	// Light external
byte Light_PWM 				= 10;	// pin
byte Light_SW 				= 2;	// pin

	// EEPROM
int  BackLight_Add 			= 4094;	// direccion de eeprom
int  Contrast_Add			= 4095;	// direccion de eeprom
int  Bank_Init_Add			= 4093;	// direccion de eeprom
int  Key_Light_Add			= 4092;	// direccion de eeprom
int  Light_Ext_Add			= 4091;	// direccion de eeprom
int  EEPROM_Limit			= 4090;	// limite de espacios en eeprom para universos
byte EEPROM_Def_Jumper		= 9;	// pin

void setup()
{
		// Encoder
	pinMode			(Enc_Center,	INPUT_PULLUP);
	// no es necesario declarar CLK y data

	// Teclado
	pinMode			(Keypad_A, 		OUTPUT);
	pinMode			(Keypad_B, 		OUTPUT);
	pinMode			(Keypad_C, 		OUTPUT);
	pinMode			(Keypad_D, 		OUTPUT);
	pinMode			(Keypad_1, 		INPUT_PULLUP);
	pinMode			(Keypad_2, 		INPUT_PULLUP);
	pinMode			(Keypad_3, 		INPUT_PULLUP);
	pinMode			(Keypad_4, 		INPUT_PULLUP);

	digitalWrite	(Keypad_A, 		HIGH);
	digitalWrite	(Keypad_B, 		HIGH);
	digitalWrite	(Keypad_C, 		HIGH);
	digitalWrite	(Keypad_D, 		HIGH);

		// LCD
	pinMode(LCD_RS, 				OUTPUT);
	pinMode(LCD_E,  				OUTPUT);
	pinMode(LCD_D7, 				OUTPUT);
	pinMode(LCD_D6, 				OUTPUT);
	pinMode(LCD_D5, 				OUTPUT);
	pinMode(LCD_D4, 				OUTPUT);
	pinMode(Back_Light_PWM,			OUTPUT);
	pinMode(Contrast_PWM,			OUTPUT);
	lcd.begin(20, 4);							//tamaño de LCD

		// Key Light
	pinMode(Key_Light_PWM,			OUTPUT);
	pinMode(Key_Light_SW,			INPUT_PULLUP);

		// Light
	pinMode(Light_PWM,				OUTPUT);
	pinMode(Light_SW,				INPUT_PULLUP);

		// EEPROM Default
	pinMode(EEPROM_Def_Jumper, 		INPUT);		// no tiene pullup fisico

		// DMX
	ArduinoDmx0.set_tx_address		(1);      	// poner aqui la direccion de inicio de DMX
	ArduinoDmx0.set_tx_channels		(512);   	// poner aqui el numero de canales a transmitir
	ArduinoDmx0.init_tx				(DMX512);   // iniciar transmision universo 0, modo estandar DMX512

		// no conectados
	pinMode			(5,   OUTPUT);
	digitalWrite	(5,   LOW);
	pinMode			(20,  OUTPUT);
	digitalWrite	(20,  LOW);
	pinMode			(21,  OUTPUT);
	digitalWrite	(21,  LOW);
	pinMode			(22,  OUTPUT);
	digitalWrite	(22,  LOW);
	pinMode			(23,  OUTPUT);
	digitalWrite	(23,  LOW);
	pinMode			(24,  OUTPUT);
	digitalWrite	(24,  LOW);
	pinMode			(25,  OUTPUT);
	digitalWrite	(25,  LOW);
	pinMode			(26,  OUTPUT);
	digitalWrite	(26,  LOW);
	pinMode			(27,  OUTPUT);
	digitalWrite	(27,  LOW);
	pinMode			(28,  OUTPUT);
	digitalWrite	(28,  LOW);
	pinMode			(29,  OUTPUT);
	digitalWrite	(29,  LOW);
	pinMode			(31,  OUTPUT);
	digitalWrite	(31,  LOW);
	pinMode			(33,  OUTPUT);
	digitalWrite	(33,  LOW);
	pinMode			(35,  OUTPUT);
	digitalWrite	(35,  LOW);
	pinMode			(37,  OUTPUT);
	digitalWrite	(37,  LOW);
	pinMode			(39,  OUTPUT);
	digitalWrite	(39,  LOW);
	pinMode			(41,  OUTPUT);
	digitalWrite	(41,  LOW);
	pinMode			(46,  OUTPUT);
	digitalWrite	(46,  LOW);
	pinMode			(48,  OUTPUT);
	digitalWrite	(48,  LOW);
	pinMode			(50,  OUTPUT);
	digitalWrite	(50,  LOW);
	pinMode			(52,  OUTPUT);
	digitalWrite	(52,  LOW);
	pinMode			(A0,  OUTPUT);
	digitalWrite	(A0,  LOW);
	pinMode			(A1,  OUTPUT);
	digitalWrite	(A1,  LOW);
	pinMode			(A2,  OUTPUT);
	digitalWrite	(A2,  LOW);
	pinMode			(A3,  OUTPUT);
	digitalWrite	(A3,  LOW);
	pinMode			(A4,  OUTPUT);
	digitalWrite	(A4,  LOW);
	pinMode			(A5,  OUTPUT);
	digitalWrite	(A5,  LOW);
	pinMode			(A6,  OUTPUT);
	digitalWrite	(A6,  LOW);
	pinMode			(A7,  OUTPUT);
	digitalWrite	(A7,  LOW);
	pinMode			(A8,  OUTPUT);
	digitalWrite	(A8,  LOW);
	pinMode			(A9,  OUTPUT);
	digitalWrite	(A9,  LOW);
	pinMode			(A10, OUTPUT);
	digitalWrite	(A10, LOW);
	pinMode			(A11, OUTPUT);
	digitalWrite	(A11, LOW);
	pinMode			(A12, OUTPUT);
	digitalWrite	(A12, LOW);
	pinMode			(A13, OUTPUT);
	digitalWrite	(A13, LOW);
	pinMode			(A14, OUTPUT);
	digitalWrite	(A14, LOW);
	pinMode			(A15, OUTPUT);
	digitalWrite	(A15, LOW);
}

void loop()
{
	Back_Light_Init();		// inicializador de Backlight desde eeprom
	Contrast_Init();		// inicializador de EEPROM desde eeprom
	EEPROM_Default();		// jumper para default eeprom
	EEPROM_Load_Init();		// valores desde eeprom
	GUI_About();			// interface grafica de about
	GUI_Memory_Init();		// interface grafica de memoria
}

void EEPROM_Default()
{
	// jumper cerrado, eeprom a default
		// valores default
	byte Key_Light_Val_Def	= 255;	// valor default de keylight
	byte Ext_Light_Def		= 255;	// valor default ext light
	byte CH_DMX_Val_Def		= 0;	// valor default de canales DMX
	byte Initial_Bank_Def	= 1;	// banco inicial de memoria a cargar
	byte Backlight_Def		= 255;	
	byte Contrast_Def		= 150;

	if (digitalRead(EEPROM_Def_Jumper) == 0)
	{
		lcd.clear ();
		lcd.setCursor(1, 1);
		lcd.print("EEPROM Default:");

			// canales DMX
		for (int ch = 0; ch <= EEPROM_Limit; ch ++)
		{
			EEPROM.write(ch, CH_DMX_Val_Def);
			lcd.setCursor(16, 1);
			lcd.print(ch);
		}

			// backlight
		EEPROM.write(BackLight_Add, Backlight_Def);
			// contraste
		EEPROM.write(Contrast_Add,  Contrast_Def);
			// Bank init
		EEPROM.write(Bank_Init_Add, Initial_Bank_Def);
			// Key light
		EEPROM.write(Key_Light_Add, Key_Light_Val_Def);
			// Light Ext
		EEPROM.write(Light_Ext_Add, Ext_Light_Def);

		lcd.clear ();
		lcd.setCursor(1, 0);
		lcd.print("EEPROM Default ok!");
		lcd.setCursor(3, 2);
		lcd.print("Remove jumper");
		lcd.setCursor(4, 3);
		lcd.print("and reset!");
		while(1);
	}
}

void Back_Light_Init()
{
	// lee y aplica el ultimo estado del backlight

	byte Back_Light_Value = EEPROM.read(BackLight_Add);
		
		// dimmer de pantalla
	for (int dim = 0; dim <= Back_Light_Value; dim ++)
	{
		analogWrite(Back_Light_PWM, dim);
		delay(3);	// aqui el retardo para el dimmer
	}	

	if (Back_Light_Value == 0)
	{
		Light_On_Off = 0;
	}

	if (Back_Light_Value > 0)
	{
		Light_On_Off = 1;
	}
}

void Contrast_Init()
{
	// lee y aplica el ultimo estado del contrast

	byte Contrast_Value = EEPROM.read(Contrast_Add);
  
	if (Contrast_Value < 150)
	{
		Contrast_Value = 150;
	}

	analogWrite(Contrast_PWM, Contrast_Value);
}

void Light_En()
{
	// encender back y key desde la tecla *

	byte Back_Light_Value 	= EEPROM.read(BackLight_Add);	// lectura del ultimo valor desde la eeprom
	byte Key_Light_Value	= EEPROM.read(Key_Light_Add);	// lectura del ultimo valor desde la eeprom
	long delay_dimmer		= 1;
	
		// encender
	if (Light_On_Off == 0)									// si esta apagada encenderla
	{
		// si el valor es 0 lo encendemos de todos modos
		if (Back_Light_Value == 0)
		{
			for (int contar = 0; contar <= 127; contar ++)
			{
				analogWrite(Back_Light_PWM, contar);		// aqui el valor a encender en el caso que se haya establecido apagado
				delay(delay_dimmer);
			}
		}

		if (Key_Light_Value == 0)
		{
			for (int contar = 0; contar <= 127; contar ++)
			{
				analogWrite(Key_Light_PWM, 127);			// aqui el valor a encender en el caso que se haya establecido apagado
				delay(delay_dimmer);
			}
		}
		
			// solo encender
		if (Back_Light_Value > 0)
		{
			for (int contar = 0; contar <= Back_Light_Value; contar ++)
			{
				analogWrite(Back_Light_PWM, contar);		// encender con el valor de la eeprom
				delay(delay_dimmer);
			}
		}

		if (Key_Light_Value > 0)
		{
			for (int contar = 0; contar <= Back_Light_Value; contar ++)
			{
				analogWrite(Key_Light_PWM, Key_Light_Value);// encender con el valor de la eeprom
				delay(delay_dimmer);
			}
		}

		Light_On_Off = 1;
		goto salida;
	}
	
	// apagar
	if (Light_On_Off == 1)									// si esta encendida apagarla
	{
		for (int contar = Back_Light_Value; contar != 0; contar --)
		{
			analogWrite(Back_Light_PWM, contar);
			delay(delay_dimmer);
		}
		analogWrite(Back_Light_PWM, 0);
		analogWrite(Key_Light_PWM, 0);
		Light_On_Off = 0;
	}

	salida:

	delay(300);												// para impedir repeticion del comando
}

void GUI_Licence()
{
	// imprimir licencia

	int retardo = 4000;
	
	lcd.clear ();
	lcd.setCursor(0, 0);
	lcd.print("  This program is");
	lcd.setCursor(0, 1);
	lcd.print("distributed in the");
	lcd.setCursor(0, 2);
	lcd.print("hope that it will be");
	lcd.setCursor(0, 3);
	lcd.print("useful, but");

	delay(retardo);

	lcd.clear ();
	lcd.setCursor(0, 0);
	lcd.print("WITHOUT ANY WARRANTY");
	lcd.setCursor(0, 1);
	lcd.print("without even the");
	lcd.setCursor(0, 2);
	lcd.print("implied warranty of");
	lcd.setCursor(0, 3);
	lcd.print("MERCHANTABILITY of");

	delay(retardo);

	lcd.clear ();
	lcd.setCursor(0, 0);
	lcd.print("FITNESS FOR A");
	lcd.setCursor(0, 1);
	lcd.print("PARTICULAR PORPUSE.");
	lcd.setCursor(0, 2);
	lcd.print("    This is free ");
	lcd.setCursor(0, 3);
	lcd.print("software and you are");

	delay(retardo);

	lcd.clear ();
	lcd.setCursor(0, 0);
	lcd.print("welcome to");
	lcd.setCursor(0, 1);
	lcd.print("redistribute it");
	lcd.setCursor(0, 2);
	lcd.print("under certain");
	lcd.setCursor(0, 3);
	lcd.print("conditions");

	delay(retardo);

	lcd.clear ();
	lcd.setCursor(0, 0);
	lcd.print("See the GNU GENERAL");
	lcd.setCursor(0, 1);
	lcd.print("PUBLIC LICENCE");
	lcd.setCursor(0, 2);
	lcd.print("for more details...");

	delay(retardo);
}

void GUI_About()
{
	// imprimir about

	byte Firm_Ver_Ent = 1;	// version firmware ----------------------------
	byte Firm_Ver_Dec = 9;
	byte Hard_Ver_Ent = 0;	// version hardware ----------------------------
	byte Hard_Ver_Dec = 7;
	byte Key_Light_Value 	= EEPROM.read(Key_Light_Add);
	byte Back_Light_Value 	= EEPROM.read(BackLight_Add);
	
	lcd.clear ();

	analogWrite(Key_Light_PWM, 0);
	analogWrite(Back_Light_PWM, 0);

	for (int numero = 0; numero <= 512; numero ++)	// efecto binario en lcd
	{
			// binario
		lcd.print (numero, BIN);
			// key light
		if (Key_Light_Value > 0)
		{
			if (numero <= 255)
			{
				if (numero <= Key_Light_Value)
				{
					analogWrite(Key_Light_PWM, numero);
				}
			}
		}
			// back light
		if (Back_Light_Value > 0)
		{
			if (numero <= 255)
			{
				if (numero <= Back_Light_Value)
				{
					analogWrite(Back_Light_PWM, numero);
				}
			}
		}
	}
	
	lcd.clear ();
	lcd.blink ();
	lcd.setCursor(3, 0);
	lcd.print("Arduino DMX-512");
	lcd.setCursor(1, 1);
	lcd.print("Tester & Controller");

		// Firmware
	lcd.setCursor(0, 3);
	lcd.print("Firm v");
	lcd.print(Firm_Ver_Ent);
	lcd.print(".");
	lcd.print(Firm_Ver_Dec);

		// Hardware
	lcd.setCursor(11, 3);
	lcd.print("Hard v");
	lcd.print(Hard_Ver_Ent);
	lcd.print(".");
	lcd.print(Hard_Ver_Dec);

		// bank
	lcd.setCursor(9, 2);
	lcd.print("b");
	if (Universo_Actual == 0)
	{
		lcd.print("-");
	}
	else
	{
		lcd.print(Universo_Actual);
	}
	lcd.setCursor(10, 2);	// Blink

		// lectura del boton centro
	while (digitalRead(Enc_Center) == HIGH);

	delay (300);			// rebote de boton
	lcd.clear ();
	lcd.setCursor(0, 0);
	lcd.print("Open Source License:");
	lcd.setCursor(0, 1);
	lcd.print("Firm: GNU GPL v3");
	lcd.setCursor(0, 2);
	lcd.print("Hard: OSHW    v1");
	lcd.setCursor(0, 3);
	lcd.print("Wiki: goo.gl/5nqJKt");
	lcd.setCursor(2, 1);

		// bank
	lcd.setCursor(18, 1);
	lcd.print("b");
	if (Universo_Actual == 0)
	{
		lcd.print("-");
	}
	else
	{
		lcd.print(Universo_Actual);
	}
	lcd.setCursor(19, 1);

		// lectura del boton centro
	while (digitalRead(Enc_Center) == HIGH);

	delay (300);			// rebote de boton
	lcd.noBlink ();
}

void Multi_Matrix(int inicial)
{
	// dibujar matriz de universo dmx
	/*
		// dibujar banco
	Numerico_Write (inicial, 13, 0);
	Numerico_Write (inicial + 14, 17, 0);

		// matrix 1
	Numerico_Write (DMX_Values[inicial], 1, 1);
	Numerico_Write (DMX_Values[inicial + 1], 5, 1);
	Numerico_Write (DMX_Values[inicial + 2], 9, 1);
	Numerico_Write (DMX_Values[inicial + 3], 13, 1);
	Numerico_Write (DMX_Values[inicial + 4], 17, 1);

		// matrix 2
	Numerico_Write (DMX_Values[inicial + 5], 1, 2);
	Numerico_Write (DMX_Values[inicial + 6], 5, 2);
	Numerico_Write (DMX_Values[inicial + 7], 9, 2);
	Numerico_Write (DMX_Values[inicial + 8], 13, 2);
	Numerico_Write (DMX_Values[inicial + 9], 17, 2);

		// matrix 3
	Numerico_Write (DMX_Values[inicial + 10], 1, 3);
	Numerico_Write (DMX_Values[inicial + 11], 5, 3);
	Numerico_Write (DMX_Values[inicial + 12], 9, 3);
	Numerico_Write (DMX_Values[inicial + 13], 13, 3);
	Numerico_Write (DMX_Values[inicial + 14], 17, 3);
	*/
}

/*void GUI_Control_Matrix()
{
	// control en matriz
	int Inicial = 1;
	Canal_Actual = 1;
	
	inicio:

	lcd.clear();
	lcd.setCursor (0, 0);
	lcd.print("c--- Mb  Exi    -");
	lcd.setCursor (7, 0);

	if (Universo_Actual == 0)
	{
		lcd.print("-");
	}
	else
	{
		lcd.print(Universo_Actual);
	}

	Multi_Matrix (Inicial);
	
		// Cursor
	LCD_Col_Pos = 12;		// posicion de cursor
	LCD_Row_Pos = 0;		// posicion e cursor

		// configuracion de cursor
	Cursor_Conf_Clear();	// limpiar array

		// Row 0
	Cursor_Conf[0][4]  = 1;	// Memory
	Cursor_Conf[0][8]  = 1;	// Unit
	Cursor_Conf[0][12] = 1;	// Banco Inicial
	Cursor_Conf[0][16] = 1;	// Banco Final

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
	Banco:

	GUI_Navegar(1, Inicial);
	
	// Acciones
		// Memory
	if (LCD_Col_Pos == 4 &&  LCD_Row_Pos == 0)
	{
		GUI_Memory();
		goto inicio;
	}

		// Control
	if (LCD_Col_Pos == 8 &&  LCD_Row_Pos == 0)
	{
		GUI_Control_Options();
		goto inicio;
	}

		// Banco Inicial
	if (LCD_Col_Pos == 12 && LCD_Row_Pos == 0)
	{
		Num_Row_Pos = 0;
		Num_Col_Pos = 13;
		Num_Val = Inicial;	// para dejar el numero que estaba si no se cambia
		Numerico_Calc(0);
		if (Num_Val > 498)	// limite de matriz
		{
			Num_Val = 498;
		}
		if (Num_Val == 0)	// limite de matriz
		{
			Num_Val = 1;
		}
		Inicial = Num_Val;
		goto inicio;
	}

		// Banco Final
	if (LCD_Col_Pos == 16 && LCD_Row_Pos == 0)
	{
		Num_Row_Pos = 0;
		Num_Col_Pos = 17;
		if (Inicial == 1)
		{
			Num_Val = 15;
		}
		else
		{
			Num_Val = Inicial - 14;	// para dejar el numero que estaba si no se cambia
			Numerico_Calc(0);
		}
		if (Num_Val > 512)			// limite de matriz
		{
			Inicial = 498;
			goto inicio;
		}
		if (Num_Val < 15)			// limite de matriz
		{
			Inicial = 1;
			goto inicio;
		}
		Inicial = Num_Val - 14;
		goto inicio;
	}

		// posicion 1
	if (LCD_Col_Pos == 0 && LCD_Row_Pos == 1)
	{
		Canal_Actual = Inicial;
		goto Salida_DMX;
	}

		// posicion 2
	if (LCD_Col_Pos == 4 && LCD_Row_Pos == 1)
	{
		Canal_Actual = Inicial + 1;
		goto Salida_DMX;
	}

		// posicion 3
	if (LCD_Col_Pos == 8 && LCD_Row_Pos == 1)
	{
		Canal_Actual = Inicial + 2;
		goto Salida_DMX;
	}

		// posicion 4
	if (LCD_Col_Pos == 12 && LCD_Row_Pos == 1)
	{
		Canal_Actual = Inicial + 3;
		goto Salida_DMX;
	}

		// posicion 5
	if (LCD_Col_Pos == 16 && LCD_Row_Pos == 1)
	{
		Canal_Actual = Inicial + 4;
		goto Salida_DMX;
	}

		// posicion 6
	if (LCD_Col_Pos == 0 && LCD_Row_Pos == 2)
	{
		Canal_Actual = Inicial + 5;
		goto Salida_DMX;
	}

		// posicion 7
	if (LCD_Col_Pos == 4 && LCD_Row_Pos == 2)
	{
		Canal_Actual = Inicial + 6;
		goto Salida_DMX;
	}

		// posicion 8
	if (LCD_Col_Pos == 8 && LCD_Row_Pos == 2)
	{
		Canal_Actual = Inicial + 7;
		goto Salida_DMX;
	}

		// posicion 9
	if (LCD_Col_Pos == 12 && LCD_Row_Pos == 2)
	{
		Canal_Actual = Inicial + 8;
		goto Salida_DMX;
	}

		// posicion 10
	if (LCD_Col_Pos == 16 && LCD_Row_Pos == 2)
	{
		Canal_Actual = Inicial + 9;
		goto Salida_DMX;
	}

		// posicion 11
	if (LCD_Col_Pos == 0 && LCD_Row_Pos == 3)
	{
		Canal_Actual = Inicial + 10;
		goto Salida_DMX;
	}

		// posicion 12
	if (LCD_Col_Pos == 4 && LCD_Row_Pos == 3)
	{
		Canal_Actual = Inicial + 11;
		goto Salida_DMX;
	}

		// posicion 13
	if (LCD_Col_Pos == 8 && LCD_Row_Pos == 3)
	{
		Canal_Actual = Inicial + 12;
		goto Salida_DMX;
	}

		// posicion 14
	if (LCD_Col_Pos == 12 && LCD_Row_Pos == 3)
	{
		Canal_Actual = Inicial + 13;
		goto Salida_DMX;
	}

		// posicion 15
	if (LCD_Col_Pos == 16 && LCD_Row_Pos == 3)
	{
		Canal_Actual = Inicial + 14;
		goto Salida_DMX;
	}
	
	Salida_DMX:

	Num_Row_Pos = LCD_Row_Pos;
	Num_Col_Pos = LCD_Col_Pos + 1;
	Num_Val = DMX_Values[Canal_Actual];		// para dejar el numero que estaba si no se cambia

	Numerico_Calc(1);

	if (Num_Val == 612)						// ubicar
	{
		Ubicar();
		Num_Col_Pos = Num_Col_Pos - 4;
	}	

	if (Num_Val == 712)						// analogo
	{
		Encoder_Read(Num_Col_Pos - 2, Num_Row_Pos, 0, 255, 1);		// Encoder_Read(byte col, byte row, long limit_min, long limit_max, byte control)
		Num_Col_Pos = Num_Col_Pos - 4;
		goto Banco;
	}

	if (Num_Val > 255)
	{
		Num_Val = 255;
		Numerico_Write (255, Num_Col_Pos + 2, Num_Row_Pos);
	}

	ArduinoDmx0.TxBuffer[Canal_Actual - 1] = Num_Val;
	DMX_Values[Canal_Actual] = Num_Val;
	goto Banco;
}*/

void GUI_Memory_Init()
{

	inicio:
	
	int salir = 0;
  	lcd.clear ();

  		// Texto
  	lcd.setCursor (0, 0);
  	lcd.print("Initial Memory:");
  	lcd.setCursor (2, 2);
  	lcd.print("Empty");
  	lcd.setCursor (9, 2);
  	lcd.print("Load");
  	lcd.setCursor (15, 2);
  	lcd.print("Clear");

  		// bank
  	lcd.setCursor(18, 0);
  	lcd.print("b");

  	if (Universo_Actual == 0)
  	{
    	lcd.print("-");
  	}
  	else
  	{
    	lcd.print(Universo_Actual);
  	}

  		// borrar datos previos en el indice
	Cursor_Index_Clear();

		// establecer el indice
	Cursor_Index[1] [2] = 1;		// y x 	// Empty
	Cursor_Index[8] [2] = 2;		// y x 	// Load
	Cursor_Index[14][2]	= 3;		// y x 	// Clear

		// navegacion
	Navegar();	// actualiza Cursor_Index_Pos
	
	switch (Cursor_Index_Pos)
	{
		case 1:
			GUI_Control_Options();
			break;
		case 2:
			salir = EEPROM_Load();
    		if (salir == 1)
    		{
      			goto inicio;
    		}
    		GUI_Control_Options();
			break;
		case 3:
			salir = EEPROM_Clear();
    		if (salir == 1)
    		{
      			goto inicio;
    		}
    		//GUI_Control_Options();
			break;
	}
}

int GUI_Memory_Bank(byte Opcion)
{
	// regresa 1 si se selecciona salir, de lo contrario 0
  	// recibe opcion para pintar en la pantalla lo que se selecciono

  	int salir = 0;
  	lcd.clear ();
  	delay (200);	// retardo para no seleccionar inmediatamente la opcion del banco

  		// Texto
  	lcd.setCursor (6, 0);
  	lcd.print("Memory Bank:");
  	lcd.setCursor (1, 1);
  	lcd.print("Bank1  Bank4  Bank7");
  	lcd.setCursor (1, 2);
  	lcd.print("Bank2  Bank5  Bank8");
  	lcd.setCursor (1, 3);
  	lcd.print("Bank3  Bank6  Exit");

  	switch (Opcion)
  	{
    	case 1:
      		lcd.setCursor (1, 0);
      		lcd.print("Save");
      		break;

    	case 2:
      		lcd.setCursor (1, 0);
      		lcd.print("Load");
      		break;

    	case 3:
      		lcd.setCursor (0, 0);
      		lcd.print("Clear");
      		break;
  	}

  		// Universo Actual
  	lcd.setCursor (19, 0);

  	if (Universo_Actual == 0)
  	{
    	lcd.print("-");
  	}
  	else
  	{
    	lcd.print(Universo_Actual);
  	}

 		// borrar datos previos en el indice
	Cursor_Index_Clear();

  		// establecer el indice
  	Cursor_Index[0][1]   = 1;	// Bank 1 	// y x
  	Cursor_Index[0][2]   = 2;  	// Bank 2
  	Cursor_Index[0][3]   = 3;	// Bank 3
  	Cursor_Index[7][1]   = 4;	// Bank 4
  	Cursor_Index[7][2]   = 5;	// Bank 5
  	Cursor_Index[7][3]   = 6;	// Bank 6
  	Cursor_Index[14][1]  = 7;	// Bank 7
  	Cursor_Index[14][2]  = 8;	// Bank 8
  	Cursor_Index[14][3]  = 9;	// Exit
	
	Cursor_Index_Pos = 1;
  	
  	navegacion:

		// iniciar navegacion y evaluar el index seleccionado
	Navegar();	// actualiza Cursor_Index_Pos
  
  	switch (Cursor_Index_Pos)
	{
			// Bank 1
		case 1:
    		Universo_Actual = 1;
   	 		break;
  			// Bank 2
   	 	case 2:
  			Universo_Actual = 2;
    		break;
	  		// Bank 3
	  	case 3:
  			Universo_Actual = 3;
    		break;
    		// Bank 4
	  	case 4:
  			Universo_Actual = 4;
    		break;
    		// Bank 5
	  	case 5:
  			Universo_Actual = 5;
    		break;
    		// Bank 6
	  	case 6:
  			Universo_Actual = 6;
    		break;
  			// Bank 7
	  	case 7:
  			Universo_Actual = 7;
    		break;
    		// Bank 8
	  	case 8:
  			Universo_Actual = 8;
    		break;
  			// Exit
	  	case 9:
  			salir = 1;
  			Cursor_Index_Pos = 1;
  			break;
  	}

  	return salir;
}
/*
void GUI_Memory()
{

	iniciar:

  		// Texto
  	lcd.clear ();
  	lcd.setCursor (0, 0);
  	lcd.print("Memory:          b");

  	if (Universo_Actual == 0)
  	{
    	lcd.print("-");
  	}
  	else
  	{
    	lcd.print(Universo_Actual);
  	}

  	lcd.setCursor (1, 1);
  	lcd.print("Save");
  	lcd.setCursor (1, 2);
  	lcd.print("Load");
  	lcd.setCursor (1, 3);
  	lcd.print("Clear");
  	lcd.setCursor (7, 2);
  	lcd.print("ClearAll");
  	lcd.setCursor (7, 1);
  	lcd.print("BlackOut");
  	lcd.setCursor (16, 3);
  	lcd.print("Exit");
  	lcd.setCursor (7, 3);
  	lcd.print("EmptyRAM");

  		// Cursor
  	LCD_Col_Pos = 0;			// posicion de cursor
  	LCD_Row_Pos = 1;

  		// configuracion de cursor
  	Cursor_Conf_Clear();		// limpiar array

  		// Acciones
  	Cursor_Conf[1][0]  = 1;		// Save
  	Cursor_Conf[2][0]  = 1; 	// Load
  	Cursor_Conf[3][0]  = 1;		// Clear
  	Cursor_Conf[2][6]  = 1;		// Clear All
  	Cursor_Conf[3][6]  = 1;		// Empty RAM
  	Cursor_Conf[1][6]  = 1;		// Black Out
  	Cursor_Conf[3][15] = 1;		// Exit

  		// navegar
	regresa:

  	GUI_Navegar(0, 0);

  	// Acciones
  		// Load
  	if (LCD_Col_Pos == 0 && LCD_Row_Pos == 2)
  	{
    	if (EEPROM_Load() == 1)
    	{
      		goto iniciar;
    	}
    	goto salida;
  	}

  		// Clear
  	if (LCD_Col_Pos == 0 && LCD_Row_Pos == 3)
  	{
    	if (EEPROM_Clear() == 1)
    	{
      		goto iniciar;
    	}
    	goto salida;
  	}

  		// Clear All
  	if (LCD_Col_Pos == 6 && LCD_Row_Pos == 2)
  	{
    	EEPROM_Clear_All();
    	goto salida;
  	}

  		// Save
  	if (LCD_Col_Pos == 0 && LCD_Row_Pos == 1)
  	{
    	if (EEPROM_Save() == 1)
    	{
     		goto iniciar;
    	}
    	goto salida;
  	}

  		// Empty RAM
  	if (LCD_Col_Pos == 6 && LCD_Row_Pos == 3)
  	{
    	EEPROM_Empty();
    	goto salida;
  	}

  		// Black Out
  	if (LCD_Col_Pos == 6 && LCD_Row_Pos == 1)
  	{
    	Black_Out();
    	goto regresa;
  	}

  		// Exit
  	if (LCD_Col_Pos == 15 && LCD_Row_Pos == 3) {}

	salida: {}

}*/
/*
void GUI_Control_Secuencer()
{
  	// secuenciador de bancos guardados en eeprom

  	int Delay_Secuencia 	= 1;
  	int First_Bank 		= 1;
  	int Final_Bank 		= 8;
  	lcd.clear ();

  		// Texto
  	lcd.setCursor (0, 0);
  	lcd.print("Secuencer Banks:  b");

  	if (Universo_Actual == 0)
  	{
    	lcd.print("-");
  	}
  	else
  	{
    	lcd.print(Universo_Actual);
  	}

  	lcd.setCursor (4, 1);
  	lcd.print("Delay 001x100=mS");
  	lcd.setCursor (0, 2);
  	lcd.print("FirstBank 001  Exit");
  	lcd.setCursor (0, 3);
  	lcd.print("FinalBank 008  Start");

  		// Cursor
  	LCD_Col_Pos = 9;			// posicion de cursor
  	LCD_Row_Pos = 1;

  		// configuracion de cursor
  	Cursor_Conf_Clear();		// limpiar array

  		// Acciones
  	Cursor_Conf[1][9]  = 1;		// Delay
  	Cursor_Conf[2][9]  = 1; 	// First Bank
  	Cursor_Conf[3][9]  = 1;		// Final Bank
  	Cursor_Conf[2][14] = 1;		// Control
  	Cursor_Conf[3][14] = 1;		// start

	inicio:

  	lcd.setCursor (15, 3);
  	lcd.print("Start");
  	lcd.noBlink();

  		// navegar
  	GUI_Navegar(0, 0);

  	// Acciones
  		// Delay
  	if (LCD_Col_Pos == 9 && LCD_Row_Pos == 1)
  	{
    	Num_Row_Pos = 1;
    	Num_Col_Pos = 10;
    	Num_Val = Delay_Secuencia;					// para dejar el numero que estaba si no se cambia
    	Numerico_Calc(0);

    	if (Num_Val == 0)
    	{
      		Numerico_Write (1, 10, 1);
      		Delay_Secuencia = 1;
      		Numerico_Write (Delay_Secuencia, 10, 1);
    	}
    	else
    	{
      		Delay_Secuencia = Num_Val;				// por el multiplicador
    	}

    	if (Num_Val > 100)
    	{
      		Delay_Secuencia = 100;
      		Numerico_Write (Delay_Secuencia, 10, 1);
    	}

    	goto inicio;
  	}

  		// First Bank
  	if (LCD_Col_Pos == 9 && LCD_Row_Pos == 2)
  	{
    	Num_Row_Pos = 2;
    	Num_Col_Pos = 10;
    	Num_Val = First_Bank;						// para dejar el numero que estaba si no se cambia
    	Numerico_Calc(0);
    	First_Bank = Num_Val;

    	if (Num_Val == 0)
    	{
      		First_Bank = 1;
      		Numerico_Write (First_Bank, 10, 2);
    	}

    	if (Num_Val > 8)
    	{
      		Numerico_Write (8, 10, 2);
      		First_Bank = 8;
    	}

    	goto inicio;
  	}

  		// Final Bank
  	if (LCD_Col_Pos == 9 && LCD_Row_Pos == 3)
  	{
    	Num_Row_Pos = 3;
    	Num_Col_Pos = 10;
    	Num_Val = Final_Bank; 						// para dejar el numero que estaba si no se cambia
    	Numerico_Calc(0);
    	Final_Bank = Num_Val;

    	if (Num_Val == 0)
    	{
      		Final_Bank = 1;
      		Numerico_Write (Final_Bank, 10, 3);
    	}

    	if (Num_Val > 8)
    	{
      		Numerico_Write (8, 10, 2);
      		Final_Bank = 8;
    	}

    	goto inicio;
  	}

  		// Control
  	if (LCD_Col_Pos == 14 && LCD_Row_Pos == 2)
  	{
    		// restablecer salida dmx como estaba antes de entrar
    	for (int Canal = 0; Canal <= 512; Canal ++)
    	{
      		ArduinoDmx0.TxBuffer[Canal] = DMX_Values[Canal]; 		// salida a DMX
    	}
    	GUI_Control_Options ();
  	}

  		// start
  	if (LCD_Col_Pos == 14 && LCD_Row_Pos == 3)
  	{
    		// validar
    	if (First_Bank == Final_Bank)
    	{
      		First_Bank = 1;
      		Numerico_Write (First_Bank, 10, 2);
      		Final_Bank = 8;
      		Numerico_Write (Final_Bank, 10, 2);
      		goto inicio;
    	}

    		// LCD
    	lcd.setCursor (14, 3);
    	lcd.print("+");
    	lcd.setCursor (15, 3);
    	lcd.print("Stop ");

    		// establecer reversa o adelante
    	byte Adelante_Reversa = 0;								// 0 Adelante, 1 Reversa

    		// adelante
    	if (First_Bank < Final_Bank)
    	{
      		Adelante_Reversa = 0;
    	}

    		// reversa
    	if (First_Bank > Final_Bank)
    	{
      		Adelante_Reversa = 1;
    	}

    		// establecer bancos a secuenciar
    	byte Bancos [9] = {0, 0, 0, 0, 0, 0, 0, 0};

    	if (Adelante_Reversa == 0)
    	{
      		for (byte Bank = 1; Bank <= 8; Bank ++)
      		{
        		if (Bank >= First_Bank && Bank <= Final_Bank)
        		{
          			Bancos[Bank] = 1;
        		}
      		}
    	}

    	if (Adelante_Reversa == 1)
    	{
      		for (byte Bank = 8; Bank >= 1; Bank --)
      		{
        		if (Bank <= First_Bank && Bank >= Final_Bank)
        		{
          			Bancos[Bank] = 1;
        		}
      		}
    	}

    		//Secuenciar
    	byte value = 0;
    	lcd.blink();

    		// adelante
    	if (Adelante_Reversa == 0)
    	{

			contar:

      		for (byte conteo = 1; conteo <= 8; conteo ++)
      		{
        		if (Bancos [conteo] == 1)
        		{
          			lcd.setCursor (19, 0);
          			lcd.print(conteo);
          			lcd.setCursor (19, 3);
          			for (int canal = 0; canal <= 511; canal ++)
          			{
            			switch (conteo)
            			{
              				case 1:
                				value = EEPROM.read(canal);
                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
                				break;

              				case 2:
                				value = EEPROM.read(canal + 512);
                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
                				break;

              				case 3:
                				value = EEPROM.read(canal + 1024);
                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
                				break;

              				case 4:
                				value = EEPROM.read(canal + 1536);
                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
                				break;

              				case 5:
                				value = EEPROM.read(canal + 2048);
                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
                				break;

              				case 6:
                				value = EEPROM.read(canal + 2560);
                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
                				break;

              				case 7:
                				value = EEPROM.read(canal + 3072);
                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
                				break;

              				case 8:
                				value = EEPROM.read(canal + 3584);
                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
                				break;
            			}
          			}

          				//delay
          			long delay_contar = Delay_Secuencia * 100;

          			while (digitalRead(Enc_Center) == HIGH)		// lectura del boton centro
          			{
            			for (long contar = 0; contar <= delay_contar; contar ++)
            			{
              				delay(1);
              				if (digitalRead(Enc_Center) == LOW)
              				{
                				goto salida;
              				}
            			}
            			goto Delay_Salir;
          			}

					salida:

          			delay(500);									// rebote de boton
          			goto inicio;

					Delay_Salir: {}

        		}
      		}
      		goto contar;
    	}

    		// reversa
    	if (Adelante_Reversa == 1)
    	{

			contar_rev:

      		for (byte conteo = 8; conteo >= 1; conteo --)
      		{
        		if (Bancos [conteo] == 1)
        		{
          			lcd.setCursor (19, 0);
          			lcd.print(conteo);
          			lcd.setCursor (19, 3);
          			for (int canal = 0; canal <= 511; canal ++)
          			{
            			switch (conteo)
            			{
              				case 1:
                				value = EEPROM.read(canal);
                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
                				break;

              				case 2:
                				value = EEPROM.read(canal + 512);
                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
                				break;

              				case 3:
                				value = EEPROM.read(canal + 1024);
                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
                				break;

              				case 4:
                				value = EEPROM.read(canal + 1536);
                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
                				break;

              				case 5:
                				value = EEPROM.read(canal + 2048);
                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
                				break;

              				case 6:
                				value = EEPROM.read(canal + 2560);
                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
                				break;

              				case 7:
                				value = EEPROM.read(canal + 3072);
                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
                				break;

              				case 8:
                				value = EEPROM.read(canal + 3584);
                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
                				break;
            			}
          			}

          				//delay
          			long delay_contar = Delay_Secuencia * 100;

          			while (digitalRead(Enc_Center) == HIGH)		// lectura del boton centro
          			{
            			for (long contar = 0; contar <= delay_contar; contar ++)
            			{
              				delay(1);
              				if (digitalRead(Enc_Center) == LOW)
              				{
                				goto salida_rev;
              				}
            			}
            			goto Delay_Salir_Rev;
          			}

					salida_rev:

          			delay(500);									// rebote de boton
          			goto inicio;

					Delay_Salir_Rev: {}

        		}
      		}
      		goto contar_rev;
    	}
  	}
  	goto inicio;
}*/

void Black_Out()
{
  	lcd.setCursor (15, 1);
  	lcd.blink();

  		// limpiar universo
  	for (int Canal = 1; Canal <= 512; Canal ++)
  	{
    	ArduinoDmx0.TxBuffer[Canal - 1] = 0;
  	}

  		// esperar al boton centro para cancelar
  	while (digitalRead(Enc_Center) == HIGH) {}

  	delay(300);		// retardo de rebote de boton

  		// regresar el universo a su lugar
  	for (int Canal = 1; Canal <= 512; Canal ++)
  	{
    	ArduinoDmx0.TxBuffer[Canal - 1] = DMX_Values[Canal];
  	}

  	lcd.setCursor (6, 2);
  	lcd.noBlink();
}
/*
int EEPROM_Save()
{
  	// guarda el universo en la eeprom
  	// regresa 1 si se selecciona exit

  	int cancel = 0;				// regresa 1 si se selecciona salir
  	int bank;					// regresa 1 si se selecciona salir
  	int EEPROM_Add = 0;			// direccion de eeprom para universos
  	bank = GUI_Memory_Bank(1);	// seleccinar banco

  	if (bank == 1)
  	{
    	cancel = 1;
    	goto salida;
  	}

  	lcd.clear ();
  	lcd.setCursor (1, 1);
  	lcd.print ("Memory Saving...");
  	lcd.setCursor (1, 2);
  	lcd.print ("Bank: ");
  	lcd.setCursor (7, 2);
  	lcd.print (Universo_Actual);
  	lcd.setCursor (19, 3);
  	lcd.blink();

  	for (int Canal = 0; Canal <= 511; Canal ++)
  	{
    	// Escritura de universo EEPROM
    	switch (Universo_Actual)
    	{
      		case 1:
        		EEPROM_Add = 0 + Canal;
        		break;

      		case 2:
        		EEPROM_Add = 512 + Canal;
        		break;

      		case 3:
        		EEPROM_Add = 1024 + Canal;
        		break;

      		case 4:
        		EEPROM_Add = 1536 + Canal;
        		break;

      		case 5:
        		EEPROM_Add = 2048 + Canal;
        		break;

      		case 6:
        		EEPROM_Add = 2560 + Canal;
        		break;

      		case 7:
        		EEPROM_Add = 3072 + Canal;
        		break;

      		case 8:
        		EEPROM_Add = 3584 + Canal;
        		if (EEPROM_Add > EEPROM_Limit)
        		{
          			EEPROM_Add = EEPROM_Limit;
        		}
        		break;
    	}

    	EEPROM.write(EEPROM_Add, DMX_Values[Canal + 1]);          		// lectura desde EEPROM
  	}

  	lcd.clear ();
  	lcd.setCursor (3, 1);
  	lcd.print ("Memory Saved!");
  	lcd.setCursor (3, 2);
  	lcd.print ("Bank: ");
  	lcd.print (Universo_Actual);
  	lcd.setCursor (19, 3);
  	delay (1000);
  	lcd.noBlink();

	salida:

  	return cancel;
}*/

int EEPROM_Load()
{
  	// guarda los valores en la eeprom
  	// regresa 1 si se selecciona exit

  	int cancel = 0;				// regresa 1 si se selecciona salir
  	int bank;					// regresa 1 si se selecciona salir
  	int EEPROM_Add = 0;			// seleccion de universo
 	bank = GUI_Memory_Bank(2);	// seleccinar banco

  	if (bank == 1)
  	{
    	cancel = 1;
    	goto salida;
  	}

  	lcd.clear ();

  	for (int Canal = 1; Canal <= 512; Canal ++)
  	{
    		// Escritura de universo EEPROM
    	switch (Universo_Actual)
    	{
      		case 1:
        		EEPROM_Add = 0 + Canal - 1;
        		break;

      		case 2:
        		EEPROM_Add = 512 + Canal - 1;
        		break;

      		case 3:
        		EEPROM_Add = 1024 + Canal - 1;
        		break;

      		case 4:
        		EEPROM_Add = 1536 + Canal - 1;
        		break;

      		case 5:
        		EEPROM_Add = 2048 + Canal - 1;
        		break;

      		case 6:
        		EEPROM_Add = 2560 + Canal - 1;
        		break;

      		case 7:
        		EEPROM_Add = 3072 + Canal - 1;
        		break;

      		case 8:
        		EEPROM_Add = 3584 + Canal - 1;
        		if (EEPROM_Add > EEPROM_Limit)
        		{
          			EEPROM_Add = EEPROM_Limit;
        		}
        		break;
   	 	}

    	DMX_Values[Canal] = EEPROM.read(EEPROM_Add);          	// lectura desde EEPROM
    	ArduinoDmx0.TxBuffer[Canal - 1] = DMX_Values[Canal]; 	// salida a DMX
  	}

	lcd.clear ();
  	lcd.setCursor (3, 1);
  	lcd.print ("Memory Loaded!");
  	lcd.setCursor (3, 2);
  	lcd.print ("Bank: ");
  	lcd.print (Universo_Actual);
  	lcd.setCursor (19, 3);
  	lcd.blink();
  	delay (1000);
  	lcd.noBlink();

	salida:

  	return cancel;
}

void EEPROM_Load_Init()
{
  	// carga los valores de los canales DMX de la eeprom al inicio e inicia el streaming de dmx

  	int EEPROM_Add = 0;
  	Universo_Actual = EEPROM.read(Bank_Init_Add);

  	if (Universo_Actual == 0)
  	{
    	goto salir;
  	}

  	for (int Canal = 1; Canal <= 512; Canal ++)
  	{
    		// Escritura de universo EEPROM
    	switch (Universo_Actual)
    	{
      		case 1:
        		EEPROM_Add = 0 + Canal - 1;
        		break;

      		case 2:
        		EEPROM_Add = 512 + Canal - 1;
        		break;

      		case 3:
        		EEPROM_Add = 1024 + Canal - 1;
        		break;

      		case 4:
        		EEPROM_Add = 1536 + Canal - 1;
        		break;

      		case 5:
        		EEPROM_Add = 2048 + Canal - 1;
        		break;

      		case 6:
        		EEPROM_Add = 2560 + Canal - 1;
        		break;

      		case 7:
       	 		EEPROM_Add = 3072 + Canal - 1;
        		break;

      		case 8:
        		EEPROM_Add = 3584 + Canal - 1;
        		if (EEPROM_Add > EEPROM_Limit)
        		{
          			EEPROM_Add = EEPROM_Limit;
        		}
        		break;
    	}
    	DMX_Values[Canal] = EEPROM.read(EEPROM_Add);          	// lectura desde EEPROM
    	ArduinoDmx0.TxBuffer[Canal - 1] = DMX_Values[Canal]; 	// salida a DMX
  	}

  	lcd.clear ();
  	lcd.setCursor (3, 1);
  	lcd.print ("Memory Loaded!");
  	lcd.setCursor (3, 2);
  	lcd.print ("Bank: ");
  	lcd.print (Universo_Actual);
  	lcd.setCursor (10, 2);
  	lcd.blink();
  	delay (2000);
  	lcd.noBlink();

	salir: {}

}

void EEPROM_Empty()
{
  	// solo borra la ram
  	// no hay retorno al menu anterior

  	lcd.clear ();

  	for (int Canal = 1; Canal <= 512; Canal ++)
  	{
    	DMX_Values[Canal] = 0;          		// lectura desde EEPROM
    	ArduinoDmx0.TxBuffer[Canal - 1] = 0; 	// salida a DMX
  	}

  	lcd.clear ();
  	lcd.setCursor (3, 1);
  	lcd.print ("Memory Emptied!");
  	lcd.setCursor (3, 2);
  	lcd.print ("Bank: RAM");
  	lcd.setCursor (19, 3);
  	lcd.blink();
  	delay (1000);
  	lcd.noBlink();
}

int EEPROM_Clear()
{
  	// Pone en ceros la memoria EEPROM
  	// regresa 1 si se selecciona exit

  	int cancel = 0;				// regresa 1 si se selecciona salir
  	int bank;					// regresa 1 si se selecciona salir
  	int EEPROM_Add = 0;			// direccion de eeprom para universos
  	bank = GUI_Memory_Bank(3);	// seleccinar banco

  	if (bank == 1)				// si se selecciono salir
  	{
    	cancel = 1;
    	goto salida;
  	}

  	lcd.clear ();
  	lcd.setCursor (1, 1);
  	lcd.print ("Memory Cleaning...");
  	lcd.setCursor (1, 2);
  	lcd.print ("Bank: ");
  	lcd.setCursor (7, 2);
  	lcd.print (Universo_Actual);
  	lcd.setCursor (19, 3);
  	lcd.blink();

  	for (int Canal = 0; Canal <= 511; Canal ++)
  	{
    	DMX_Values[Canal] = 0;          		// lectura desde EEPROM
    	ArduinoDmx0.TxBuffer[Canal] = 0; 		// salida a DMX
    		// Escritura de universo EEPROM
    	switch (Universo_Actual)
    	{
      		case 1:
        		EEPROM_Add = 0 + Canal;
        		break;

      		case 2:
        		EEPROM_Add = 512 + Canal;
        		break;

      		case 3:
        		EEPROM_Add = 1024 + Canal;
        		break;

      		case 4:
        		EEPROM_Add = 1536 + Canal;
        		break;

      		case 5:
        		EEPROM_Add = 2048 + Canal;
        		break;

      		case 6:
        		EEPROM_Add = 2560 + Canal;
        		break;

      		case 7:
        		EEPROM_Add = 3072 + Canal;
        		break;

      		case 8:
       			EEPROM_Add = 3584 + Canal;
        		if (EEPROM_Add > EEPROM_Limit)
        		{
          			EEPROM_Add = EEPROM_Limit;
        		}
        		break;
    	}

    	EEPROM.write (EEPROM_Add, 0);		// escritura EEPROM
  	}
  	lcd.clear ();
  	lcd.setCursor (2, 1);
  	lcd.print ("Memory Cleaned!");
  	lcd.setCursor (2, 2);
  	lcd.print ("Bank: ");
  	lcd.print (Universo_Actual);
  	lcd.setCursor (19, 3);
  	delay (1000);
  	lcd.noBlink();

	salida:

  	return cancel;
}

void EEPROM_Clear_All()
{
  	// Pone en ceros la memoria EEPROM toda
  	lcd.clear ();
  	lcd.setCursor (1, 1);
  	lcd.print ("All");
  	lcd.setCursor (1, 2);
  	lcd.print ("Memory Cleaning...");
  	lcd.setCursor (19, 2);
  	lcd.blink();

  	for (int Canal = 0; Canal <= EEPROM_Limit; Canal ++)
  	{
    	EEPROM.write (Canal, 0);				// escritura EEPROM
    	if (Canal <= 511)
    	{
     	 	DMX_Values[Canal + 1] = 0;
      		ArduinoDmx0.TxBuffer[Canal] = 0; 	// salida a DMX
    	}
  	}

  	lcd.clear ();
  	lcd.noBlink();
  	lcd.setCursor (2, 2);
  	lcd.print ("Memory Cleaned!");
  	lcd.setCursor (2, 1);
  	lcd.print ("All");
  	Universo_Actual = 0;
  	delay (1000);
}

void GUI_Control_Options()
{

	inicio:

  		// LCD
  	lcd.clear ();
  	lcd.setCursor (18, 0);
  	lcd.print ("b");

  	if (Universo_Actual == 0)
  	{
    	lcd.print ("-");
  	}
  	else
  	{
    	lcd.print (Universo_Actual);
  	}

  	lcd.setCursor (2, 0);
  	lcd.print ("Convert");
  	lcd.setCursor (2, 1);
  	lcd.print ("Unitary");
	lcd.setCursor (2, 2);
	lcd.print ("Matrix");
	lcd.setCursor (2, 3);
	lcd.print ("Chaser");
	lcd.setCursor (11, 3);
	lcd.print ("Multiply");
	lcd.setCursor (11, 0);
	lcd.print ("Config");
	lcd.setCursor (11, 2);
	lcd.print ("Secuencer");
	lcd.setCursor (11, 1);
	lcd.print ("Memory");

  		// borrar datos previos en el indice
	Cursor_Index_Clear();

  		// establecer el indice
  	Cursor_Index[1][1]   = 2;	// Unitary		// y x
  	Cursor_Index[1][2]   = 3; 	// Matrix
  	Cursor_Index[1][3]   = 4; 	// Chaser
  	Cursor_Index[10][3]  = 8; 	// Multiply
  	Cursor_Index[10][0]  = 5; 	// Config
  	Cursor_Index[10][2]  = 7; 	// Secuencer
  	Cursor_Index[10][1]  = 6; 	// Memory
  	Cursor_Index[1][0]   = 1; 	// Convert

  	navegacion:

		// iniciar navegacion y evaluar el index seleccionado
	Navegar();	// actualiza Cursor_Index_Pos

  	switch (Cursor_Index_Pos)
	{
			// Convert
		case 1:
			// convert _______________________________________________________
			break;
			// Unitary
		case 2:
			//GUI_Control_Unit();
			break;
			// Matrix
		case 3:
			//GUI_Control_Matrix();
			break;
			// Chaser
		case 4:
			//GUI_Control_Chaser();
			break;
			// Config
		case 5:
			//GUI_Config();
			break;
			// Memory
		case 6:
			//GUI_Memory();
    		goto inicio;
			break;
			// Secuencer
		case 7:
			//GUI_Control_Secuencer();
			break;
			// Multiply
		case 8:
			//GUI_Control_Multiply();
			break;
	}
}

/*void GUI_Convert()
{
	int valor 			= 0;								// aqui el valor a calcular
	int valor_temp		= 0;								// aqui el valor temporal para las cuentas
	int valor_resto 	= 0;								// aqui el valor del resto de la divicion
	int valor_Bin [10]	= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};	// aqui el valor descompuesto en binario
	lcd.clear ();
	lcd.setCursor (0, 0);
	lcd.print ("Bin: OOOOOOOOO I=On");
	lcd.setCursor (5, 1);
	lcd.print ("124813612 O=Off");
	lcd.setCursor (9, 2);
	lcd.print ("62425");
	lcd.setCursor (0, 3);
	lcd.print ("Dec: 000    86  Exit");

		// Cursor
	LCD_Col_Pos = 4;			// posicion de cursor
	LCD_Row_Pos = 3;			// posicion e cursor

		// configuracion de cursor
	Cursor_Conf_Clear();		// limpiar array

		// Cursores
	Cursor_Conf[0][4]  	= 1;	// Bin
	Cursor_Conf[3][4]  	= 1;	// Dec
	Cursor_Conf[3][15]  = 1;	// Exit

		//Navegacion:
	calc:
	GUI_Navegar(0, 0);

	// Acciones
		// Exit
	if (LCD_Col_Pos == 15 && LCD_Row_Pos == 3)
	{
		GUI_Control_Options();
	}

		// Binario a decimal
	if (LCD_Col_Pos == 4 && LCD_Row_Pos == 0)
	{
		// boton de centro para salir
		// boton de lados para navegar
		// boton arriba abajo para cambiar valor
		byte cursor 		= 5;		// posicion de cursor
		int boton_retardo 	= 250;		// retardo de boton para estabilidad
		byte calcular 		= 0;		// calcular binario a decimal
		byte calcular_val	= 0;		// valor a meter a la matriz para calcular
		lcd.blink();
		lcd.setCursor (5, 0);

		while (digitalRead(Enc_Center) == HIGH)	// salida
		{
			if (digitalRead(Boton_Right) == LOW)
			{
				delay(boton_retardo);	// esperar a estabilidad
				cursor = cursor + 1;
				if (cursor > 13)
			{
			cursor = 5;			// regresar al principio
        }
        lcd.setCursor (cursor, 0);
    }

    if (digitalRead(Boton_Left) == LOW)
    {
		delay(boton_retardo);	// esperar a estabilidad
        cursor = cursor - 1;
        if (cursor < 5)
        {
          cursor = 13;		// regresar al final
        }
        lcd.setCursor (cursor, 0);
    }

    if (digitalRead(Boton_Up) == LOW)
    {
        delay(boton_retardo);	// esperar a estabilidad
        lcd.print ("I");
        lcd.setCursor (cursor, 0);
        calcular_val 	= 1;
        calcular 		= 1;
    }

    if (digitalRead(Boton_Down) == LOW)
    {
        delay(boton_retardo);	// esperar a estabilidad
        lcd.print ("O");
        lcd.setCursor (cursor, 0);
        calcular_val	= 0;
        calcular 		= 1;
    }

    if (calcular == 1)
    {
        calcular = 0;
        // agregar a la matriz el valor nuevo
        switch (cursor)
        {
			case 5:		// 1
				valor_Bin [1] = calcular_val;
				break;

			case 6:		// 2
				valor_Bin [2] = calcular_val;
				break;

			case 7:		// 4
				valor_Bin [3] = calcular_val;
				break;

			case 8:		// 8
				valor_Bin [4] = calcular_val;
				break;

			case 9:		// 16
				valor_Bin [5] = calcular_val;
				break;

			case 10:	// 32
				valor_Bin [6] = calcular_val;
				break;

			case 11:	// 64
				valor_Bin [7] = calcular_val;
				break;

			case 12:	// 128
				valor_Bin [8] = calcular_val;
				break;

			case 13:	// 256
				valor_Bin [9] = calcular_val;
				break;

		}

        	// calcular valor de binario a decimal
        valor = 0;
        if (valor_Bin [1] == 1)
        {
			valor = valor + 1;
        }

        if (valor_Bin [2] == 1)
        {
			valor = valor + 2;
        }

        if (valor_Bin [3] == 1)
        {
			
			valor = valor + 4;
        }

        if (valor_Bin [4] == 1)
        {
			valor = valor + 8;
        }

        if (valor_Bin [5] == 1)
        {
			valor = valor + 16;
        }

        if (valor_Bin [6] == 1)
        {
			valor = valor + 32;
        }

        if (valor_Bin [7] == 1)
        {
			valor = valor + 64;
        }

        if (valor_Bin [8] == 1)
        {
			valor = valor + 128;
        }

        if (valor_Bin [9] == 1)
        {
			valor = valor + 256;
        }

        	// escribir el valor en decimal
        Numerico_Write (valor, 5, 3);
        lcd.setCursor (cursor, 0);
    }
   }
    delay(200);		// esperar a estabilidad
    lcd.noBlink();
    goto calc;
  }
  	// Decimal a binario
  if (LCD_Col_Pos == 4 && LCD_Row_Pos == 3)
  {
    Num_Row_Pos = 3;
    Num_Col_Pos = 5;
    Numerico_Calc (0);

	if (Num_Val == 712)
	{
		Encoder_Read (5, 3, 0, 511, 8);		// Encoder_Read(byte col, byte row, long limit_min, long limit_max, byte control)
	}

    if (Num_Val > 511)
    {
      Num_Val = 511;				// corregir valor en pantalla
      lcd.setCursor (5, 3);
      lcd.print ("511");
    }

    valor = Num_Val;

    	// escribir 00000000 en el valor binario para borrar el anterior
    lcd.setCursor (5, 0);
    lcd.print ("OOOOOOOOO");
    lcd.setCursor (5, 0);

    	// calcular binario
    valor_temp = valor;
    for (byte pos = 9; pos >= 1; pos --)
    {
      valor_resto 		= valor_temp % 2;
      valor_temp  		= valor_temp / 2;
      valor_Bin [pos] 	= valor_resto;
      if (valor_resto == 0)
      {
        lcd.print ("O");
      }
      else
      {
        lcd.print ("I");
      }
    }
    goto calc;
  }
}*/
/*
void GUI_Config()
{
	Inicio:

	byte Back_Light_Value 	= EEPROM.read(BackLight_Add);
	byte Contrast_Value 	= EEPROM.read(Contrast_Add);
	byte Bank_Init_Value	= EEPROM.read(Bank_Init_Add);
	byte Key_Light_Value	= EEPROM.read(Key_Light_Add);

		// GUI
	lcd.clear ();
	lcd.setCursor (0, 0);
	lcd.print (" KeyLight:");
	Numerico_Write(Key_Light_Value, 11, 0);
	lcd.setCursor (15, 2);
	lcd.print ("About");
	lcd.setCursor (0, 1);
	lcd.print ("BackLight:");
	Numerico_Write(Back_Light_Value, 11, 1);
	lcd.setCursor (1, 2);
	lcd.print ("Contrast:");
	Numerico_Write(Contrast_Value, 11, 2);
	lcd.setCursor (15, 3);
	lcd.print ("Exit");

		// Bank
	lcd.setCursor (1, 3);
	lcd.print ("BankInit:");

	if (Bank_Init_Value > 8 || Bank_Init_Value < 1)
	{
		lcd.setCursor (11, 3);
		lcd.print ("---");
	}
	else
	{
		Numerico_Write(Bank_Init_Value, 11, 3);
	}

		// Cursor
	LCD_Col_Pos = 10;			// posicion de cursor
	LCD_Row_Pos = 1;			// posicion de cursor

		// configuracion de cursor
	Cursor_Conf_Clear();		// limpiar array

		// Cursores
	Cursor_Conf[1][10]  = 1;	// Back Light Value
	Cursor_Conf[2][10]  = 1;	// Contrast Value
	Cursor_Conf[3][10]  = 1;	// Bank init Value
	Cursor_Conf[0][10]  = 1;	// Key Light Value
	Cursor_Conf[3][14]  = 1;	// Exit
	Cursor_Conf[2][14]  = 1;	// About
	Navegacion:
	GUI_Navegar(0, 0);

	// Acciones
		//Back Light Value
	if (LCD_Col_Pos == 10 && LCD_Row_Pos == 1)
	{
		Num_Row_Pos = 1;
		Num_Col_Pos = 11;
		Numerico_Calc (1);

		if (Num_Val == 712)
		{
			digitalWrite(Boton_Array_3, LOW);			// lectura linea 3
			while (digitalRead(Boton_Array_D) == HIGH) 	//&& digitalRead(Boton_Center) == HIGH) // enter y center para paro
			{
				Encoder_Read (11, 1, 0, 255, 3);		// Encoder_Read(byte col, byte row, long limit_min, long limit_max, byte control)
				goto salida;
				
			}
			digitalWrite(Boton_Array_3, HIGH);			// lectura linea 3
			delay(300);									// retraso para center
		}

		if (Num_Val > 255)
		{
			Num_Val = 255;
			Numerico_Write (255, 11, 1);
		}
		analogWrite(Back_Light_PWM, Num_Val);

		salida:

			// mecanismo para on off Enable
		if (Num_Val == 0)
		{
			Light_On_Off = 0;
		}

		if (Num_Val > 0)
		{
			Light_On_Off = 1;
		}

		EEPROM.write(BackLight_Add, Num_Val);			// guardar valor nuevo
		goto Navegacion;
	}

		//Key Light Value
	if (LCD_Col_Pos == 10 && LCD_Row_Pos == 0)
	{
		Num_Row_Pos = 0;
		Num_Col_Pos = 11;
		Numerico_Calc (1);
		
		if (Num_Val == 712)
		{
			digitalWrite(Boton_Array_3, LOW);			// lectura linea 3
			while (digitalRead(Boton_Array_D) == HIGH && digitalRead(Enc_Center) == HIGH) // enter y center para paro
			{
				Encoder_Read (11, 0, 0, 255, 4);		// Encoder_Read(byte col, byte row, long limit_min, long limit_max, byte control)
				goto salida_key;
			}
			digitalWrite(Boton_Array_3, HIGH);			// lectura linea 3
			delay(300);									// retraso para center
			goto salida_key;
		}

		if (Num_Val > 255)
		{
			Num_Val = 255;
			Numerico_Write (255, 11, 0);
		}

		analogWrite(Key_Light_PWM, Num_Val);

		salida_key:

		// mecanismo para on off Enable
		if (Num_Val == 0)
		{
			Light_On_Off = 0;
		}

		if (Num_Val > 0)
		{
			Light_On_Off = 1;
		}

		EEPROM.write(Key_Light_Add, Num_Val);	// guardar valor nuevo
		goto Navegacion;
	}

		//Contrast Value
	if (LCD_Col_Pos == 10 && LCD_Row_Pos == 2)
	{
		Num_Row_Pos = 2;
		Num_Col_Pos = 11;
		Numerico_Calc (1);

			// encoder
		if (Num_Val == 712)
		{
			Encoder_Read (11, 2, 0, 255, 2);	// Encoder_Read(byte col, byte row, long limit_min, long limit_max, byte control)
			goto salir;
		}

			// teclado
		if (Num_Val > 255)
		{
			Num_Val = 255;
			Numerico_Write (255, 11, 2);
		}

		if (Num_Val < 150)
		{
			Num_Val = 150;						// limite menor de contraste LCD
			Numerico_Write (150, 11, 2);
		}

		analogWrite(Contrast_PWM, Num_Val);

		salir:

		EEPROM.write(Contrast_Add, Num_Val);	// guardar valor nuevo
		goto Navegacion;
	}

		//Bank init Value
	if (LCD_Col_Pos == 10 && LCD_Row_Pos == 3)
	{
		Num_Row_Pos = 3;
		Num_Col_Pos = 11;
		Numerico_Calc (1);
		if (Num_Val == 712)
		{
			Encoder_Read (11, 3, 0, 8, 7);		// Encoder_Read(byte col, byte row, long limit_min, long limit_max, byte control)
			if (EEPROM.read(Bank_Init_Add) == 0)
			{
				lcd.setCursor (11, 3);
				lcd.print("---");
			}
			goto Navegacion;
		}

		if (Num_Val > 8)
		{
			Num_Val = 8;
			Numerico_Write (8, 11, 3);
		}

		if (Num_Val == 0)
		{
			lcd.setCursor (11, 3);
			lcd.print("---");
		}

		EEPROM.write(Bank_Init_Add, Num_Val);	// guardar valor nuevo
		goto Navegacion;
	}
		// Exit
	if (LCD_Col_Pos == 14 && LCD_Row_Pos == 3)
	{
		GUI_Control_Options();
		goto Navegacion;
	}

		// About
	if (LCD_Col_Pos == 14 && LCD_Row_Pos == 2)
	{
		GUI_About();
		GUI_Licence();
		goto Inicio;
	}

	goto Navegacion;
}*/
/*
void GUI_Control_Multiply()
{
  	int  First_Channel = 1;
  	long Multiply 	   = 0;
  	long Quantity 	   = 0;
  	int  Value         = 255;

	iniciar:

  		// LCD
  	lcd.clear ();
  	lcd.setCursor (0, 0);
  	lcd.print ("b  Value");
  	lcd.setCursor (1, 0);

  	if (Universo_Actual == 0)
  	{
    	lcd.print("-");
  	}
  	else
  	{
    	lcd.print(Universo_Actual);
  	}

  	lcd.setCursor (0, 1);
  	lcd.print ("First CH      Exit");
  	lcd.setCursor (0, 2);
  	lcd.print ("Multiply      Memory");
  	lcd.setCursor (0, 3);
  	lcd.print ("Quantity      Apply");
  	Numerico_Write (Value, 		   9, 0);
  	Numerico_Write (First_Channel, 9, 1);
  	Numerico_Write (Multiply,      9, 2);
  	Numerico_Write (Quantity,      9, 3);

  		// Cursor
  	LCD_Col_Pos = 8;			// posicion de cursor
  	LCD_Row_Pos = 0;

	Siguiente:

  		// configuracion de cursor
  	Cursor_Conf_Clear();		// limpiar array

  		// Acciones
  	Cursor_Conf[1][8]   = 1;	// first Channel
  	Cursor_Conf[3][8]   = 1; 	// quantity
  	Cursor_Conf[2][8]   = 1; 	// Multiply
  	Cursor_Conf[1][13]  = 1; 	// control
  	Cursor_Conf[2][13]  = 1; 	// Memory
  	Cursor_Conf[3][13]  = 1; 	// apply
  	Cursor_Conf[0][8]   = 1; 	// value

  		// navegar
  	GUI_Navegar(0, 0);

  	// Acciones
  		// Exit
  	if (LCD_Col_Pos == 13 && LCD_Row_Pos == 1)
  	{
    	GUI_Control_Options();
  	}

  		// Memory
  	if (LCD_Col_Pos == 13 && LCD_Row_Pos == 2)
  	{
    	GUI_Memory();
    	goto iniciar;
  	}

  		// Apply
  	if (LCD_Col_Pos == 13 && LCD_Row_Pos == 3)
  	{
    		// Validar datos
    	long valid = Multiply * Quantity;
    
    	if (valid > 512)	// si no es valido
    	{
      		lcd.setCursor(13, 0);
      		lcd.print("Error! ");
      		goto Siguiente;
    	}

    		// calcular
    	lcd.setCursor(13, 0);
    	lcd.print("       ");
    	lcd.setCursor(14, 3);
    	lcd.print("Calc..");
    	long canal;

    	for (long conteo = 1; conteo <= Quantity; conteo++)
    	{
      		if (conteo == 1)
      		{
        		canal = First_Channel;
      		}

      		if (conteo != 1)
      		{
        		canal = canal + Multiply;
      		}

      		if (canal > 512)
      		{
        		canal = canal - Multiply;
       	 		conteo = Quantity;
      		}

      		lcd.setCursor(17, 0);
      		lcd.print(canal);
      		delay (5);
      		ArduinoDmx0.TxBuffer[canal - 1] = Value;
      		DMX_Values[canal] = Value;
    	}

    	lcd.setCursor(13, 0);
    	lcd.print("Ok!");
    	lcd.setCursor(14, 3);
    	lcd.print("Apply ");
    	goto Siguiente;
  	}

  		// First Channel
  	if (LCD_Col_Pos == 8 && LCD_Row_Pos == 1)
  	{
    	Num_Row_Pos = 1;
    	Num_Col_Pos = 9;
    	Num_Val = First_Channel;	// para dejar el numero que estaba si no se cambia
    	Numerico_Calc(0);
    	First_Channel = Num_Val;
    
    	if (First_Channel == 0)
    	{
      		First_Channel = 1;
      		Numerico_Write (First_Channel, 9, 1);
    	}
    
    	if (First_Channel > 512)
    	{
      		First_Channel = 512;
      		Numerico_Write (First_Channel, 9, 1);
    	}
  	}

  		// Multiply
  	if (LCD_Col_Pos == 8 && LCD_Row_Pos == 2)
  	{
    	Num_Row_Pos = 2;
   	 	Num_Col_Pos = 9;
    	Num_Val = Multiply;			// para dejar el numero que estaba si no se cambia
    	Numerico_Calc(0);
    	Multiply = Num_Val;
    	if (Multiply == 0)
    	{
      		Multiply = 1;
      		Numerico_Write (Multiply, 9, 2);
    	}
    
    	if (Multiply > 512)
    	{
      		Multiply = 512;
      		Numerico_Write (Multiply, 9, 2);
    	}
  	}

  		// Quantity
  	if (LCD_Col_Pos == 8 && LCD_Row_Pos == 3)
  	{
    	Num_Row_Pos = 3;
    	Num_Col_Pos = 9;
    	Num_Val = Quantity;			// para dejar el numero que estaba si no se cambia
    	Numerico_Calc(0);
    	Quantity = Num_Val;
    
    	if (Quantity == 0)
    	{
      		Quantity = 1;
      		Numerico_Write (Quantity, 9, 3);
    	}
    
    	if (Quantity > 512)
    	{
      		Quantity = 512;
      		Numerico_Write (Quantity, 9, 3);
    	}
  	}

  		// Value
  	if (LCD_Col_Pos == 8 && LCD_Row_Pos == 0)
  	{
    	Num_Row_Pos = 0;
    	Num_Col_Pos = 9;
    	Num_Val = Value;			// para dejar el numero que estaba si no se cambia
    	Numerico_Calc(1);
    	Value = Num_Val;

    	if (Value > 255)
    	{
      		Value = 255;
      		Numerico_Write (Value, 9, 0);
    	}
  	}

  	goto Siguiente;
}*/
/*
void GUI_Control_Chaser()
{
  	long Delay     = 1;
  	long First 	 = 1;
  	long Final 	 = 0;

  		// LCD
  	lcd.clear ();
  	lcd.setCursor (0, 0);
  	lcd.print ("ChaserCH ---");
  	lcd.setCursor (3, 1);
  	lcd.print ("Delay    x10=mS");
  	lcd.setCursor (0, 2);
  	lcd.print ("First CH       Exit");
  	lcd.setCursor (0, 3);
  	lcd.print ("Final CH       Start");
  	Numerico_Write (Delay, 9, 1);
  	Numerico_Write (First, 9, 2);
  	Numerico_Write (Final, 9, 3);

  		// Cursor
  	LCD_Col_Pos = 8;			// posicion de cursor
  	LCD_Row_Pos = 1;

	Siguiente:

  		// configuracion de cursor
  	Cursor_Conf_Clear();		// limpiar array

  		// Acciones
  	Cursor_Conf[1][8]   = 1;	// Delay
  	Cursor_Conf[2][8]   = 1; 	// First
  	Cursor_Conf[3][8]   = 1; 	// Final
  	Cursor_Conf[2][14]  = 1; 	// control
  	Cursor_Conf[3][14]  = 1; 	// Start

  		// navegar
  	GUI_Navegar(0, 0);

  	// Acciones
  		// Control
  	if (LCD_Col_Pos == 14 && LCD_Row_Pos == 2)
  	{
    	// regresar el universo a su lugar
    	for (int Canal = 1; Canal <= 512; Canal ++)
    	{
      		ArduinoDmx0.TxBuffer[Canal - 1] = DMX_Values[Canal];
    	}
    	GUI_Control_Options();
  	}

  		// Start
  	if (LCD_Col_Pos == 14 && LCD_Row_Pos == 3)
  	{
    	long ciclo_longitud = 1300;						// numero multiplicador aprox para 1 seg
    	long ciclo 			= 0;
    	long Delay_Cont		= 0;
    	int  canal 			= First;
    	lcd.setCursor(15, 3);
    	lcd.print("Stop ");
    	lcd.blink();

    		// borrar canales previos
    	for (int Canales = 0; Canales <= 512; Canales ++)
    	{	
     	 	ArduinoDmx0.TxBuffer[Canales] = 0; 			// salida a DMX
    	}

    	while (digitalRead(Enc_Center) == HIGH)			// lectura del boton centro
    	{
      		ciclo = ciclo + 1;
      		if (ciclo == ciclo_longitud)
      		{
        		Delay_Cont = Delay_Cont + 1;
        		if (Delay_Cont == Delay)
        		{
          			if (canal > Final)
          			{
            			canal = First;
          			}
          			Numerico_Write (canal, 9, 0);
          			lcd.setCursor(19, 3);
          
          				// apagar lo anterior
          			for (long contar = First; contar <= Final; contar ++)
          			{
            			ArduinoDmx0.TxBuffer[contar - 1] = 0;
          			}
          				// encender el siguiente
          			ArduinoDmx0.TxBuffer[canal - 1] = 255;
          			Delay_Cont = 0;
          			canal = canal + 1;
        		}
        		ciclo = 0;
      		}
    	}
    	lcd.noBlink();
    	lcd.setCursor(15, 3);
    	lcd.print("Start");
    	delay (300); 		// evita que le gane la descarga del capacitor
    	goto Siguiente;
  	}

  		// Delay
  	if (LCD_Col_Pos == 8 && LCD_Row_Pos == 1)
  	{
    	Num_Row_Pos = 1;
    	Num_Col_Pos = 9;
    	Num_Val = Delay;	// para dejar el numero que estaba si no se cambia
    	Numerico_Calc(0);
    	Delay = Num_Val;
  	}

  		// First
  	if (LCD_Col_Pos == 8 && LCD_Row_Pos == 2)
  	{
    	Num_Row_Pos = 2;
    	Num_Col_Pos = 9;
    	Num_Val = First;	// para dejar el numero que estaba si no se cambia
    	Numerico_Calc(0);
    	First = Num_Val;

    	if (First == 0)
    	{
      		First = 1;
      		Numerico_Write (First, 9, 2);
    	}

    	if (First > 512)
    	{
      		First = 512;
      		Numerico_Write (First, 9, 2);
    	}
  	}

  		// Final
  	if (LCD_Col_Pos == 8 && LCD_Row_Pos == 3)
  	{
    	Num_Row_Pos = 3;
    	Num_Col_Pos = 9;
    	Num_Val = Final;	// para dejar el numero que estaba si no se cambia
    	Numerico_Calc(0);
    	Final = Num_Val;

    	if (Final == 0)
    	{
      		Final = 1;
      		Numerico_Write (Final, 9, 3);
    	}

    	if (Final > 512)
    	{
      		Final = 512;
      		Numerico_Write (Final, 9, 3);
    	}
  	}
  	goto Siguiente;
}*/
/*
void GUI_Control_Unit()
{

	Inicio:

  	Canal_Actual = 1;

  		// GUI
  	lcd.clear ();
  	lcd.setCursor (0, 0);
  	lcd.print ("Unitary Control:  b");

  	if (Universo_Actual == 0)
  	{
    	lcd.print("-");
  	}
  	else
  	{
    	lcd.print(Universo_Actual);
  	}

  	lcd.setCursor (14, 2);
  	lcd.print ("Exit");
  	lcd.setCursor (14, 3);
  	lcd.print ("Memory");
  	lcd.setCursor (0, 2);
  	lcd.print ("Channel: 001");
  	lcd.setCursor (2, 3);
  	lcd.print ("Value:");
  	Numerico_Write(DMX_Values[1], 9, 3);
  	lcd.setCursor (0, 1);
  	lcd.print ("c002=v");
  	Numerico_Write(DMX_Values[2], 6, 1);
  	lcd.setCursor (11, 1);
  	lcd.print ("c003=v");
  	Numerico_Write(DMX_Values[3], 17, 1);

  		// Cursor
  	LCD_Col_Pos = 8;			// posicion de cursor
  	LCD_Row_Pos = 2;			// posicion e cursor

  		// configuracion de cursor
  	Cursor_Conf_Clear();		// limpiar array

  		// Cursores
  	Cursor_Conf[2][8]  = 1;		// Channel
  	Cursor_Conf[3][8]  = 1;		// Value
  	Cursor_Conf[2][13] = 1; 	// Control
  	Cursor_Conf[3][13] = 1;		// Memory

  		// navegar
	Navegacion:

  	GUI_Navegar(0, 0);

  	// Acciones
  		//Channel
  	if (LCD_Col_Pos == 8 && LCD_Row_Pos == 2)
  	{
    	Numerico_Write(Canal_Actual, 9, 2);
    	Num_Row_Pos = 2;
    	Num_Col_Pos = 9;
    	Num_Val = Canal_Actual;		// para dejar el numero que estaba si no se cambia
    	Numerico_Calc (0);

    	if (Num_Val > 512)
    	{
     	 	Num_Val = 512;
      		Numerico_Write (512, 9, 2);
    	}

    	if (Num_Val < 1)
    	{
     	 	Num_Val = 1;
      		Numerico_Write (1, 9, 2);
    	}

    		// mostrar valor actual del canal
    	Canal_Actual = Num_Val;
    	Numerico_Write(DMX_Values[Canal_Actual], 9, 3);

    		// mostrar anterior y siguiente
    	if (Canal_Actual == 1)
    	{
      		Numerico_Write(2, 1, 1);
      		Numerico_Write(DMX_Values[2], 6, 1);
      		Numerico_Write(3, 12, 1);
      		Numerico_Write(DMX_Values[3], 17, 1);
    	}

    	if (Canal_Actual == 512)
    	{
      		Numerico_Write(510, 1, 1);
      		Numerico_Write(DMX_Values[510], 6, 1);
      		Numerico_Write(511, 12, 1);
      		Numerico_Write(DMX_Values[511], 17, 1);
   	 	}

    	if (Canal_Actual > 1 && Canal_Actual < 512)
    	{
      		Numerico_Write(Canal_Actual - 1, 1, 1);
      		Numerico_Write(DMX_Values[Canal_Actual - 1], 6, 1);
      		Numerico_Write(Canal_Actual + 1, 12, 1);
      		Numerico_Write(DMX_Values[Canal_Actual + 1], 17, 1);
    	}
  	}

  		// Value
  	if (LCD_Col_Pos == 8 && LCD_Row_Pos == 3)
  	{
    	Num_Row_Pos = 3;
    	Num_Col_Pos = 9;
    	Num_Val = DMX_Values[Canal_Actual];		// para dejar el numero que estaba si no se cambia
    	Numerico_Calc (1);

    	if (Num_Val == 612)						// ubicar
    	{
      		Ubicar();
    	}

    	if (Num_Val == 712)						// analogo
    	{
      		Encoder_Read(9, 3, 0, 255, 1);		// Encoder_Read(byte col, byte row, long limit_min, long limit_max, byte control)
      		goto Navegacion;
    	}

    	if (Num_Val > 255)
    	{
      		Num_Val = 255;
      		Numerico_Write (255, 9, 3);
    	}

    		// Escribr valor en dmx
    	ArduinoDmx0.TxBuffer[Canal_Actual - 1] = Num_Val;
    	DMX_Values[Canal_Actual] = Num_Val;
    	goto Navegacion;
  	}

  		// Memory
  	if (LCD_Col_Pos == 13 && LCD_Row_Pos == 3)
  	{
    	GUI_Memory();
    	goto Inicio;
  	}

  		// Control
  	if (LCD_Col_Pos == 13 && LCD_Row_Pos == 2)
  	{
    	GUI_Control_Options();
  	}

  	goto Navegacion;
}*/
/*
void Ubicar()
{
  	digitalWrite(Boton_Array_4, LOW);
  
  	while (digitalRead(Boton_Array_C) == HIGH && digitalRead(Enc_Center) == HIGH)
  	{
    	ArduinoDmx0.TxBuffer[Canal_Actual - 1] = 255;
    	Numerico_Write (255, Num_Col_Pos - 2, Num_Row_Pos);
    	delay (100);
    	ArduinoDmx0.TxBuffer[Canal_Actual - 1] = 0;
    	lcd.setCursor (Num_Col_Pos - 2, Num_Row_Pos);
    	lcd.print ("   ");
    	delay (100);
  	}

  	digitalWrite(Boton_Array_4, HIGH);
  	delay(300); 	// rebote de boton enter
  	lcd.setCursor (Num_Col_Pos, Num_Row_Pos);
}*/

// ----------------------------- Navegacion LCD - Encoder - Keypad v0.0 -----------------------------

void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
{
	// valor: numero a acomodar
	// max: numero maximo, para el espaciado
	// Dec_Hex: Dec 1, Hex 2
	// LCD_x: cursor
	// LCD_y: cursor

	// calcular tamaño

	lcd.noBlink();							// no parpadear cursor
	lcd.setCursor(LCD_x, LCD_y);

		// Dec
	if (Dec_Hex == 1)				
	{
		if (max < 10)						// 1 cifra
		{
			lcd.print(valor);
			goto salir;
		}
		if (max > 9 && max < 100)			// 2 cifras
		{
			if (valor < 10)
			{
				lcd.print(0);
				lcd.print(valor);
			}
			else
			{
				lcd.print(valor);
			}
			goto salir;
		}
		if (max > 99 && max < 1000)			// 3 cifras
		{
			if (valor < 10)
			{
				lcd.print("00");
				lcd.print(valor);
			}
			if (valor > 9 && valor < 100)
			{
				lcd.print("0");
				lcd.print(valor);
			}
			if (valor > 99)
			{
				lcd.print(valor);
			}
			goto salir;
		}
		if (max > 999)						// 4 cifras
		{
			if (valor < 10)
			{
				lcd.print("000");
				lcd.print(valor);
			}
			if (valor > 9 && valor < 100)
			{
				lcd.print("00");
				lcd.print(valor);
			}
			if (valor > 99)
			{
				lcd.print("0");
				lcd.print(valor);
			}
			if (valor > 999)
			{
				lcd.print(valor);
			}
			goto salir;
		}
	}
		// hexadecimal
	if (Dec_Hex == 2)				
	{
		if (valor < 16)
		{
			lcd.print("0");
			lcd.print(valor, HEX);
			goto salir;
		}
		if (valor > 15)
		{
			lcd.print(valor, HEX);
		}
	}

	salir: {}
}

void Navegar()
{
	// actualiza Cursor_Index_Pos

	byte Index_Final = 0;	// saber cual es el ultimo indice

		// buscar donde poner el cursor y ultimo indice
	for (byte Conteo_Y = 0; Conteo_Y <= 19; Conteo_Y ++)
	{
		for (byte Conteo_X = 0; Conteo_X <= 3; Conteo_X ++)
		{
				// posicionar cursor
			if (Cursor_Index[Conteo_Y][Conteo_X] == Cursor_Index_Pos)
			{
				lcd.setCursor (Conteo_Y, Conteo_X);
				lcd.print(">");
			}
				// saber ultimo indice
			if (Cursor_Index[Conteo_Y][Conteo_X] > Index_Final)
			{
				Index_Final = Cursor_Index[Conteo_Y][Conteo_X];
			}
		}
	} 

	long Enc_ant 				= myEnc.read() / 4;
	long Enc_read				= 0;
	int  Cursor_Index_Pos_ant 	= 0;
	byte giro 					= 0;

		// Lectura de encoder
	while(digitalRead(Enc_Center) == 1)
	{
		Enc_read = myEnc.read() / 4;
		Cursor_Index_Pos_ant = Cursor_Index_Pos;
		giro = 0;

			// izquierda
		if (Enc_read < Enc_ant)
		{
			Enc_ant = Enc_read;
				// restar Cursor_Index_Pos
			Cursor_Index_Pos = Cursor_Index_Pos - 1;
				// limites
			if(Cursor_Index_Pos < 1)
			{
				Cursor_Index_Pos = Index_Final;
			}
			giro = 1;
		}
			// derecha
		if (Enc_read > Enc_ant)		
		{
			Enc_ant = Enc_read;
				// sumar Cursor_Index_Pos
			Cursor_Index_Pos = Cursor_Index_Pos + 1;
					// limites
			if(Cursor_Index_Pos > Index_Final)
			{
				Cursor_Index_Pos = 1;
			}
			giro = 1;
		}

			// si se giro...
		if (giro == 1)
		{
			// posicionar cursor
			for (byte Conteo_Y = 0; Conteo_Y <= 19; Conteo_Y ++)
			{
				for (byte Conteo_X = 0; Conteo_X <= 3; Conteo_X ++)
				{
						// posicionar cursor
					if (Cursor_Index[Conteo_Y][Conteo_X] == Cursor_Index_Pos)
					{
						lcd.setCursor (Conteo_Y, Conteo_X);
						lcd.print(">");
					}
						// borrar cursor anterior
					if (Cursor_Index[Conteo_Y][Conteo_X] == Cursor_Index_Pos_ant)
					{
						lcd.setCursor (Conteo_Y, Conteo_X);
						lcd.print(" ");
					}
				}
			}
		}
	}
	delay(300); // rebote de centro encoder
}

void Cursor_Index_Clear()
{
	// borrar el indice
	for (byte Conteo_Y = 0; Conteo_Y <= 19; Conteo_Y ++)
	{
		for (byte Conteo_X = 0; Conteo_X <= 3; Conteo_X ++)
		{
			Cursor_Index[Conteo_Y][Conteo_X] = 0;
		}
	}
}

int  Numerico_Enc_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, long num_ant)
{
	// regresa el numero generado por el encoder
	// numero minimo a escribir - numero maximo a escribir - x y de pantalla donde se escribe
	// num_ant, el numero que estaba impreso
	// Dec_Hex decimal 1, hexadecimal 2
	// enter: encoder centro
	// hexadecimal max 2 digitos
	// si regresa numero max + 1 se presiono enter en encoder

	long Enc_ant 		= myEnc.read() / 4;
	long Enc_read		= 0;
	int  numero_lenght 	= 0;
	int  Enc_Real_Time  = 0;

	Enc_Real_Time 		= num_ant;

	lcd.setCursor(LCD_x, LCD_y);
	lcd.blink();					// parpadear cursor
	lcd.setCursor(LCD_x, LCD_y);
	lcd.print(num_ant);
	lcd.setCursor(LCD_x, LCD_y);
	
		// esperar giro
	while(1)
	{
		Enc_read = myEnc.read() / 4;
			
		// incrementar
		if (Enc_read > Enc_ant)	
		{
			Enc_Real_Time = Enc_Real_Time + 1;

			// limites
			if (Enc_Real_Time > max)
			{
				Enc_Real_Time = min;
				goto calculo;
			}
			goto calculo;
		}

			// decrementar
		if (Enc_read < Enc_ant)	
		{
			Enc_Real_Time = Enc_Real_Time - 1;

				// limites
			if (Enc_Real_Time < min)
			{
				Enc_Real_Time = max;
				goto calculo;
			}
			goto calculo;
		}

		if (digitalRead(Enc_Center) == 0)
		{
			delay(300);		// rebote
			
			return max + 1;
		}
	}
	
	calculo:

	// calcular tamaños maximos del numero

		// decimal
	if (Dec_Hex == 1)				
	{
		if (max < 10)
		{
			numero_lenght = 1;
		}
		if (max > 9)
		{
			numero_lenght = 2;
		}
		if (max > 99)
		{
			numero_lenght = 3;
		}
		if (max > 999)
		{
			numero_lenght = 4;
		}
	}
		// hexadecimal
	if (Dec_Hex == 2)				
	{
		if (max < 16)
		{
			numero_lenght = 1;
		}
		if (max > 15)
		{
			numero_lenght = 2;
		}
	}
	
	// borrar numeros anteriores

	lcd.setCursor(LCD_x, LCD_y);

	if (numero_lenght == 2)
	{
		lcd.print("  ");
	}
	if (numero_lenght == 3)
	{
		lcd.print("   ");
	}
	if (numero_lenght == 4)
	{
		lcd.print("    ");
	}

	// dibujar numero
	
	lcd.setCursor(LCD_x, LCD_y);
		// dec
	if (Dec_Hex == 1)
	{
		lcd.print(Enc_Real_Time);
	}
		// hex
	if (Dec_Hex == 2)
	{
		lcd.print(Enc_Real_Time, HEX);
	}

	return Enc_Real_Time;
}

int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)
{
	// regresa el numero tecleado
	// numero minimo a escribir - numero maximo a escribir - x y de pantalla donde se escribe
	// el calculo del tamaño del numero lo hace en automatico
	// num_ant, el numero que estaba impreso
	// Dec_Hex decimal 1, hexadecimal 2
	// enter: # y encoder centro
	// cancelar y poner numero default: *
	// hexadecimal max 2 digitos
	// entrada desde encoder: D
	// si regresa numero max + 1 se presiono D para encoder
	
	int 	numero_lenght 		= 0;
	int 	retardo_lecturas 	= 300;
	byte 	numero				= 0;
	byte 	numero_1			= 0;
	byte	numero_2			= 0;
	byte	numero_3			= 0;
	byte	numero_4			= 0;
	byte 	lectura 			= 0;
	byte 	numero_unidades		= 0;
	
	lcd.blink();	// parpadear cursor
	
	// calcular tamaño de numero de espacios que ve a utilizar el numero maximo
		// decimal
	if (Dec_Hex == 1)				
	{
		if (max < 10)
		{
			numero_lenght = 1;
		}
		if (max > 9)
		{
			numero_lenght = 2;
		}
		if (max > 99)
		{
			numero_lenght = 3;
		}
		if (max > 999)
		{
			numero_lenght = 4;
		}
	}
		// hexadecimal
	if (Dec_Hex == 2)				
	{
		if (max < 16)
		{
			numero_lenght = 1;
		}
		if (max > 15)
		{
			numero_lenght = 2;
		}
	}
	
		// LCD posicionar cursor	
	lcd.setCursor(LCD_x, LCD_y);
	if (numero_lenght == 1)
	{
		lcd.print("_");
		lcd.setCursor(LCD_x, LCD_y);
	}
	if (numero_lenght == 2)
	{
		lcd.print("__");
		lcd.setCursor(LCD_x + 1, LCD_y);
	}
	if (numero_lenght == 3)
	{
		lcd.print("___");
		lcd.setCursor(LCD_x + 2, LCD_y);
	}
	if (numero_lenght == 4)
	{
		lcd.print("____");
		lcd.setCursor(LCD_x + 3, LCD_y);
	}
	
dibujar_numero_1:

	lectura = Numerico_Key();
		
		// lectura desde encoder
	if (lectura == 13)	
	{
		return max + 1;
	}

		// reglas decimal
	if (Dec_Hex == 1)
	{
		if (lectura == 16 || lectura == 14 || lectura == 15)	// enter, sin numero
		{
			goto numero_ant;
		}
		if (lectura > 9 && lectura < 14)	// tecla no valida
		{
			goto dibujar_numero_1;
		}
	}
		// reglas hexadecimal
	if (Dec_Hex == 2)
	{
		if (lectura == 16)					// enter, sin numero
		{
			goto numero_ant;
		}
	}
	
	// dibujar numero
	lcd.setCursor(LCD_x, LCD_y);
		// decimal
	if (Dec_Hex == 1)
	{
		if (numero_lenght == 1)
		{
			lcd.print(lectura);
			numero_1 = lectura;
			goto salida;
		}
		if (numero_lenght == 2)
		{
			lcd.setCursor(LCD_x + 1, LCD_y);
			lcd.print(lectura);
			lcd.setCursor(LCD_x + 1, LCD_y);
		}
		if (numero_lenght == 3)
		{
			lcd.setCursor(LCD_x + 2, LCD_y);
			lcd.print(lectura);
			lcd.setCursor(LCD_x + 2, LCD_y);
		}
		if (numero_lenght == 4)
		{
			lcd.setCursor(LCD_x + 3, LCD_y);
			lcd.print(lectura);
			lcd.setCursor(LCD_x + 3, LCD_y);
		}
	}
		// hexadecimal
	if (Dec_Hex == 2)
	{
		if (numero_lenght == 1)
		{
			lcd.print(lectura, HEX);
			numero_1 = lectura;
			goto salida;
		}
		if (numero_lenght ==  2)
		{
			lcd.setCursor(LCD_x + 1, LCD_y);
			lcd.print(lectura, HEX);
			lcd.setCursor(LCD_x + 1, LCD_y);
		}
	}
	
		// continuar
	numero_1 = lectura;

dibujar_numero_2:

	delay(retardo_lecturas);
	lectura = Numerico_Key();
	
		// reglas decimal
	if (Dec_Hex == 1)
	{
		if (lectura == 16 || lectura == 14)	// enter, numero 1
		{
			lcd.setCursor(LCD_x, LCD_y);
			lcd.print("0");
			numero_2 = 0;
			numero_unidades = 1;
			goto salida;
		}
		if (lectura > 9 && lectura < 14)	// tecla no valida
		{
			goto dibujar_numero_2;
		}
		if (lectura == 15)					// cancelar
		{
			goto numero_ant;
		}
	}
		// reglas hexadecimal
	if (Dec_Hex == 2)
	{
		if (lectura == 16)					// enter encoder, solo numero 1
		{
			lcd.setCursor(LCD_x, LCD_y);
			lcd.print("0");
			numero_2 = 0;
			numero_unidades = 1;
			goto salida;
		}
	}
	
	// dibujar numero
		// decimal
	if (Dec_Hex == 1)
	{
		lcd.setCursor(LCD_x, LCD_y);
		if (numero_lenght == 2)
		{
			lcd.print(numero_1);
			lcd.print(lectura);
			numero_2 = lectura;
			goto salida;
		}
		if (numero_lenght == 3)
		{
			lcd.setCursor(LCD_x + 1, LCD_y);
			lcd.print(numero_1);
			lcd.print(lectura);
			lcd.setCursor(LCD_x + 2, LCD_y);
		}
		if (numero_lenght == 4)
		{
			lcd.setCursor(LCD_x + 2, LCD_y);
			lcd.print(numero_1);
			lcd.print(lectura);
			lcd.setCursor(LCD_x + 3, LCD_y);
		}
	}
		// hexadecimal
	if (Dec_Hex == 2)
	{
		lcd.setCursor(LCD_x, LCD_y);
		lcd.print(numero_1, HEX);
		lcd.print(lectura, HEX);
		numero_2 = lectura;
		goto salida;
	}		
	
	numero_2 = lectura;

dibujar_numero_3:

	delay(retardo_lecturas);
	
	lectura = Numerico_Key();
	
		// reglas
	if (lectura == 16 || lectura == 14)	// enter, numero 2
	{
		numero_3 = 0;
		numero_unidades = 2;
		goto salida;
	}
	if (lectura > 9 && lectura < 14)	// tecla no valida
	{
		goto dibujar_numero_3;
	}
	if (lectura == 15)					// cancelar
	{
		goto numero_ant;
	}	
		// dibujar numero
	lcd.setCursor(LCD_x, LCD_y);
	if (numero_lenght == 3)
	{
		lcd.print(numero_1);
		lcd.print(numero_2);
		lcd.print(lectura);
		numero_3 = lectura;
		goto salida;
	}
	if (numero_lenght == 4)
	{
		lcd.setCursor(LCD_x + 1, LCD_y);
		lcd.print(numero_1);
		lcd.print(numero_2);
		lcd.print(lectura);
		lcd.setCursor(LCD_x + 3, LCD_y);
	}
	numero_3 = lectura;	
	
dibujar_numero_4:

	delay(retardo_lecturas);
	
	lectura = Numerico_Key();
	
		// reglas
	if (lectura == 16 || lectura == 14)	// enter, numero 3
	{
		numero_4 = 0;
		numero_unidades = 3;
		goto salida;
	}
	if (lectura > 9 && lectura < 14)	// tecla no valida
	{
		goto dibujar_numero_4;
	}
	if (lectura == 15)					// cancelar
	{
		goto numero_ant;
	}	
		// dibujar numero
	lcd.setCursor(LCD_x, LCD_y);
	lcd.print(numero_1);
	lcd.print(numero_2);
	lcd.print(numero_3);
	lcd.print(lectura);
	
	numero_4 = lectura;
		
	goto salida;	
	
numero_ant:
	
	lcd.noBlink();
		// inicial
	lcd.setCursor(LCD_x, LCD_y);
		// 2 digitos
	if (numero_lenght == 2)
	{
			// decimal
		if (Dec_Hex == 1)
		{
			if (num_ant < 10)
			{
				lcd.print("0");
			}
		}
			// hexadecimal
		if (Dec_Hex == 2)
		{
			if (num_ant < 16)
			{
				lcd.print("0");
			}
		}
	}
		// 3 digitos
	if (numero_lenght == 3)
	{
		if (num_ant < 10)
		{
			lcd.print("00");
		}
		if (num_ant > 9 && num_ant < 100)
		{
			lcd.print("0");
		}
	}
		// 4 digitos
	if (numero_lenght == 4)
	{
		if (num_ant < 10)
		{
			lcd.print("000");
		}
		if (num_ant > 9 && num_ant < 100)
		{
			lcd.print("00");
		}
		if (num_ant > 99 && num_ant < 1000)
		{
			lcd.print("0");
		}		
	}
		// dibujar numero
	if (Dec_Hex == 1)	// decimal
	{
		lcd.print(num_ant);
	}
	if (Dec_Hex == 2)	// hexadecimal
	{
		lcd.print(num_ant, HEX);
	}
	return num_ant;
	
salida:
		// agrupar numeros para enviar de vuelta
	lcd.noBlink();
	int numero_total;
	int numero_temp;
	
		// 1 digito
	if (numero_lenght == 1)
	{
			// limites
		lcd.setCursor(LCD_x, LCD_y);
		if (numero_1 > max)
		{
			numero_1 = max;
			if (Dec_Hex == 1)	// decimal
			{
				lcd.print(max);
			}
			if (Dec_Hex == 2)	// hexadecimal
			{
				lcd.print(max, HEX);
			}
		}
		if (numero_1 < min)
		{
			numero_1 = min; 
			if (Dec_Hex == 1)	// decimal
			{
				lcd.print(min);
			}
			if (Dec_Hex == 2)	// hexadecimal
			{
				lcd.print(min, HEX);
			}
		}
		
		return numero_1;
	}
		// 2 digitos
	if (numero_lenght == 2)
	{
		// cncatenar numero
			// decimal
		if (Dec_Hex == 1)
		{
			if (numero_unidades == 0)
			{
				numero_total 	= numero_1 * 10;
				numero_total 	= numero_total + numero_2;
			}
			else
			{
				numero_total 	= numero_1;
			}
		
		}
			// hexadecimal
		if (Dec_Hex == 2)
		{
			if (numero_unidades == 0)
			{
				numero_total 	= numero_1 * 16;
				numero_total 	= numero_total + numero_2;
			}
			else
			{
				numero_total 	= numero_1;
			}
			
		}
			// limites
		if (numero_total > max)
		{
			numero_total = max;
		}
		if (numero_total < min)
		{
			numero_total = min;
		}
			// escribir numero
		lcd.setCursor(LCD_x, LCD_y);
		if (numero_total < 10)
		{
			lcd.print("0");
			if (Dec_Hex == 1)	// decimal
			{
				lcd.print(numero_total);
			}
			if (Dec_Hex == 2)	// hexadecimal
			{
				lcd.print(numero_total, HEX);
			}
		}
		if (numero_total > 9)
		{
			if (Dec_Hex == 1)	// decimal
			{
				lcd.print(numero_total);
			}
			if (Dec_Hex == 2)	// hexadecimal
			{
				if (numero_total > 15)
				{
					lcd.print(numero_total, HEX);
				}
				else
				{
					lcd.print("0");
					lcd.print(numero_total, HEX);
				}
				
			}
		}
		
		return numero_total;
	}
		// 3 digitos
	if (numero_lenght == 3)
	{
		// concatenar numero
			// 1 digitos
		if (numero_unidades == 1)
		{
			numero_total 	= numero_1;
		}
			// 2 digitos
		if (numero_unidades == 2)
		{
			numero_total 	= numero_1 * 10;
			numero_total	= numero_total + numero_2;
		}
			// 3 digitos
		if (numero_unidades == 0)
		{
			numero_total 	= numero_1 * 100;
			numero_temp		= numero_2 * 10; 
			numero_total	= numero_total + numero_temp + numero_3;
		}
		
		// limites
		if (numero_total > max)
		{
			numero_total = max;
		}
		if (numero_total < min)
		{
			numero_total = min;
		}
			// escribir numero
		lcd.setCursor(LCD_x, LCD_y);
		if (numero_total < 10)
		{
			lcd.print("00");
			lcd.print(numero_total);
		}
		if (numero_total > 9 && numero_total < 100)
		{
			lcd.print("0");
			lcd.print(numero_total);
		}
		if (numero_total > 99)
		{
			lcd.print(numero_total);
		}
		
		return numero_total;
	}
		// 4 digitos
	if (numero_lenght == 4)
	{
			// concatenar numeros
		if (numero_unidades == 1)
		{
			numero_total 	= numero_1;
		}
		if (numero_unidades == 2)
		{
			numero_total 	= numero_1 * 10;
			numero_total	= numero_total + numero_2;
		}
		if (numero_unidades == 3)
		{
			numero_total 	= numero_1 * 100;
			numero_temp		= numero_2 * 10;
			numero_total	= numero_total + numero_temp + numero_3;
		}
		if (numero_unidades == 0)
		{
			numero_total 	= numero_1 * 1000;
			numero_temp		= numero_2 * 100; 
			numero_total	= numero_total + numero_temp;
			numero_temp		= numero_3 * 10;
			numero_total	= numero_total + numero_temp + numero_4;
		}
			// limites
		if (numero_total > max)
		{
			numero_total = max;
		}
		if (numero_total < min)
		{
			numero_total = min;
		}
			// escribir numero
		lcd.setCursor(LCD_x, LCD_y);
		if (numero_total < 10)
		{
			lcd.print("000");
			lcd.print(numero_total);
		}
		if (numero_total > 9 && numero_total < 100)
		{
			lcd.print("00");
			lcd.print(numero_total);
		}
		if (numero_total > 99 && numero_total < 1000)
		{
			lcd.print("0");
			lcd.print(numero_total);
		}
		if (numero_total > 999)
		{
			lcd.print(numero_total);
		}
		
		return numero_total;
	}
}

int Numerico_Key()
{
	// devuelve el numero de la tecla precionada o el centro del encoder
	// A = 10, B = 11, C = 12, D = 13, # = 14, * = 15, encoder = 16
	
	byte numero = 17;			// 17 para valor sin tecla
	
	// puertos a ceros
	digitalWrite(Keypad_A, HIGH);
	digitalWrite(Keypad_B, HIGH);
	digitalWrite(Keypad_C, HIGH);
	digitalWrite(Keypad_D, HIGH);
	
	while (numero == 17)
	{
		// encoder
		if (digitalRead(Enc_Center) == 0)
		{
			delay(300);
			numero = 16;
			break;
		}
		
		// A 1
		digitalWrite(Keypad_A, LOW);
		if (digitalRead(Keypad_1) == 0)
		{
			numero = 1;
			break;
		}
		
		// A 2
		if (digitalRead(Keypad_2) == 0)
		{
			numero = 2;
			break;
		}
		
		// A 3
		if (digitalRead(Keypad_3) == 0)
		{
			numero = 3;
			break;
		}
		
		// A 4
		if (digitalRead(Keypad_4) == 0)
		{
			numero = 10;
			break;
		}
		digitalWrite(Keypad_A, HIGH);
		
		// B 1
		digitalWrite(Keypad_B, LOW);
		if (digitalRead(Keypad_1) == 0)
		{
			numero = 4;
			break;
		}
		
		// B 2
		if (digitalRead(Keypad_2) == 0)
		{
			numero = 5;
			break;
		}
		
		// B 3
		if (digitalRead(Keypad_3) == 0)
		{
			numero = 6;
			break;
		}
		
		// B 4
		if (digitalRead(Keypad_4) == 0)
		{
			numero = 11;
			break;
		}
		digitalWrite(Keypad_B, HIGH);
		
		// C 1
		digitalWrite(Keypad_C, LOW);
		if (digitalRead(Keypad_1) == 0)
		{
			numero = 7;
			break;
		}
		
		// C 2
		if (digitalRead(Keypad_2) == 0)
		{
			numero = 8;
			break;
		}
		
		// C 3
		if (digitalRead(Keypad_3) == 0)
		{
			numero = 9;
			break;
		}
		
		// C 4
		if (digitalRead(Keypad_4) == 0)
		{
			numero = 12;
			break;
		}
		digitalWrite(Keypad_C, HIGH);
		
		// D 1
		digitalWrite(Keypad_D, LOW);
		if (digitalRead(Keypad_1) == 0)
		{
			numero = 15;
			break;
		}
		
		// D 2
		if (digitalRead(Keypad_2) == 0)
		{
			numero = 0;
			break;
		}
		
		// D 3
		if (digitalRead(Keypad_3) == 0)
		{
			numero = 14;
			break;
		}
		
		// D 4
		if (digitalRead(Keypad_4) == 0)
		{
			numero = 13;
			break;
		}
		digitalWrite(Keypad_D, HIGH);
	}
	
		// puertos a ceros
	digitalWrite(Keypad_A, HIGH);
	digitalWrite(Keypad_B, HIGH);
	digitalWrite(Keypad_C, HIGH);
	digitalWrite(Keypad_D, HIGH);
	
	return numero;
}