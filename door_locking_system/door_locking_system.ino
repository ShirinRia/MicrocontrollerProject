#include <LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>
Servo myservo;//servo motor er object
LiquidCrystal lcd(A4, A5, A3, A2, A1, A0);
const byte rows=4;
const byte cols=3;
int t=0;
char key[rows][cols]={
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[rows]={0,1,11,3};
byte colPins[cols]={4,5,6};
Keypad keypad= Keypad(makeKeymap(key),rowPins,colPins,rows,cols);
char* password="0123";
int currentposition=0;
int pirState;
char code;
void setup()
{
displayscreen();
myservo.attach(9); //Servo motor connection
lcd.begin(16,2);
pinMode(8,OUTPUT);
pinMode(12,OUTPUT); 
pinMode(2, INPUT);
myservo.write(0);
}
 
void loop()
{
int l=0;
if( currentposition==0)
{
displayscreen();
}
code=keypad.getKey();
if(code!=NO_KEY)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("PASSWORD:");
lcd.setCursor(7,1);
lcd.print(" ");
lcd.setCursor(7,1);
for(l=0;l<=currentposition;++l)
{ 
lcd.print("*");
}
if (code==password[currentposition])
{
++currentposition;
if(currentposition==4)
{
unlockdoor();
currentposition=0; 
} 
}
else
{
incorrect();
currentposition=0;
}
}
} 
//Function 1- OPEN THE DOOR
void unlockdoor()
{
delay(200);
myservo.write(90); 
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(1,0);
digitalWrite(8,HIGH);
lcd.print("Access Granted");
lcd.setCursor(4,1);
lcd.println("WELCOME!!");

counterbeep();
delay(1000);
currentposition=0; 
lcd.clear();
displayscreen();
}
 
//Function 2- Wrong code 
void incorrect()
{
delay(500);
myservo.write(0); 
digitalWrite(8,LOW);
lcd.clear();
lcd.setCursor(1,0);
lcd.print("CODE");
lcd.setCursor(6,0);
lcd.print("INCORRECT");
lcd.setCursor(15,1);
lcd.println(" ");
delay(500);
lcd.clear();
++t;
if(t==3){
digitalWrite(12,HIGH);
tone(12,1000);
lcd.noDisplay();
} 
}

//Function 4 - DISPLAY FUNCTION
void displayscreen()
{
lcd.setCursor(0,0);
lcd.println("ENTER THE CODE");
lcd.setCursor(1 ,1);
lcd.println("TO OPEN DOOR");
}

//Function 5 - Count down
void counterbeep()
{
delay(1000); 
pirState = digitalRead(2);
if(pirState==LOW){
lcd.clear();
lcd.setCursor(2,0);
lcd.print("RE-LOCKING");
lcd.setCursor(12,0);
lcd.print(".");
delay(200);
lcd.setCursor(13,0);
lcd.print(".");
delay(200);
lcd.setCursor(14,0);
lcd.print(".");
delay(200);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Someone is in");
lcd.setCursor(1,1);
lcd.print("the room");
delay(500);
lcd.clear();
lcd.setCursor(4,0);
myservo.write(0); 
lcd.print("LOCKED!");
delay(300);
}
else if(pirState==HIGH){
lcd.clear(); 
lcd.setCursor(2,15);
lcd.println(" ");
lcd.setCursor(2,14);
lcd.println(" ");
lcd.setCursor(2,0);
delay(100);
lcd.println("GET IN WITHIN:");
 
lcd.setCursor(4,1);
lcd.print("5");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(500);
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); //2
lcd.print("4");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(100);

lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); 
lcd.print("3");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(100);
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); 
lcd.print("2");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(100);
lcd.setCursor(4,1);
lcd.print("1");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(100);
delay(40);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("RE-LOCKING");
delay(100);
lcd.setCursor(12,0);
lcd.print(".");
delay(200);
lcd.setCursor(13,0);
lcd.print(".");
delay(200);
lcd.setCursor(14,0);
lcd.print(".");
delay(200);
lcd.clear();
lcd.setCursor(4,0);
digitalWrite(8,LOW);
t=0;
lcd.clear();
lcd.setCursor(2,0);
lcd.print("No one Entered");
delay(200);
lcd.clear();
lcd.setCursor(2,0);
myservo.write(0); 
lcd.print("LOCKED!");
delay(400);
}
}
