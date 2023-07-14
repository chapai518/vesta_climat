#include <GyverOLED.h>
#include <GyverEncoder.h>
#include <microDS18B20.h>
MicroDS18B20<10> sensor1; // номер пина к которому подключен DS18B20

#define CLK 2 // номер пина к которому подключен пин S2 энкодера
#define DT 3 // номер пина к которому подключен пин S1 энкодера
#define SW 4 // номер пина к которому подключен пин KEY энкодера

GyverOLED oled(0x3C);
Encoder enc(CLK, DT, SW);
int temp = 22;
int min_temp = 15;
int max_temp = 30;

void setup()
{
  Serial.begin(9600);
  enc.setType(TYPE2);
  oled.init(OLED128x64);        // инициализация экрана
  oled.clear();
  oled.scale2X();
  oled.home();        // курсор в 0,0
  oled.print("Т1: ");
  oled.setCursor(0, 2);
  oled.print("T2: ");
  oled.setCursor(7, 2);
  oled.print(temp);
  oled.setCursor(0, 4);
  oled.print("T3: ");
  oled.setCursor(0, 6);
  oled.print("T4: ");
}

void loop(){
//  poten();  //если использовать потенциометр
  enc.tick();
  if (enc.isTurn()) {
    if (enc.isRight()) {
      temp++;
      if(temp > max_temp)
        temp = max_temp;
        else{
        temp=temp;
      }
    }
    if (enc.isLeft()) {
      temp--;
      if(temp < min_temp)
        temp = min_temp;
        else{
        temp=temp;
      }
    }
   updTemp2();
   Serial.println(temp);
  }
  static uint32_t tmr;
  if (millis() - tmr >= 2000) {
    tmr = millis();
//    sensors.requestTemperatures();
    sensor1.requestTemp();
    updTemp1(); 
  }

//void poten(){     //если использовать потенциометр
//  int enc = analogRead(0);
//  temp = map(enc,0,1023,10,30);
//}
}
void updTemp1(){
//  oled.setCursor(7, 0);
//  oled.print("    "); 
  oled.setCursor(7, 0);
  Serial.print(sensor1.getTemp());
  oled.print(sensor1.getTemp());
}

void updTemp2(){
  oled.setCursor(7, 2);
  oled.print("    ");
  oled.setCursor(7, 2);
  oled.print(temp);
}
/*
#define DELAY_ENC_BTWN 500
#define DELAY_ENC_CKL_MS 30
void calc(){
  if (sensor1.getTemp() < temp) {
	    pin_low(OUT_BTN_T_UP);
	    delay(DELAY_ENC_BTWN);
	    pin_low(OUT_BTN_T_DWN);
        else{
        temp=temp;
      }
  }
}

#define DELAY_ENC_BTWN 500
#define DELAY_ENC_CKL_MS 30

void switch_temp(int8_t up)
{
    if (up) {
	if (get_output(OUT_BTN_T_UP)) {
	    pin_low(OUT_BTN_T_UP);
	    delay(DELAY_ENC_BTWN);
	    pin_low(OUT_BTN_T_DWN);
	} else {
	    pin_high(OUT_BTN_T_UP);
	    delay(DELAY_ENC_BTWN);
	    pin_high(OUT_BTN_T_DWN);
	}
    } else {
	if (get_output(OUT_BTN_T_UP)) {
	    pin_low(OUT_BTN_T_DWN);
	    delay(DELAY_ENC_BTWN);
	    pin_low(OUT_BTN_T_UP);
	} else {
	    pin_high(OUT_BTN_T_DWN);
	    delay(DELAY_ENC_BTWN);
	    pin_high(OUT_BTN_T_UP);
	}
    }
    delay_ms(DELAY_ENC_CKL_MS);
}
*/