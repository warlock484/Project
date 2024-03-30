// include the library code:
#include <LiquidCrystal.h>
#include <string>
#include <cmath>

LiquidCrystal lcd(19, 23, 18, 21, 22, 15);

int bitNr = 0;
char input;
std::string byteString = "00000000";

void printChar()
{
  int nr = 0;
  int putere = 0;
  
  for(int i = 7; i >= 0; i--)
  {
    nr += (byteString[i] - '0') * pow(2, putere++);
  }

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print((char)nr);
  lcd.print(" = ");
  lcd.print(nr);
  
  lcd.setCursor(0, 1);
  lcd.print(byteString.c_str());
}

void setup() 
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  Serial.print("Enter bits: ");
}

void loop() 
{
  if(Serial.available() > 0)
  {
    input = Serial.read();
    if(input == '0' || input == '1')
    {
       byteString[bitNr++] = input;
    }
    else if(input == 10)
    {
      printChar();
      bitNr = 0;
      byteString.clear();
    }
  }
  delay(100);
}
