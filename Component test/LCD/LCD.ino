
/*

LCD 16x2 I2C test

This code is used to test the LCD 16x2 I2C	

method:

1. Connect the LCD 16x2 I2C to the arduino board
2. Connect the arduino board to the computer
3. The LCD should print "Hello World"

Components:

1. Arduino board
2. LCD 16x2 I2C
3. Jumper wires
4. Breadboard

*/

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2); // I2C address 0x27, 16 column and 2 rows

void setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();
}

void loop()
{
  lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("Arduino");        // print message at (0, 0)
  lcd.setCursor(2, 1);         // move cursor to   (2, 1)
  lcd.print("Chamodi"); // print message at (2, 1)
  delay(2000);                 // display the above for two seconds

  lcd.clear();                  // clear display
  lcd.setCursor(3, 0);          // move cursor to   (3, 0)
  lcd.print("Ape");        // print message at (3, 0)
  lcd.setCursor(0, 1);          // move cursor to   (0, 1)
  lcd.print("Sene"); // print message at (0, 1)
  delay(2000);                  // display the above for two seconds
}


}
