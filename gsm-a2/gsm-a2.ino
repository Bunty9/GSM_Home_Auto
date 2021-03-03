#include <SoftwareSerial.h>
//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2




int temp=0,i=0;

#define Fan 6
#define Light 4
#define TV 5

char str[25];
String msg;
char ph[] = "+919420490305";


void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);


  pinMode(Fan, OUTPUT);
  pinMode(Light, OUTPUT);
  pinMode(TV, OUTPUT);
  digitalWrite(TV, HIGH);
  digitalWrite(Light, HIGH);
  digitalWrite(Fan, HIGH);

  Serial.println("Initializing..."); 
  delay(1000);
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  delay(500);
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  delay(500);
  mySerial.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
  updateSerial();
  delay(500);

  delay(500);
  mySerial.print("AT+CMGS=");
  mySerial.print("\"");
  mySerial.print(ph);
  mySerial.println("\"");
  delay(1000);
  mySerial.println("System is ready to receive SMS commands.");
  delay(100);
  mySerial.println((char)26);

  
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

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
//  while(mySerial.available()) 
//  { 
//    String msg = mySerial.readString();
//    Serial.println(msg);  //Forward what Software Serial received to Serial Port      
//  }
}


void serialEvent() 
 {
  while(mySerial.available()) 
  {
    if(mySerial.find("#A."))
    {
      Serial.println("cmd");
      while (mySerial.available()) 
      {
      char inChar=mySerial.read();
      Serial.print(inChar);
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

///////////////////////////////////////////////////////

void check()
{
   if(!(strncmp(str,"tv on",5)))
    {
      digitalWrite(TV, LOW);
      delay(200);
      Serial.println("TV ON");
      
      mySerial.print("AT+CMGS=");
      mySerial.print("\"");
      mySerial.print(ph);
      mySerial.println("\"");
      delay(200);
      mySerial.println("TV turned ON.");
      delay(200);
      mySerial.println((char)26);
      
    }  
   
   else if(!(strncmp(str,"tv off",6)))
    {
      digitalWrite(TV, HIGH);
      Serial.println("TV OFF");
      delay(200);
      mySerial.print("AT+CMGS=");
      mySerial.print("\"");
      mySerial.print(ph);
      mySerial.println("\"");
      delay(200);
      mySerial.println("TV turned OFF.");
      delay(200);
      mySerial.println((char)26);
    }
  
    else if(!(strncmp(str,"fan on",6)))
    {
      digitalWrite(Fan, LOW);
      delay(200);
      Serial.println("fan on");
            
      mySerial.print("AT+CMGS=");
      mySerial.print("\"");
      mySerial.print(ph);
      mySerial.println("\"");
      delay(200);
      mySerial.println("FAN turned ON.");
      delay(200);
      mySerial.println((char)26);
    }
 
    else if(!(strncmp(str,"fan off",7)))
    {
      digitalWrite(Fan, HIGH);
      delay(200);
      Serial.println("fan off");

      mySerial.print("AT+CMGS=");
      mySerial.print("\"");
      mySerial.print(ph);
      mySerial.println("\"");
      delay(200);
      mySerial.println("FAN turned OFF.");
      delay(200);
      mySerial.println((char)26);

    }
 

    
    else if(!(strncmp(str,"all on",6)))
    {

      digitalWrite(Fan, LOW);
      digitalWrite(TV, LOW);
      delay(200);

      mySerial.print("AT+CMGS=");
      mySerial.print("\"");
      mySerial.print(ph);
      mySerial.println("\"");
      delay(200);
      mySerial.println("ALL DEVICES turned ON.");
      delay(200);
      mySerial.println((char)26);
    }
 
    else if(!(strncmp(str,"all off",7)))
    {

      digitalWrite(Fan, HIGH);
      digitalWrite(TV, HIGH);
      delay(200);

      mySerial.print("AT+CMGS=");
      mySerial.print("\"");
      mySerial.print(ph);
      mySerial.println("\"");
      delay(200);
      mySerial.println("ALL DEVICES turned OFF.");
      delay(200);
      mySerial.println((char)26);
    }     
}


/////////////////////////////////////////////////////////////////
