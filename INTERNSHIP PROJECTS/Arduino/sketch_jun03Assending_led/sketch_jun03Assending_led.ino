const int Redled = 4;
const int Yellowled = 5;
const int Blueled = 6;
const int Greenled = 7;
const int Orangeled = 8;
const int Purpleled = 9;
const int Pinkled = 10;
void setup() {
  // put your setup code here, to run once:

 pinMode(Redled,OUTPUT);
 pinMode(Yellowled,OUTPUT);
 pinMode(Blueled,OUTPUT);
 pinMode(Greenled,OUTPUT);
 pinMode(Orangeled,OUTPUT);
 pinMode(Purpleled,OUTPUT);
 pinMode(Pinkled,OUTPUT);
 
}

void loop() {

  digitalWrite(Redled,HIGH);
  delay(200);
  digitalWrite(Yellowled,HIGH);
  delay(200);
  digitalWrite(Blueled,HIGH);
  delay(200);
  digitalWrite(Greenled,HIGH);
  delay(200);
  digitalWrite(Orangeled,HIGH);
  delay(200);
  digitalWrite(Purpleled,HIGH);
  delay(200);
  digitalWrite(Pinkled,HIGH);
  delay(200);
  
  digitalWrite(Redled,LOW);
  delay(200);
  digitalWrite(Yellowled,LOW);
  delay(200);
  digitalWrite(Blueled,LOW);
  delay(200);
  digitalWrite(Greenled,LOW);
  delay(200);
  digitalWrite(Orangeled,LOW);
  delay(200);
  digitalWrite(Purpleled,LOW);
  delay(200);
  digitalWrite(Pinkled,LOW);
  delay(200);
 
}