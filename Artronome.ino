// LiquidCrystal_I2C.h 라이브러리와 Wire.h 라이브러리를 읽어옴
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int ON = HIGH;
const int OFF = LOW;

int piezoPin = 8;         // Buzzer
int ledPin = 9;           // led 
int button = 10;          // push button
int bpmControl = A0;      // 가변저항
int bpm;                  // 빠르기                               
int count = 1;            // 박자 카운트
int first = 4186;         // 첫박 소리
int other = 33;           // 다른 박자 소리
int rhythm = 4;           // 박자
int buttonstate = 0;      // 버튼 현재 상태
int prevstate = 0;        // 버튼 이전 상태
int rhythmcount = 1;      // 박자 결정 변수

// (CLCD_I2C 주소, 행, 열)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  // 가변저항과 버튼은 입력, LED와 Buzeer은 출력
  pinMode(ledPin, OUTPUT);       
  pinMode(piezoPin, OUTPUT);     
  pinMode(bpmControl, INPUT);     
  pinMode(button, INPUT);         
  
  lcd.begin(16,2);                // lcd 시작
  lcd.init();                     // lcd 초기화
  lcd.backlight();                // lcd 백라이트 on
}

void loop()
{
  bpm = analogRead(bpmControl);        // 가변저항에서 읽은 아날로그 값을 디지털값으로 변경
  bpm = map(bpm, 0, 1023, 30, 180);    // bpm을 0~1023으로 구분한 값을 30~180으로 변경
  buttonstate = digitalRead(button);
  int led_pulse_time = 100;            
  int piezo_pulse_time = 1;            
  int delayTime = (60000 / bpm);       // bpm 값을 초단위로 변경

  lcd.setCursor(0,0);                  // lcd 출력할 위치
  lcd.print("bpm : ");                 // lcd 내용 출력
  lcd.setCursor(6,0);
  lcd.print(bpm);
  
  // 첫 박일 때
  if (count%rhythm == 1 ) {                
    digitalWrite(ledPin, HIGH);                // led on
    tone(piezoPin, first);                     // 부저를 first 음으로 출력
    delay(piezo_pulse_time);                   
    noTone(piezoPin);                           
    delay(led_pulse_time - piezo_pulse_time);  
    digitalWrite(ledPin, LOW);                 // led off
    lcd.setCursor(count+10,0);
    lcd.print("!");
    count = count+1;                           // 박자 카운트 증가 (첫박 외의 다른 박을 위해)
    delay(delayTime - led_pulse_time - piezo_pulse_time);
  }
  
  // 첫박 외의 다른 박자일 때
  if (count%rhythm == 2 || count%rhythm == 3 || count%rhythm == 0){
    digitalWrite(ledPin, HIGH);
    tone(piezoPin, other);
    delay(piezo_pulse_time);
    noTone(piezoPin);
    delay(led_pulse_time - piezo_pulse_time);
    digitalWrite(ledPin, LOW);
    lcd.setCursor(count+10,0);
    lcd.print("!");
    count = count+1;
    delay(delayTime - led_pulse_time - piezo_pulse_time);
    
    if (count>rhythm){    // 박자를 다 세면 count
      count=1;            // count를 1로 변경하고
      lcd.clear();        // lcd 박자 출력 지움
    }
  }
  
  // 버튼 누를때 마다 박자 카운트 증가
  if(buttonstate != prevstate){                                
    if(buttonstate == 1){         
      rhythmcount++;
      if(rhythmcount > 3){     // 카운트가 3초과이면
        rhythmcount = 1;       // 다시 1로 변경
      }
    }
    else{
    }
    prevstate = buttonstate;
  }
  
  // 버튼 누를 때 박자 변경
  switch(rhythmcount){                                        
    case 1:                     // 1번상태면 4/4박자
    rhythm = 4;
    lcd.setCursor(0,1);
    lcd.print("rhythm : ");
    lcd.setCursor(9,1);
    lcd.print(rhythm);
    lcd.setCursor(10,1);
    lcd.print("/4");
    break;
    case 2:                    // 2번상태면 3/4박자
    rhythm = 3;
    lcd.setCursor(0,1);
    lcd.print("rhythm : ");
    lcd.setCursor(9,1);
    lcd.print(rhythm);
    lcd.setCursor(10,1);
    lcd.print("/4");
    break;
    case 3:                   // 3번상태면 2/4박자
    rhythm = 2;
    lcd.setCursor(0,1);
    lcd.print("rhythm : ");
    lcd.setCursor(9,1);
    lcd.print(rhythm);
    lcd.setCursor(10,1);
    lcd.print("/4");
    break;
  }
}
