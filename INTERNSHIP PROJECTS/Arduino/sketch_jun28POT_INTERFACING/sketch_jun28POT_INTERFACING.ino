const int led = 2;
const int pot = A4;
int potvalue;
void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  pinMode(pot,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  potvalue = analogRead(pot);
  if(potvalue<=potvalue )
   {
    digitalWrite(led,HIGH);
    delay(500);
   }
   else
   {
    digitalWrite(led,LOW);
    delay(1000);
   }
}

