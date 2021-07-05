// https://www.sparkfun.com/tutorials/289
// adapted by niq_ro from http://nicuflorica.blogspot.com/

#include <SoftwareSerial.h>

SoftwareSerial lcd(255, 2);  // This is required, to start an instance of an LCD (RX at pin D2)

void setup()
{
  lcd.begin(9600);  // Start the LCD at 9600 baud
//  Serial.begin(9600);

  lcd.write(231); // CLR
}

void loop()
{
  lcd.write(35); // n
  lcd.write(45); // i
  lcd.write(29); // q
  lcd.write(65); // _
  lcd.write(27); // r
  lcd.write(33); // o
  lcd.write(1); // space
  
  lcd.write(25); // s
  lcd.write(61); // a
  lcd.write(13); // y
  
  lcd.write(1); // space

  lcd.write(111); // H
  lcd.write(117); // E
  lcd.write(103); // L
  lcd.write(103); // L
  lcd.write(97); // O

  lcd.write(1); // space

  lcd.write(23); // t
  lcd.write(33); // o

  lcd.write(1); // space
  lcd.write(1); // space
  lcd.write(1); // space
  lcd.write(1); // space
  lcd.write(1); // space

  lcd.write(125); // A
  lcd.write(39); // l
  lcd.write(53); // e
  lcd.write(41); // k
  lcd.write(25); // s
  lcd.write(61); // a
  lcd.write(35); // n
  lcd.write(55); // d
  lcd.write(53); // e
  lcd.write(27); // r

  lcd.write(1); // space

  lcd.write(189); // !
 
  delay (3000); 
  lcd.write(231); // CLR
  /*
  // self test
  lcd.write(193); // US
  lcd.write(127); // @
  */
  delay (3000);
  
   }
