int bpmControl = A0;
int bpm;

void setup() {
  // put your setup code here, to run once:
  pinMode(bpmControl, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  bpm = analogRead(bpmControl);
  bpm = map(bpm, 0, 1023, 30, 181);
  Serial.println(bpm);
  delay(1000);
}
