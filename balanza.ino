/*
---------------------------------------------------------------------------------------
Datos de Referencia :https://naylampmechatronics.com/blog/25_tutorial-trasmisor-de-celda-de-carga-hx711-ba.html
Program Created  by @PablitoLesPaul & @Leandrouno
Date : 01/09/2018
--------------------------------------------------------------------------------------

*/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

#define DOUT  A1
#define CLK  A0
#define SET 2
#define RESET 3


HX711 balanza(DOUT, CLK);
int esta_contando = 0, bandera_inicio = 0, guarda_peso = 0, apagado = 0;
float peso = 0, peso_actual = 0, peso_anterior[]= {0,0,0}, peso_mostrar = 0;
long anteriores = 0;
LiquidCrystal_I2C lcd(0x3F,16,2); 

void setup() {
              pinMode(SET,INPUT_PULLUP);
              pinMode(RESET,INPUT_PULLUP);
              //Serial.begin(9600);
              //Serial.print("Lectura del valor del ADC:  ");
              //Serial.println(balanza.read());
              //Serial.println("No ponga ningun  objeto sobre la balanza");
              //Serial.println("Iniciando Tara...");
              lcd.init();
              lcd.backlight();       
              lcd.setCursor(0, 0);
              lcd.print("Iniciando Tara  ");
              lcd.setCursor(0, 1);
              lcd.print("Espere...       ");         
            }

void loop() {
               if(bandera_inicio == 0){
                                       lcd.clear();
                                       lcd.setCursor(0, 0);
                                       lcd.print("Espere...       ");
                                       balanza.set_scale(414844.44); // Establecemos la escala
                                       balanza.tare(20);  //El peso actual es considerado Tara.
                                       lcd.print("Ya puede pesar  ");          
                                       bandera_inicio = 1;
                                       esta_contando = 0;
                                       }
                                      if(digitalRead(SET)==LOW) {esta_contando = 1; guarda_peso = 0;}
                                      if(digitalRead(RESET)==LOW) bandera_inicio = 0;

              if(esta_contando == 1)  {                  
                                       if(guarda_peso == 0) {peso = peso_actual; guarda_peso = 1;}
                                       lcd.setCursor(0, 0);
                                       lcd.print("Unidades: ");
                                       lcd.setCursor(10, 0);
                                       lcd.print(peso_actual/peso*10,0);
                                       lcd.print("             ");
                                      }
                                     else { guarda_peso = 0; }
                            
 if(millis()-anteriores >= 1000) {
                                  lcd.setCursor(15, 0);
                                  lcd.print("*"); 
                                  peso_actual = balanza.get_units(5);
                                  peso_mostrar = peso_actual*1000;
                                  anteriores = millis();
                                  
                                 if(esta_contando == 0)  {   
                                                          lcd.setCursor(0, 0);
                                                          lcd.print("                ");                                         
                                                         }
                                                          lcd.setCursor(0, 1);
                                  lcd.print("Peso: ");
                                  lcd.setCursor(6, 1); 
                                  lcd.print(peso_mostrar,0);                   
                                  lcd.print(" gramos   ");
                                }
                                  
}
