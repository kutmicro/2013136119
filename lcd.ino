#include <LiquidCrystal_I2C.h>
#include <Wire.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

int bpm = 60;
int rhythm = 4;
int count = 1;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);              
  lcd.init();
  lcd.backlight(); 
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);           
  lcd.print("bpm : ");     
  lcd.setCursor(6,0);
  lcd.print(bpm);
  lcd.setCursor(0,1);
  lcd.print("rhythm : ");
  lcd.setCursor(9,1);
  lcd.print(rhythm);
  lcd.setCursor(10,1);
  lcd.print("/4");
  
  if (count%rhythm == 1 ) {
    lcd.setCursor(count+10,0);
    lcd.print("!");
    count = count+1; 
    delay(1000);
  }
  if (count%rhythm == 2 || count%rhythm == 3 || count%rhythm == 0){
    lcd.setCursor(count+10,0);
    lcd.print("!");
    count = count+1; 
    delay(1000);
    if (count>rhythm){   
      count=1;           
      lcd.clear();      
    }
  }
}
