const int Redled=4;
void setup() {

  pinMode(Redled,OUTPUT);
 
}

void loop() {

  digitalWrite(Redled,HIGH);
  delay(2000);
  digitalWrite(Redled,LOW);
  delay(1000);
 
}