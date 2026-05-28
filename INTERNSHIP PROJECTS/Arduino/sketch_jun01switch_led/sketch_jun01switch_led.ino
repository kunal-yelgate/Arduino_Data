const int led1 = 7;
const int switch1 = 3; 
int switchstate = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(led1,OUTPUT);
  pinMode(switch1,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   switchstate = digitalRead(switch1);
   if(switchstate == HIGH )
    {
     digitalWrite(led1,HIGH);
     }
   else
    {
     digitalWrite(led1,LOW);
    }
}
