int piezoPin = 8;      
int ledPin = 9;  
int first = 4186;         
int other = 33;
int count = 1;
int rhythm = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);       
  pinMode(piezoPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int led_pulse_time = 100;            
  int piezo_pulse_time = 1;            
  int delayTime = 1000;
  
  // 첫 박일 때
  if (count%rhythm == 1 ) {                
    digitalWrite(ledPin, HIGH);               
    tone(piezoPin, first);                   
    delay(piezo_pulse_time);                   
    noTone(piezoPin);                           
    delay(led_pulse_time - piezo_pulse_time);  
    digitalWrite(ledPin, LOW);                 
    delay(delayTime - led_pulse_time - piezo_pulse_time);
    count = count+1;
  }
  
  // 첫박 외의 다른 박자일 때
  if (count%rhythm == 2 || count%rhythm == 3 || count%rhythm == 0){                                                       // 다른 박자에 소리 출력
    digitalWrite(ledPin, HIGH);
    tone(piezoPin, other);
    delay(piezo_pulse_time);
    noTone(piezoPin);
    delay(led_pulse_time - piezo_pulse_time);
    digitalWrite(ledPin, LOW);
    delay(delayTime - led_pulse_time - piezo_pulse_time);
    count = count+1;
    if (count>rhythm){
      count=1;
    }
  }
}
