const int p=3;
const int g=4;
 void setup() {
  // put your setup code here, to run once:
  pinMode(p,OUTPUT);
  pinMode(g,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(p,LOW);
  digitalWrite(g,HIGH);
  delay(200);
}
