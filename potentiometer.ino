int bpmControl = A0;  // 가변저항
int bpm;

void setup() {
  pinMode(bpmControl, INPUT);   // 가변저항 입력
  Serial.begin(9600);
}

void loop() {
  // 가변저항에서 읽은 아날로그 값을 디지털값으로 변경
  bpm = analogRead(bpmControl);
  // bpm을 0~1023으로 구분한 값을 30~180으로 변경
  bpm = map(bpm, 0, 1023, 30, 180);
  Serial.println(bpm);
  delay(1000);
}
