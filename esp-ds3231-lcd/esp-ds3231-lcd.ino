#include <SPI.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>

#define I2C_Freq 100000
#define I2C_ADDR 0x27 
#define SDA 21
#define SCL 22


DS3231 rtc(&Wire.begin());
LiquidCrystal_I2C lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7); 
void setup() {
  // put your setup code here, to run once:
  rtc.begin();
  lcd.begin(20,4);

  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Date:");
  lcd.setCursor(1, 2);
  lcd.print("Time:");

}

void loop() {
  // put your main code here, to run repeatedly:
  String t_now = rtc.getTimeStr();
  String d_now = rtc.getDateStr();

  lcd.setCursor(1, 1);
  lcd.print(t_now);
  lcd.setCursor(1, 3);
  lcd.print(d_now);
  delay(1000);

}
