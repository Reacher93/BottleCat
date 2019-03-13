//Gehört zum Master Sketch; Bottle-Cat

#include <LiquidCrystal_I2C.h>    //Benötigte Datenbank für LCD über I2C Ansteuerung

#define lcdColumns 16             //Anzahl Zeilen definiert
#define lcdRows 2                 //Anzahl Reihen definiert

LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);     //Definiert die Adresse, anzahl Reihen und Zeilen

void LCD_init(void){
  lcd.init();                    
  lcd.backlight();
}

void lcd_loop(){    //Raum und Flaschen Temp. Anzeige
  lcd.setCursor(0, 0);
  lcd.print("Raum:    ");
  lcd.print(TR);
  lcd.print((char) 223);
  lcd.print(" ");
  lcd.setCursor(0, 1);
  lcd.print("Flasche: ");
  lcd.print(TB1);
  lcd.print((char) 223);
  lcd.print(" ");
}

void lcd_cooling(int zeit){    //Anzeige zu kühlstellende Zeit
  lcd.clear();
  lcd.print("Rat der Katze:");
  lcd.setCursor(0, 1);
  lcd.print(zeit);
  lcd.print(" min k");
  lcd.print("\365");
  lcd.print("hlen");
}

void lcd_drink(int zeit){    //Anzeige Zeit zum trinken
  lcd.clear();
  lcd.print("Rat der Katze");
  lcd.setCursor(0, 1);
  lcd.print("Trinken in ");
  lcd.print(zeit);
  lcd.print(" min");
}

void lcd_animation(){   //Augen der Katze anzeigen
  lcd.clear();
  lcd.print(" 00        00");
  lcd.setCursor(0, 1);
  lcd.print(" 00        00");
  delay(1500);
  lcd.clear();
  lcd.print("   00        00");
  lcd.setCursor(0, 1);
  lcd.print("   00        00");
  delay(1500);
}

void lcd_clear(void){   //LCD löschen Funktion, da lcd  im Masterfile nich bekannt ist
  lcd.clear();
}
