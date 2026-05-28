const int leda=1;
const int ledb=2;
const int ledc=3;
void setup() {
  // put your setup code here, to run once:
  pinMode(leda,OUTPUT);
  pinMode(ledb,OUTPUT);
  pinMode(ledc,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(leda,HIGH);
  digitalWrite(ledb,HIGH);
   digitalWrite(ledc,HIGH);
  delay(500);
  digitalWrite(leda,LOW);
   digitalWrite(ledb,LOW);
  digitalWrite(ledc,LOW);
   delay(500);
}
