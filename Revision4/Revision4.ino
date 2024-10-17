
//#include <Adafruit_SSD1306.h>
//#include <SimpleDHT.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#define led1 7
#define led2 8
int data, flag = 2;
int tempPin=A2;
LiquidCrystal lcd(A4, A5, A3, 9, A1, A0);
Servo myservo;
int pos=0; // position of servo motor
int val;
void setup()
{
  //pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  myservo.attach(10);
  Serial.begin(9600);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  lcd.begin(16, 2);                       
  lcd.setCursor (0,0);                   
  lcd.print("                ");
  lcd.setCursor (0,1);
  lcd.print("                ");
}

void loop()
{
  while( Serial.available() )
  {
    data = Serial.read();

    if (data == '1')
    {
      flag = 1;
    }
    else if(data == '0')
    {
      flag = 0;
    }
  }
  if(flag == 1)
  {
    if(checkTemp()==true)
    {
      lcd.setCursor (0,0);
      lcd.print("Access Granted ");
      openandclose();
      //delay(200);
      //digitalWrite(led, LOW);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      /*digitalWrite(led3, LOW);
      delay(200);*/
    }
    else if(checkTemp()==false){
      lcd.setCursor (0,0);
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      lcd.clear();
      lcd.print("Temp too high");
      delay(1000);
    }
    }
     else if (flag == 0)
    {
      lcd.setCursor (0,0);
      lcd.print("Face Unidentified  ");
      //digitalWrite(led, LOW);
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
    }
}
boolean checkTemp(){ //Function to check temperature
  val=analogRead(tempPin);
  float mv=(val/1024.0)*5000;
  float cel=mv/10;
  Serial.print("Temperature=");
  Serial.print(cel);
  Serial.print("C");
  Serial.println();

  if(cel<38)
  {
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    return true;
  }
  else
  {
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    return false;
  }
  delay(500);
}
void openandclose(){
  for(pos = 180; pos>=0; pos-=5) // open the door
  {
  myservo.write(pos); //To turn the servo
  delay(5); 
}
delay(2000);

 
for(pos = 0; pos <= 180; pos +=5) // close the door
  { // in steps of 1 degree
    myservo.write(pos); 
    delay(15);
   
   
    lcd.clear();

 
  }
}
