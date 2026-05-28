const int led1 = 0;
const int led2 = 1;
const int led3 = 2;
const int led4 = 3;
const int led5 = 4;
const int led6 = 5;
const int led7 = 6;
void setup() {
  // put your setup code here, to run once:

 pinMode(led1,OUTPUT);
 pinMode(led2,OUTPUT);
 pinMode(led3,OUTPUT);
 pinMode(led4,OUTPUT);
 pinMode(led5,OUTPUT);
 pinMode(led6,OUTPUT);
 pinMode(led7,OUTPUT);
 
}

void loop() {

  digitalWrite(led1,HIGH);
  delay(200);
  digitalWrite(led2,HIGH);
  delay(200);
  digitalWrite(led3,HIGH);
  delay(200);
  digitalWrite(led4,HIGH);
  delay(200);
  digitalWrite(led5,HIGH);
  delay(200);
  digitalWrite(led6,HIGH);
  delay(200);
  digitalWrite(led7,HIGH);
  delay(200);
  
  digitalWrite(led1,LOW);
  delay(200);
  digitalWrite(led2,LOW);
  delay(200);
  digitalWrite(led3,LOW);
  delay(200);
  digitalWrite(led4,LOW);
  delay(200);
  digitalWrite(led5,LOW);
  delay(200);
  digitalWrite(led6,LOW);
  delay(200);
  digitalWrite(led7,LOW);
  delay(200);
 
}