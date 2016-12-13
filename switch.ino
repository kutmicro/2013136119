int button = 10;          // push button
int prevstate = 0;        // 버튼 이전 상태
int buttonstate = 0;      // 버튼 현재 상태
int rhythmcount = 1;      // 박자 결정 변수

void setup() {
  // 버튼 입력
  pinMode(button, INPUT);
  Serial.begin(9600);
}

void loop() {
  // 버튼 상태를 읽음
  buttonstate = digitalRead(button);
  // 버튼이 이전상태와 다르면 (버튼을 누르면)                            
  if(buttonstate != prevstate){                                
    if(buttonstate == HIGH){         
      rhythmcount++;           // 카운트 증가
      if(rhythmcount > 3){     // 카운트가 3초과이면
        rhythmcount = 1;       // 다시 1로 변경
      }
    }
    else{
    }
  }
  prevstate = buttonstate;
  Serial.print(buttonstate);
  Serial.print("     rhythm : ");
  Serial.print(rhythmcount);
  Serial.print("\n");
  delay(1000);
}
