/*
 * // http://gorgusgfx.se/?page_id=62
 * kod för att styra en DLR3416-display från Siemens
 * Nicu FLORICA tests 5 module HDLO-2416 
 * for future projects see http://arduinotehniq.com
 * or http://www.tehnic.go.ro
 * 
 * http://nicuflorica.blogspot.com/2016/11/afisaje-dhlo-2416-cu-4-caractere.html
 * https://github.com/tehniq3/HDLO-2416/blob/master/HDLO2416_DHT_RTC1.ino
 * ver.0 - change for Datecs DPD-201 (firmware 2.4/2004)
 */

#include <SoftwareSerial.h>
#define DATAOUT 6 
SoftwareSerial lcd(255, DATAOUT);  // This is required, to start an instance of an LCD (RX at pin D6)

// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


#include "DHT.h"
#define DHTPIN 12     // what pin we're connected to
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);
// NOTE: For working with a faster chip, like an Arduino Due or Teensy, you
// might need to increase the threshold for cycle counts considered a 1 or 0.
// You can do this by passing a 3rd parameter for this threshold.  It's a bit
// of fiddling to find the right value, but in general the faster the CPU the
// higher the value.  The default for a 16mhz AVR is a value of 6.  For an
// Arduino Due that runs at 84mhz a value of 30 works.
// Example to initialize DHT sensor for Arduino Due:
//DHT dht(DHTPIN, DHTTYPE, 30);

int timp = 250;
int timp2 = 1000;

float temperatura;
int umiditate;
int tzeci, tunit, tzecimi, trest;
int tsemn, ttot;
int hzeci, hunit;

byte hh, mm, ss;
byte yy, ll, dd, zz;

String text7 = "  niq_ro's clock on    DPD-201 display";
int i1,i2;
byte numar = 0;
unsigned long tprtc = 1000;
unsigned long tpcitirertc = 0;
unsigned long tpcitire = 0;
unsigned long tppauza = 60000;
 
void setup()
{
 dht.begin();
  lcd.begin(9600);  // Start the LCD at 9600 baud

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
   if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
//rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
// rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  
 
initializare();
mop(); 
for (int i = 0; i < text7.length(); i++)
  {
    lcd.write(255-2*text7[i]);   // Push each char 1 by 1 on each loop pass
  }
delay(5000);
temperatura = 10*dht.readTemperature();
umiditate = dht.readHumidity();
mop();
}
 
void loop()
{

if (millis() - tpcitirertc > tprtc)
{
DateTime now = rtc.now();
   /* 
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  */
    
//mop();
hh = now.hour();
mm = now.minute();
ss = now.second();
yy = now.year()-2000;
ll = now.month();
dd = now.day();
zz = now.dayOfTheWeek();

String text = "";
text = text + dd/10 + dd%10 + "/" + ll/10 + ll%10 + "/" + "20" + yy + "  ";
text = text + hh/10 + hh%10 + ":" + mm/10 + mm%10 + ":" + ss/10 + ss%10;

if (temperatura >= 0) 
{
  tsemn = 1;
  ttot = temperatura;
}
if (temperatura < 0) 
{
  tsemn = -1;
  ttot = -temperatura;
}

tzeci = ttot/100;
trest = ttot%100;
tunit = trest/10;
tzecimi = trest%10;

hzeci = umiditate/10;
hunit = umiditate%10;


String text1 = "";
text1 = text1 + "Temperature: ";
  if (tsemn == -1)
  {
   if (tzeci > 0)
   text1 = text1 + "-" + tzeci;
   else
   text1 = text1 + " -";
  }
  else
  if (tsemn == 1)
  {
   if (tzeci > 0)
   text1 = text1 + "+" + tzeci;
   else
   text1 = text1 + " +";
  }
  else
   text1 = text1 + "  ";

text1 = text1 + tunit + "." + tzecimi + "`C";

String text2 = "";
text2 = text2 + "Air Humidity:  ";
 if (hzeci == 0)
text2 = text2 + " "+ hunit + "%RH";
 else
text2 = text2 + hzeci + hunit + "%RH";

 for (int i = 0; i < text.length(); i++)
  {
    lcd.write(255-2*text[i]);   // Push each char 1 by 1 on each loop pass
  }

if (numar < 5)
{
for (int i = 0; i < text1.length(); i++)
  {
    lcd.write(255-2*text1[i]);   // Push each char 1 by 1 on each loop pass
  }
}
else
{
for (int i = 0; i < text2.length(); i++)
  {
    lcd.write(255-2*text2[i]);   // Push each char 1 by 1 on each loop pass
  }
}
numar = numar + 1;
if (numar > 10)
    numar = 0;
tpcitirertc = millis();
}  //

if (millis() - tpcitire > tppauza) 
{  
temperatura = 10*dht.readTemperature();
umiditate = dht.readHumidity();
//temperatura = random(-150, 350);  // for test
//umiditate = random (10, 90);  // for test
tpcitire = millis();
}

}  // end main program
 

void mop()
{
  lcd.write(231); // CLR (clear the display)
  delay(10);
}  // end 'mop'subroutine     

void initializare()
{
  lcd.write(1);  // SPACE
  lcd.write(231); // CLR (clear the display)
  
  // initialize display
  lcd.write(201); // ESC
  lcd.write(127); // @ 
delay(1000);
}
