const int leda=1;
const int ledb=2;
const int ledc=3;
const int ledd=4;
const int lede=5;
const int ledf=6;
const int ledg=7;

void setup() {

  pinMode(leda,OUTPUT);
  pinMode(ledb,OUTPUT);
  pinMode(ledc,OUTPUT);
  pinMode(ledd,OUTPUT);
  pinMode(lede,OUTPUT);
  pinMode(ledf,OUTPUT);
  pinMode(ledg,OUTPUT);
 
}

void loop() {
   //for 0
  digitalWrite(leda,LOW);
  digitalWrite(ledb,LOW);
  digitalWrite(ledc,LOW);
  digitalWrite(ledd,LOW);
  digitalWrite(lede,LOW);
  digitalWrite(ledf,LOW);
  digitalWrite(ledg,HIGH);
  delay(500);


  //for 1
  digitalWrite(leda,HIGH);
  digitalWrite(ledb,LOW);
  digitalWrite(ledc,LOW);
  digitalWrite(ledd,HIGH);
  digitalWrite(lede,HIGH);
  digitalWrite(ledf,HIGH);
  digitalWrite(ledg,HIGH);
  delay(500);

  //for 2
  digitalWrite(leda,LOW);
  digitalWrite(ledb,LOW);
  digitalWrite(ledc,HIGH);
  digitalWrite(ledd,LOW);
  digitalWrite(lede,LOW);
  digitalWrite(ledf,HIGH);
  digitalWrite(ledg,LOW);
  delay(500);
  // for 3
  digitalWrite(leda,LOW);
  digitalWrite(ledb,LOW);
  digitalWrite(ledc,LOW);
  digitalWrite(ledd,LOW);
  digitalWrite(lede,HIGH);
  digitalWrite(ledf,HIGH);
  digitalWrite(ledg,LOW);
  delay(500);

  //for 4
  digitalWrite(leda,HIGH);
  digitalWrite(ledb,LOW);
  digitalWrite(ledc,LOW);
  digitalWrite(ledd,HIGH);
  digitalWrite(lede,HIGH);
  digitalWrite(ledf,LOW);
  digitalWrite(ledg,LOW);
  delay(500);

   //for 5
  digitalWrite(leda,LOW);
  digitalWrite(ledb,HIGH);
  digitalWrite(ledc,LOW);
  digitalWrite(ledd,LOW);
  digitalWrite(lede,HIGH);
  digitalWrite(ledf,LOW);
  digitalWrite(ledg,LOW);
  delay(500);

  //for 6
  digitalWrite(leda,LOW);
  digitalWrite(ledb,HIGH);
  digitalWrite(ledc,LOW);
  digitalWrite(ledd,LOW);
  digitalWrite(lede,LOW);
  digitalWrite(ledf,LOW);
  digitalWrite(ledg,LOW);
  delay(500);

  //for 7
   digitalWrite(leda,LOW);
  digitalWrite(ledb,LOW);
  digitalWrite(ledc,LOW);
  digitalWrite(ledd,HIGH);
  digitalWrite(lede,HIGH);
  digitalWrite(ledf,HIGH);
  digitalWrite(ledg,HIGH);
  delay(500);

  //for 8
   digitalWrite(leda,LOW);
  digitalWrite(ledb,LOW);
  digitalWrite(ledc,LOW);
  digitalWrite(ledd,LOW);
  digitalWrite(lede,LOW);
  digitalWrite(ledf,LOW);
  digitalWrite(ledg,LOW);
  delay(500);

//for 9
   digitalWrite(leda,LOW);
  digitalWrite(ledb,LOW);
  digitalWrite(ledc,LOW);
  digitalWrite(ledd,LOW);
  digitalWrite(lede,HIGH);
  digitalWrite(ledf,LOW);
  digitalWrite(ledg,LOW);
  delay(500);
}

