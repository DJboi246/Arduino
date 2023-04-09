const int outputpin=22;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int anologvalue = analogRead(A0);
  
  analogWrite(outputpin,anologvalue/4);
}
