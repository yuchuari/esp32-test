
/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/
#include <DS1307RTC.h>
#include <TimeLib.h>
#include <LiquidCrystal_I2C.h>
#include "Wire.h"

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

tmElements_t tm;
bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}

void setup(){
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();


   bool parse=false;
  bool config=false;

  // get the date and time the compiler was run
  if (getDate(__DATE__) && getTime(__TIME__)) {
    parse = true;
    // and configure the RTC with this info
    if (RTC.write(tm)) {
      config = true;
    }

  
}
}
void loop(){
  tmElements_t tm;
 /* // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Hello, World!");
  delay(1000);
  // clears the display to print new message
  lcd.clear();
  // set cursor to first column, second row
  lcd.setCursor(0,1);
  lcd.print("Hello, World!");
  delay(1000);
  lcd.clear(); */
  mostrarFecha();
}

String a2Digitos(int numero) {
  if (numero >= 0 && numero < 10) {
    return "0" + String(numero);
  }
  else
  {
    return String(numero); 
  }
}

void mostrarHora()
{
  lcd.setCursor(0,1);
  lcd.print("Hora ");
  lcd.setCursor(5,1);
  lcd.print(a2Digitos(tm.Hour));
  lcd.setCursor(7,1);
  lcd.print(":");
  lcd.setCursor(8,1);
  lcd.print(a2Digitos(tm.Minute));
  lcd.setCursor(10,1);
  lcd.print(":");
  lcd.setCursor(11,1);
  lcd.print(a2Digitos(tm.Second));
}

void mostrarFecha()
{
  char *meses[] = {"", "ENE", "FEB", "MAR", "ABR", "MAY", "JUN", "JUL", "AGO", "SEP", "OCT", "NOV", "DIC"};
  lcd.setCursor(0,1);
  lcd.print(a2Digitos(tm.Day));
  lcd.setCursor(2,1);
  lcd.print(" de ");
  lcd.setCursor(6,1);
  lcd.print(meses[tm.Month]);
  lcd.setCursor(9,1);
  lcd.print(", ");
  lcd.setCursor(11,1);
  lcd.print(tmYearToCalendar(tm.Year));
}
