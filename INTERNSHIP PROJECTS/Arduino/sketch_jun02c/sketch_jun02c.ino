const int N_Redled=1;
const int N_Yellowled=2;
const int N_Greenled=3;
const int S_Redled=4;
const int S_Yellowled=5;
const int S_Greenled=6;
const int E_Redled=7;
const int E_Yellowled=8;
const int E_Greenled=9;
const int W_Redled=10;
const int W_Yellowled=11;
const int W_Greenled=12;

void setup() {

  pinMode(N_Redled,OUTPUT);
  pinMode(N_Yellowled,OUTPUT);
  pinMode(N_Greenled,OUTPUT);
  pinMode(S_Redled,OUTPUT);
  pinMode(S_Yellowled,OUTPUT);
  pinMode(S_Greenled,OUTPUT);
  pinMode(E_Redled,OUTPUT);
  pinMode(E_Yellowled,OUTPUT);
  pinMode(E_Greenled,OUTPUT);
  pinMode(W_Redled,OUTPUT);
  pinMode(W_Yellowled,OUTPUT);
  pinMode(W_Greenled,OUTPUT);
 
}

void loop() {
   //east to west
  digitalWrite(N_Redled,HIGH);
  digitalWrite(S_Redled,HIGH);
  digitalWrite(E_Greenled,HIGH);
  digitalWrite(W_Greenled,HIGH);
  delay(5000);
  digitalWrite(E_Greenled,LOW);
  digitalWrite(W_Greenled,LOW);
  digitalWrite(E_Yellowled,HIGH);
  digitalWrite(W_Yellowled,HIGH);
  delay(2000);
  digitalWrite(E_Yellowled,LOW);
  digitalWrite(W_Yellowled,LOW);
  digitalWrite(E_Redled,HIGH);
  digitalWrite(W_Redled,HIGH);
  delay(1000);
  //south to north
  digitalWrite(S_Redled,LOW);
  digitalWrite(N_Redled,LOW);
  digitalWrite(N_Greenled,HIGH);
  digitalWrite(S_Greenled,HIGH);
  delay(5000);
  digitalWrite(N_Greenled,LOW);
  digitalWrite(S_Greenled,LOW);
  digitalWrite(N_Yellowled,HIGH);
  digitalWrite(S_Yellowled,HIGH);
  delay(2000);
  digitalWrite(N_Yellowled,LOW);
  digitalWrite(S_Greenled,LOW);
  digitalWrite(E_Redled,HIGH);
  digitalWrite(W_Redled,HIGH);
  delay(2000);
  

 
}