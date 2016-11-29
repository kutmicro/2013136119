/*
 *
 * Driver for Arduino-based metronome with keypad input.
 * By Ken Schwarz, July 29, 2012.
 *
 * Defaults at boot-time to 60 bpm (beat-per-minute).
 * Uses Velleman 12-key keypad for input (UPC 836479000001).
 * Press '*' to stop metronome and input new ppm.
 * Must enter 3-digit amount. For example, enter 120 bpm with "*120" and 60 bpm with "*060"
 *
 */
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int ON = HIGH;
const int OFF = LOW;

int piezoPin = 30;
int ledPin = 3;
int bpm = 60;                                                  // 기본 bpm 설정 : 60
int keypad[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};             // 키패드 0~9
int count = 1;
int first = 1319;                                              // 첫박 소리
int other = 1047;                                              // 다른 박자 소리
int button = 31;
int rhythm = 4;                                                // 박자
int buttonstate = 0;
int prevstate = 0;
int rhythmcount = 1;

LiquidCrystal_I2C lcd(0x27, 16, 2);


/*
 * setup() ?this function runs once when you turn your Arduino on
 */
 void read_keypad()
{
  int digit_index;
  int key_index;
  int key_read;
  int key_pressed;
  
  digitalWrite(ledPin, LOW);                                   // 입력중 LED OFF

  bpm = 0;
  for (digit_index = 1; digit_index <=3; digit_index ++) {     // 항상 3자리로 입력
    bpm *= 10;                                                 // 입력할때마다 자릿수 변경
    key_pressed = 0;
    while (!key_pressed) {                                     // 키패드 누르는동안 루프
      for (key_index = 0; key_index <=9; key_index++) {        // 키패드 스캔
        key_read = !digitalRead(keypad[key_index]);
        if (key_read) {
          key_pressed = 1;
          bpm += key_index;                                    
          while (!digitalRead(keypad[key_index]));             // 키패드가 실행될 때까지 루프
        }
      }
    }
  }
}

void setup()
{
  pinMode(ledPin, OUTPUT);                                     // Initialize output pins
  pinMode(piezoPin, OUTPUT);
  
  int key_index;
  for (key_index = 0; key_index <=9; key_index++)              // Initialize input pins
    pinMode(keypad[key_index], INPUT);

  attachInterrupt(0, read_keypad, FALLING);                    // *키를 누르면 bpm입력

  lcd.begin(16,2);              // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  lcd.init();
  lcd.backlight();                  // start with a blank screen
}

/*
 * loop() ?this function will start after setup finishes and then repeats
 */
void loop()
{
  int led_pulse_time = 100;                                    // Duration of LED pulse in milliseconds
  int piezo_pulse_time = 1;                                    // Duration of piezo tone in milliseconds
  int delayTime = (60000 / bpm);                               // Time between LED pulses' rising edges

  lcd.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
  lcd.print("bpm : ");      // change text to whatever you like. keep it clean!
  lcd.setCursor(6,0);
  lcd.print(bpm);
  
  if (count%rhythm == 1 ) {                                    // 첫 박에 소리 출력
    digitalWrite(ledPin, HIGH);                                // Turn on LED
    tone(piezoPin, first);                                     // Turn on piezo
    delay(piezo_pulse_time);                                   // Wait while piezo on
    noTone(piezoPin);                                          // Turn off piezo
    delay(led_pulse_time - piezo_pulse_time);                  // Wait while LED on, less piezo time
    digitalWrite(ledPin, LOW);                                 // Turn off LED
    delay(delayTime - led_pulse_time - piezo_pulse_time);      // Wait while LED off
    lcd.setCursor(1,1);
    lcd.print("!");
    count = count+1;
  }
  if (count%rhythm == 2 || count%rhythm == 3 || count%rhythm == 0){                                                       // 다른 박자에 소리 출력
    digitalWrite(ledPin, HIGH);
    tone(piezoPin, first);
    delay(piezo_pulse_time);
    noTone(piezoPin);
    delay(led_pulse_time - piezo_pulse_time);
    digitalWrite(ledPin, LOW);
    delay(delayTime - led_pulse_time - piezo_pulse_time);
    lcd.setCursor(count,1);
    lcd.print("!");
    count = count+1;
    if (count>rhythm){
      count=1;
      lcd.clear();
    }
  }
  
  buttonstate = digitalRead(button);
  if(buttonstate != prevstate){                                
    if(buttonstate == 1){                                      // 버튼 누를때 마다 박자 카운트 증가
      rhythmcount++;
      if(rhythmcount > 3){                                     // 카운트가 3초과이면 다시 1로 변경
        rhythmcount = 1;
      }
    }
    else{
    }
    prevstate = buttonstate;
  }
  switch(rhythmcount){                                        
    case 1:                                                    // 1번상태면 4/4박자
    rhythm = 4;
    break;
    case 2:                                                    // 2번상태면 3/4박자
    rhythm = 3;
    break;
    case 3:                                                    // 3번상태면 2/4박자
    rhythm = 2;
    break;
  }
}
