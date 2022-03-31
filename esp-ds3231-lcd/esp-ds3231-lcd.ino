#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"

LiquidCrystal_I2C lcd (0x27,20,4);

RTC_DS3231 rtc;


void setup() {
  Serial.println(115200);

  //Wire.begin();
  
  rtc.begin();
  rtc.adjust(DateTime(__DATE__,__TIME__));
/*
  lcd.init();
  lcd.backlight();
  lcd.clear(); */

}

void loop() {
  DateTime now_ = rtc.now();
  String hora = String(now_.hour())+":"+String(now_.minute()) +":"+ String(now_.second());
  Serial.println(hora);


}
