const int led = 2;
const int ldr = A4;
int ldrvalue;
void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  pinMode(ldr,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  ldrvalue = analogRead(ldr);
  if(ldrvalue<=300 )
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
