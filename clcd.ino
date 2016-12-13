// LiquidCrystal_I2C.h 라이브러리와 Wire.h 라이브러리를 읽어옴
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// (CLCD_I2C 주소, 행, 열)
LiquidCrystal_I2C lcd(0x27, 16, 2);

int bpm = 60;
int rhythm = 4;   // 박자
int count = 1;    // 박자 카운트

void setup() {
  // lcd 시작, 초기화, 백라이트 on
  lcd.begin(16,2);              
  lcd.init();
  lcd.backlight(); 
}

void loop() {
  // cursor를 지정된 위치에 놓고, 출력
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

  // 박자를 셀 때마다 !를 출력하고 count를 증가시킴
  lcd.setCursor(count+10,0);
  lcd.print("!");
  count = count+1; 
  delay(1000);
  // 만약 카운트가 현재 박자 이상이 되면 1로 초기화
  if (count>rhythm){   
    count=1;           
    lcd.clear();      // 화면 초기화
  }
}
