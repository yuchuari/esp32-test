//#include <DS3231.h>

 
#include "RTClib.h"
 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4); //0x27 adalah alamat i2c di LCD
#include <Wire.h>
 
RTC_DS3231 rtc;
 
char daysOfTheWeek[7][4] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
 
int Day; 
int Month;
int Year; 
int Secs;
int Minutes;
int Hours;
 
String dofweek; // hari
 
String myDate; 
String myTime;
 
void setup () 
{
  Serial.begin(9600);
  lcd.begin();
  lcd.setCursor(2,0); 
  lcd.print("WELCOME TO"); 
  lcd.setCursor(2,1); 
  lcd.print("pauzan.com"); 
  delay(2000); // delay 2 detik
  lcd.clear();
 
  if (! rtc.begin()) {
  Serial.println("tidak menemukan RTC");
  while (1);
}
 
  if (rtc.lostPower()) {
  Serial.println("daya RTC hilang, set waktu");
 
  // Comment out below lines once you set the date and time.
  // Following line sets the RTC to the date &amp;amp;amp; time this sketch was compiled
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 
  // Following line sets the RTC with an explicit date and time
  // for example to set January 27 2017 at 12:56 you would call:
  // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));
}
}
 
void loop () 
{
  DateTime now = rtc.now();
  lcd.clear(); 
  Day = now.day(); 
  Month = now.month(); 
  Year = now.year();
  Secs = now.second(); 
  Hours = now.hour(); 
  Minutes = now.minute(); 
  dofweek = daysOfTheWeek[now.dayOfTheWeek()]; 
 
  myDate = myDate +dofweek+ ", "+ Day + "/" + Month + "/" + Year ; 
  myTime = myTime + Hours +":"+ Minutes +":" + Secs ; 
  // send to serial monitor
  Serial.println(dofweek); 
  Serial.println(myDate); 
  Serial.println(myTime);
  //Print on lcd
  lcd.setCursor(0,0);
  lcd.print("Date: "+myDate); 
  lcd.setCursor(0,1); 
  lcd.print("Hora: "+myTime); 
  lcd.setCursor(0,2); 
  lcd.print("Yandri J. Uchuari");
  lcd.setCursor(0,3); 
  lcd.print("yuchuari@outlook.com"); 
  myDate = ""; 
  myTime = ""; 
  delay(800);
}
