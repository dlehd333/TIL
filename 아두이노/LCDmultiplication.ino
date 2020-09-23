#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int n1 = 2, n2 = 1;

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
}


void loop()
{
  char buffer[20];
  
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("multiplication");
  
  lcd.setCursor(0, 1);
  sprintf(buffer, "%d x %d = %d", n1, n2, n1*n2);
  lcd.print(buffer);

  n2++;
  if(n2 == 10)
  {
    n1++;
    n2 = 1;
    if(n1 == 10)
      n1 = 2;
  }

  delay(500);
}
