const int Redled = 4;
const int Yellowled = 5;
const int Blueled = 6;
const int Greenled = 7;
const int Orangeled = 8;
const int Purpleled = 9;
const int Pinkled = 10;
void setup() {
  // put your setup code here, to run once:

  pinMode(Redled, OUTPUT);
  pinMode(Yellowled, OUTPUT);
  pinMode(Blueled, OUTPUT);
  pinMode(Greenled, OUTPUT);
  pinMode(Orangeled, OUTPUT);
  pinMode(Purpleled, OUTPUT);
  pinMode(Pinkled, OUTPUT);
}

void loop() {

  digitalWrite(Pinkled, HIGH);
  delay(500);
  digitalWrite(Purpleled, HIGH);
  delay(500);
  digitalWrite(Orangeled, HIGH);
  delay(500);
  digitalWrite(Greenled, HIGH);
  delay(500);
  digitalWrite(Blueled, HIGH);
  delay(500);
  digitalWrite(Yellowled, HIGH);
  delay(500);
  digitalWrite(Redled, HIGH);
  delay(500);

  //////////////////////////////

  digitalWrite(Pinkled, LOW);
  delay(500);
  digitalWrite(Purpleled, LOW);
  delay(500);
  digitalWrite(Orangeled,LOW);
  delay(500);
   digitalWrite(Greenled,LOW);
  delay(500);
   digitalWrite(Blueled,LOW);
  delay(500);
  digitalWrite(Yellowled,LOW);
  delay(500);
  digitalWrite(Redled,LOW);
  delay(500);
}
