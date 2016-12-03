int button = 10;
int prevstate = 0;        
int buttonstate = 0;
int rhythmcount = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonstate = digitalRead(button);                               
  if(buttonstate != prevstate){                                
    if(buttonstate == HIGH){         
      rhythmcount++;
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
