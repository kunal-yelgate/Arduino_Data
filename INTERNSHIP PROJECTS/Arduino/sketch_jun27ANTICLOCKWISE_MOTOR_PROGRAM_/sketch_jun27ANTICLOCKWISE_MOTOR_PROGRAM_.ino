const int P = 2;
const int G = 3;
void setup() {
  // put your setup code here, to run once:
  pinMode(P,OUTPUT);
  pinMode(G,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(P,LOW);
digitalWrite(G,HIGH);
}
