const int P = 5;
const int G = 6;
const int switch1 = 3; 
int switchstate = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(switch1,INPUT);
  pinMode(P,OUTPUT);
  pinMode(G,OUTPUT);  
}

void loop() {
  // put your main code here, to run repeatedly:
  switchstate = digitalRead(switch1);
   if(switchstate == HIGH )
    {
     digitalWrite(P,HIGH);
     digitalWrite(G,LOW);
     }
   else
    {
     digitalWrite(P,LOW);
     digitalWrite(G,HIGH);
    }
}