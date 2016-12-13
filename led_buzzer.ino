int piezoPin = 8;     // Buzzer
int ledPin = 9;       // LED
int first = 4186;     // 첫 박자 소리
int other = 33;       // 다른 박자 소리
int count = 1;        // 박자 카운트
int rhythm = 4;       // 박자

void setup() {
  // LED, Buzzer 출력
  pinMode(ledPin, OUTPUT);       
  pinMode(piezoPin, OUTPUT);
}

void loop() {
  // delay 시간
  int led_pulse_time = 100;            
  int piezo_pulse_time = 1;            
  int delayTime = 1000;
  
  // 첫 박일 때
  if (count%rhythm == 1 ) {                
    digitalWrite(ledPin, HIGH);                             // LED HIGH상태 (on)      
    tone(piezoPin, first);                                  // Buzzer를 첫 음으로 출력
    delay(piezo_pulse_time);                                // 소리 지속시간
    noTone(piezoPin);                                       // 소리 멈춤
    delay(led_pulse_time - piezo_pulse_time);               // LED 지속시간
    digitalWrite(ledPin, LOW);                              // LED LOW상태 (off)
    delay(delayTime - led_pulse_time - piezo_pulse_time);   // LED off 시간
    count = count+1;                                        // count 증가
  }
  
  // 첫박 외의 다른 박자일 때
  if (count%rhythm == 2 || count%rhythm == 3 || count%rhythm == 0){  
    digitalWrite(ledPin, HIGH);
    tone(piezoPin, other);
    delay(piezo_pulse_time);
    noTone(piezoPin);
    delay(led_pulse_time - piezo_pulse_time);
    digitalWrite(ledPin, LOW);
    delay(delayTime - led_pulse_time - piezo_pulse_time);
    count = count+1;
    // count가 rhythm보다 크면 count를 1로 변환
    if (count>rhythm){
      count=1;
    }
  }
}
