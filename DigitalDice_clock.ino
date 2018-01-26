#define Pin_Clock 12
void setup() {
  // put your setup code here, to run once:
  pinMode(Pin_Clock, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Pin_Clock, HIGH);
  delay(10);
  digitalWrite(Pin_Clock, LOW);
  delay(10);
}
