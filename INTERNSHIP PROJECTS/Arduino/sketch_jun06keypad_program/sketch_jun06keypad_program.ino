#include<Keypad.h>
#include<LiquidCrystal.h>
const byte rows = 4;
const byte columns = 4;
char keys [rows][columns]={{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'},
};
byte rowPins[rows]= {0,1,2,3};
byte colPins[columns]= {4,5,6,7};
Keypad keypad = Keypad (makeKeymap (keys),rowPins,colPins,rows,columns);
const int Rs = 8;
const int En = 9;
const int D4 = 10;
const int D5 = 11;
const int D6 = 12;
const int D7 = 13;
LiquidCrystal lcd (Rs,En,D4,D5,D6,D7);
void setup() {
  // put your setup code here, to run once:
  
Serial.begin(9600);
  lcd.begin(16,2);
}
void loop(){
char key = keypad.getKey();
if( key != NO_KEY )
  {
    Serial.print(key);
  }
  // put your main code here, to run repeatedly:
   lcd.setCursor(0,0);
   lcd.print(" HELLO WORLD ");
}