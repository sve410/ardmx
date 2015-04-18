// includes 
	#include <lib_dmx.h>  		// libreria DMX 4 universos deskontrol four universes DMX library  - http://www.deskontrol.net/blog
	#include <EEPROM.h>
	#include<string.h>
	#include <LiquidCrystal.h>	// Simple library for driving 20x4 LCD with 4bits http://morf.lv/modules.php?name=tutorials&lasit=22 
	#include <Wire.h>			
	
// DMX Library
	#define DMX512 (0)             // (250 kbaud - 2 to 512 channels) Standard USITT DMX-512
	//#define    DMX1024    (1)    // (500 kbaud - 2 to 1024 channels) Completely non standard - TESTED ok
	//#define    DMX2048    (2)    // (1000 kbaud - 2 to 2048 channels) called by manufacturers DMX1000K, DMX 4x or DMX 1M ???

//LCD Library
	#define   CONTRAST_PIN   9;
	#define   BACKLIGHT_PIN  7;
	#define   CONTRAST       110;
	LiquidCrystal lcd(30, 31, 32, 22, 23, 24, 25, 26, 27, 28, 29);

//Variable globales
	byte DMX_Values [511];       //array de valores actuales DMX
	int Delay_Boton = 150;       //retardo de rebote de boton
	int Delay_EEPROM = 20;       //retardo de escritura de eeprom 
	byte Array = 0;              //posicion de array a mostrar
	byte EEPROM_Load_Select = 0; //1 eeprom cambios, 0 sin cambios
	byte Multi_Coor_X_SW = 12;   //posiciones iniciales de menu multi
	byte Multi_Coor_Y_SW = 0;    //posiciones iniciales de menu multi
	//byte SW_Posicion[2] = {0,0,0}; //X, Y ,Enter 

//Defines
	//Botones
		#define Up_Boton 33
		#define Down_Boton 34
		#define Left_Boton 35
		#define Right_Boton 36
		#define Center_Boton 37

void setup() 
	{
		//DMX
			ArduinoDmx0.set_tx_address(1);      // poner aqui la direccion de inicio de DMX 
			ArduinoDmx0.set_tx_channels(512);   // poner aqui el numero de canales a transmitir 
			ArduinoDmx0.init_tx(DMX512);        // iniciar transmision universo 0, modo estandar DMX512
		//LCD 
			lcd.begin(20,4); // initialize the lcd 
			lcd.home();      // go home
		//Botones
			pinMode(Up_Boton,INPUT_PULLUP);
			pinMode(Down_Boton,INPUT_PULLUP);
			pinMode(Left_Boton,INPUT_PULLUP);
			pinMode(Right_Boton,INPUT_PULLUP);
			pinMode(Center_Boton,INPUT_PULLUP);
	}    

void loop()
	{
		LCD_Init();            //inicializador de LCD
		LCD_EEPROM_Options(); //Opciones iniciales de eeprom  
		LCD_Control_Options();     //Opciones iniciales de control multi y unit   
		//ArduinoDmx0.TxBuffer[0] = 255;  
		//ArduinoDmx0.TxBuffer[1] = 0;
		//ArduinoDmx0.TxBuffer[2] = 255;   
		//ArduinoDmx0.TxBuffer[3] = 0;   
		//ArduinoDmx0.TxBuffer[4] = 0;   
		//ArduinoDmx0.TxBuffer[5] = 0;  
	}

void LCD_Init()
	{//texto inicial de LCD verciones
		lcd.print(" Tech Inside.com.mx");  
		lcd.setCursor (0, 1);
		lcd.print("DMX-512   Controller"); 
		lcd.setCursor (0, 2);
		lcd.print("           Soft v0.0"); 
		lcd.setCursor (0, 3);
		lcd.print("ID:20      Hard v0.0"); 
		delay(200); //retardo de muestra de verciones
		lcd.clear();
		lcd.home();
	}

void LCD_Multi_Array_Load()
	{
		lcd.clear();
		lcd.setCursor (1,0);
		lcd.print("Bac Nex Mem 000-000");
		for(byte Conteo = 1; Conteo < 4; Conteo ++)
			{
				lcd.setCursor (1, Conteo);
				lcd.print("000 000 000 000 000"); 
			}
		Array = 0; 							//arranque en channel 0
		Control_Multi_Array_Load(Array);  	//escribe array de multi Array pone el indice
		Control_Multi_SW_Select();        	//control de botones en multi
	}

void Control_Multi_SW_Select()
	{
		byte Center_Go = 0;    //0 sin accion, 1 accion
		byte Mover_X = 2;      //0 resta, 1 suma, 2 sin cambio
		byte Mover_Y = 2;      //0 resta, 1 suma, 2 sin cambio
		byte Sumar_Restar = 0; //suma de numerador 0 resta 1 suma
  
		lcd.setCursor (Multi_Coor_X_SW, Multi_Coor_Y_SW);
		lcd.print(">"); 
		
	Lectura: //lectura de botones 
		if (digitalRead(Center_Boton) == LOW) //seleccion de boton central
			{
				if (Center_Go == 0) //si no hay una accion de por medio
					{
						Center_Go = 1;  //accion a ejecutar
						lcd.setCursor (Multi_Coor_X_SW, Multi_Coor_Y_SW);
						lcd.print("+");
					}
			}
		else //si hay accion de por medio
			{
				Center_Go = 0; //no ejecutar accion
				lcd.setCursor (Multi_Coor_X_SW, Multi_Coor_Y_SW);
				lcd.print(">");
			}   
		delay(Delay_Boton);
		goto Lectura; 
		if (digitalRead(Left_Boton) == LOW) //seleccion de boton izquierdo
			{
				Mover_X = 0;     //0 resta, 1 suma, 2 sin cambio
				if (Multi_Coor_X_SW == 0)
					{
						Mover_X = 2;
					} 
				Mover_Y = 2; 
				delay(Delay_Boton);    
				goto Dibujar;
				goto Lectura;
			}
		if (digitalRead(Right_Boton) == LOW) //seleccion de boton derecho
			{
				Mover_X = 1;     //0 resta, 1 suma, 2 sin cambio
				if (Multi_Coor_X_SW == 16)
					{
						Mover_X = 2;
					} 
				Mover_Y = 2; 
				delay(Delay_Boton);    
				goto Dibujar;
				goto Lectura;
			}
		if (digitalRead(Up_Boton) == LOW) //seleccion de boton arriba
			{
				if (Center_Go == 0)  //si no hay accion de pormedio
					{
						Mover_Y = 0;     //0 resta, 1 suma, 2 sin cambio
						if (Multi_Coor_Y_SW == 00) 
							{
								Mover_Y = 2;
							} 
						Mover_X = 2; 
						delay(Delay_Boton);    
						goto Dibujar;
					}
				else  //si fay accion de pormedio
					{
						Sumar_Restar = 1;
						delay(Delay_Boton);
						goto Accion; 
					}
				goto Lectura;
			}
		if (digitalRead(Down_Boton) == LOW) //seleccion boton abajo
			{
				if (Center_Go == 0)
					{
						Mover_Y = 1;     //0 resta, 1 suma, 2 sin cambio
						if (Multi_Coor_Y_SW == 4)
							{
								Mover_Y = 2;
							} 
						Mover_X = 2; 
						delay(Delay_Boton);    
						goto Dibujar;
					}
			}
		else
			{
				Sumar_Restar = 0;
				delay(Delay_Boton);
				goto Accion;
			}
		goto Lectura;
		
	Dibujar:
		lcd.setCursor (Multi_Coor_X_SW, Multi_Coor_Y_SW);        // go to the next line
		if (Multi_Coor_X_SW == 16)
			{
				if (Multi_Coor_Y_SW == 0) 
					{
						lcd.print("-"); 
					}
			}
		else
			{
				lcd.print(" ");
			} 
		switch (Mover_X)
			{
				case 0: //resta
					Multi_Coor_X_SW = Multi_Coor_X_SW - 4;
					break;
				case 1: //suma 
					Multi_Coor_X_SW = Multi_Coor_X_SW + 4;
					if (Multi_Coor_X_SW == 6)
						{
							Multi_Coor_X_SW = 5;  
						}
					break;
				case 2: //sin cambios
					break;  
			}
		switch (Mover_Y)
			{
				case 0: //resta
					Multi_Coor_Y_SW = Multi_Coor_Y_SW - 1;
					break; 
				case 1: //suma 
					Multi_Coor_Y_SW = Multi_Coor_Y_SW + 1;
					if (Multi_Coor_Y_SW == 6)
						{
							Multi_Coor_Y_SW = 5;  
						}
					break;
				case 2: //sin cambios
					break; 
			}      
		lcd.setCursor (Multi_Coor_X_SW, Multi_Coor_Y_SW);
		lcd.print(">"); 
		goto Lectura;    
   
	Accion:
		byte Posicion = 0;
		//numerador Array
		if (Multi_Coor_X_SW > 8)
			{              
				if (Multi_Coor_Y_SW == 0)
					{
						if (Multi_Coor_X_SW == 12) //menor numero
							{
								if (Sumar_Restar == 1)//sumar
									{
										// primer numero
										if (Array == 0)
											{
												Array = 1;
											}
										Array = Array + 1;
										if (Array > 241)
											{
												Array = Array - 1;
												goto Lectura;
											}
										Posicion = 13;
										if (Array < 10)
											{
												Posicion = Posicion + 2;
												goto Sumalo;
											}  
										if (Array < 100)
											{  
												Posicion = Posicion + 1;
											}
											
	Sumalo:
										lcd.setCursor (Posicion, 0);        // go to the next line
										lcd.print(Array);
										// segundo numero
										byte Array_Segundo = Array + 14;
										Posicion = 17;
										if (Array_Segundo < 10)
											{
												Posicion = Posicion + 2;
												goto Sumalo_Segundo;
											}  
										if (Array_Segundo < 100)
											{  
												Posicion = Posicion + 1;
											}
										Sumalo_Segundo:
										lcd.setCursor (Posicion, 0);        // go to the next line
										lcd.print(Array_Segundo);                 
										Array = Array - 1;
										goto Lectura;
									}
								else //restar
									{
										// primer numero
										if (Array == 0)
											{
												Array = 1;
											}   
										Posicion = 13;
										if (Array < 10)
											{		
												Posicion = Posicion + 2;
												goto Restalo;
											}  
										if (Array < 100)
											{  
												Posicion = Posicion + 1;
											}
													
	Restalo:
										lcd.setCursor (Posicion, 0);        // go to the next line
										lcd.print(Array);	
										// segundo numero
										byte Array_Segundo = Array - 14;
										Posicion = 17;
										if (Array_Segundo < 10)
											{
												Posicion = Posicion + 2;
												goto Restalo_Segundo;
											}  
										if (Array_Segundo < 100)
											{  
												Posicion = Posicion + 1;
											}
											
	Restalo_Segundo:
										lcd.setCursor (Posicion, 0);        // go to the next line
										lcd.print(Array_Segundo);
										goto Lectura;
									}
							}   
					}
			}
		goto Lectura;
	}

void Control_Multi_Array_Load (byte Array)
	{	//llenado de array multi
		byte Posicion;
		byte Array_Pos = 0;
		Array_Pos = Array; 
		// texto de array
		if(Array_Pos == 0)
			{
				Array_Pos = 1;
			}
		Posicion = 13;
		if (Array_Pos < 10)
			{
				Posicion = Posicion + 2;
				goto Escribe_First;
			}  
		if (Array_Pos < 100)
			{  
				Posicion = Posicion + 1;
			}  
	
	Escribe_First:
		lcd.setCursor (Posicion,0); //Posicion_LCD
		lcd.print(Array_Pos); 
		Posicion = 17;
		Array_Pos = Array_Pos + 14;
		if(Array_Pos == 0)
			{
				Array_Pos = 1;
			}
		if (Array_Pos < 10)
			{
				Posicion = Posicion + 2;
				goto Escribe_Second;
			}  
		if (Array_Pos < 100)
			{  
				Posicion = Posicion + 1;
			} 

	Escribe_Second:
		lcd.setCursor (Posicion,0); //Posicion_LCD
		lcd.print(Array_Pos); 
		//Array
		for (byte Row = 1; Row < 4; Row ++)
			{
				Posicion = 1;
				for (byte Conteo = 1; Conteo < 6; Conteo ++)
					{ 
						if (DMX_Values[Array] < 10)
							{
								Posicion = Posicion + 2;
								goto Escribe_Tree;
							}
						if (DMX_Values[Array] < 100)
							{
								Posicion = Posicion + 1;
							}
							
	Escribe_Tree:
						lcd.setCursor (Posicion,Row);
						lcd.print(DMX_Values[Array]);
						if (DMX_Values[Array] < 10)
							{
								Posicion = Posicion - 2; 
								goto Salida; 
							}
						if (DMX_Values[Array] < 100)
							{
								Posicion = Posicion - 1;
							}

	Salida:
						Posicion = Posicion + 4; 
						Array = Array + 1;
					}
			}
	}

void LCD_EEPROM_Options()
	{	//opcion de valores iniciales de EEPROM
		lcd.print("Memory Init:");  
		lcd.setCursor (0, 2);      
		lcd.print(">Empty"); 
		lcd.setCursor (8, 2);     
		lcd.print("Load"); 
		lcd.setCursor (14, 2);    
		lcd.print("Clear"); 
		byte Boton = 0;
		byte Posicion = 1;

	Lectura:
		if (digitalRead(Center_Boton) == LOW)
			{
				delay(Delay_Boton);
				Boton = 3;
				goto Option;
			}  
		if (digitalRead(Left_Boton) == LOW)
			{
				delay(Delay_Boton);
				Boton = 2;
				goto Option;
			}
		if (digitalRead(Right_Boton) == LOW)
			{
				delay(Delay_Boton);
				Boton = 4;
				goto Option;
			}
		goto Lectura;

	Option:
		switch (Boton)
			{
				case 2: //Left
					switch (Posicion)
						{
							case 2: //regresar a posicion 1
								lcd.setCursor (7, 2);       
								lcd.print(" "); 
								lcd.setCursor (0, 2);        
								lcd.print(">");
								Posicion = 1;
								break;
							case 3: //regresar a posicion 2
								lcd.setCursor (13, 2);        
								lcd.print(" "); 
								lcd.setCursor (7, 2);       
								lcd.print(">");
								Posicion = 2;
								break;
						}
					break;
				case 4: //Right
					switch (Posicion)
						{
							case 1: //avanzar a 2
								lcd.setCursor (0, 2);       
								lcd.print(" "); 
								lcd.setCursor (7, 2);       
								lcd.print(">");
								Posicion = 2;
								break;  
							case 2: //avanzar a 3
								lcd.setCursor (7, 2);  
								lcd.print(" "); 
								lcd.setCursor (13, 2);     
								lcd.print(">");
								Posicion = 3;
								break; 
						}
					break;
				case 3: //Center
					switch (Posicion)
						{
							case 1:
								goto Salida; //Empty
								EEPROM_Load_Select = 0;
								goto Salida;
							case 2:
								EEPROM_Load_Select = 1;	
								EEPROM_Load(); //Load
								goto Salida;
							case 3:
								EEPROM_Load_Select = 1;	
								EEPROM_Clear(); //Clear
								goto Salida;
						}  
			}
		goto Lectura;
Salida: {}
}

void EEPROM_Load()
	{	//cargar valores desde eeprom
		for(int Canal = 0; Canal < 512; Canal++)
			{
				DMX_Values[Canal] = EEPROM.read(Canal);          //lectura desde EEPROM
				ArduinoDmx0.TxBuffer[Canal] = DMX_Values[Canal]; //salida a DMX
			}
		lcd.clear();
		lcd.setCursor (3, 1);        // go to the next line
		lcd.print("Memory Loaded!");
		delay(300);
	}

void EEPROM_Clear()
	{	//cargar valores desde eeprom
		lcd.clear();
		lcd.setCursor (1, 1);        // go to the next line
		lcd.print("Memory Cleaning...");
		for(int Canal = 0; Canal < 512; Canal ++)
			{
				EEPROM.write(Canal,0);
				delay(0); //Delay_EEPROM);///////////////////////////////////////////// cambia a 20
				ArduinoDmx0.TxBuffer[Canal] = 0; //salida a DMX
				DMX_Values[Canal] = 0;
			}
		lcd.clear();
		lcd.setCursor (1, 1);        // go to the next line
		lcd.print("Memory Cleaned!");
		delay(300);
	}

void LCD_Control_Options()
	{
		lcd.clear();
		lcd.setCursor (0, 0);       
		lcd.print("Control Options:");
		lcd.setCursor (2, 2);        
		lcd.print(">Unit");
		lcd.setCursor (11, 2);      
		lcd.print("Multi");
		byte Boton = 0;
		byte Posicion = 1;

	Lectura:
		if (digitalRead(Center_Boton) == LOW)
			{
				delay(Delay_Boton);
				Boton = 3;
				goto Option;
			}  
		if (digitalRead(Left_Boton) == LOW)
			{
				delay(Delay_Boton);
				Boton = 2;
				goto Option;
			}
		if (digitalRead(Right_Boton) == LOW)
			{
				delay(Delay_Boton);
				Boton = 4;
				goto Option;
			}
		goto Lectura;

	Option:
		switch (Boton)
			{
				case 2: //Left
					switch (Posicion)
						{
							case 2: //regresar a posicion 1
								lcd.setCursor (10, 2);    
								lcd.print(" "); 
								lcd.setCursor (2, 2);
								lcd.print(">");
								Posicion = 1;
								break;
						}
					break;
				case 4: //Right
					switch (Posicion)
						{
							case 1: //avanzar a 2
								lcd.setCursor (2, 2);      
								lcd.print(" "); 
								lcd.setCursor (10, 2);       
								lcd.print(">");
								Posicion = 2;
								break;  
						}
					break;
				case 3: //Center
					switch (Posicion)
						{
							case 1: //Unit
								goto Salida;
								break;
							case 2: //Multi
								Control_Multi();
								break;
						} 
					break;    
			}
		goto Lectura;

	Salida: {}
}

void Switch_Control_Posicion ()
{
	//SW_Posicion[0] = 0; //inicial de X
	//SW_Posicion[1] = 0; //inicial de Y
	//SW_Posicion[2] = 0; //inicial de Enter
	
	Lectura:
		//enter
		if (digitalRead(Center_Boton) == LOW)
			{
				delay(Delay_Boton);
				//SW_Posicion[2] = 1
			}
			
			
		//Up
		if (digitalRead(Up_Boton) == LOW)
			{
				
			}
}










