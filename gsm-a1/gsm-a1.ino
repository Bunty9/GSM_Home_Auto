#include <SoftwareSerial.h>


SoftwareSerial mySerial(3, 2);

#define Fan 3
#define Light 4
#define TV 5

int temp=0,i=0;

char str[15];
char ph[] = "+919420490305";

void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(Fan, OUTPUT);
  pinMode(Light, OUTPUT);
  pinMode(TV, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(TV, HIGH);
  digitalWrite(Light, HIGH);
  digitalWrite(Fan, HIGH);
  Serial.println("Initializing..."); 
  delay(1000);
  mySerial.println("AT+CNMI=2,2,0,0,0");
  delay(1000);
  mySerial.println("System is ready to receive SMS commands.");
  delay(500);
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  delay(500);
  mySerial.println("AT+CMGS=\"+919420490305\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  delay(500);

}

void loop()
{ 
  updateSerial();
  serialEvent();
  if(temp==1)
  { check();
    temp=0;
    i=0;
  }
  
}

void serialEvent() 
 {
  while(mySerial.available()) 
  {
    if(mySerial.find("#A."))
    {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
      while (mySerial.available()) 
      {
      char inChar=mySerial.read();
      str[i++]=inChar;
      if(inChar=='*')
      {
        temp=1;
        return;
      } 
      } 
    }
   }
 }

void check()
{
   if(!(strncmp(str,"tv on",5)))
    {
      digitalWrite(TV, LOW);
      delay(200);
      Serial.println("TV ON");
    }  
   
   else if(!(strncmp(str,"tv off",6)))
    {
      digitalWrite(TV, HIGH);
      Serial.println("TV OFF");
      delay(200);

    }
  
    else if(!(strncmp(str,"fan on",5)))
    {
      digitalWrite(Fan, LOW);
      delay(200);
      Serial.println("fan on");
    }
 
    else if(!(strncmp(str,"fan off",7)))
    {
      digitalWrite(Fan, HIGH);
      delay(200);
      Serial.println("fan off");


    }
 
    else if(!(strncmp(str,"light on",8)))
    {
      digitalWrite(Light, LOW);
      delay(200);
      Serial.println("light on");

    }
 
    else if(!(strncmp(str,"light off",9)))
    {
      digitalWrite(Light, HIGH);
      delay(200);
      Serial.println("light off");

    } 
    
    else if(!(strncmp(str,"all on",6)))
    {
      digitalWrite(Light, LOW);
      digitalWrite(Fan, LOW);
      digitalWrite(TV, LOW);
      delay(200);

    }
 
    else if(!(strncmp(str,"all off",7)))
    {
      digitalWrite(Light, HIGH);
      digitalWrite(Fan, HIGH);
      digitalWrite(TV, HIGH);
      delay(200);

    }     
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
