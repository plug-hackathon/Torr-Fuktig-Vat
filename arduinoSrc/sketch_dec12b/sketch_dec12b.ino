#include <SoftwareSerial.h>   //Library for serial communication 

SoftwareSerial esp(10,11);    //Set receiver and transmitter for esp8266

/*Change the value to modify when the watering should start. Dry air
 is approximately 650, very dry soil is approximately 610. Very moist
 soil yields approximately 200.*/
int maxValueBefWatering = 610; 

/* Change of the following variable for the amount of seconds in between
 sampling for program logic (interval inbetween checking the moist 
 sensor).*/
int milliSecondsDelay = 10000;

/* This integer sets how long the pump will be on for when the waterMe
 method is called.*/
int milliSecondsPump = 500;

//Setup
void setup() 
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);   
  pinMode(12, OUTPUT);    //Output for the water pump
  
  /*-----------------Setting up esp8266-----------------*/
  esp.begin(9600);        //Set to same rate
  delay(5000);            //Letting communications read info
  esp.println("AT+RST");
  delay(5000);
  esp.println("AT+CWMODE=1");
  delay(5000);
  String connectString = "AT+CWJAP=";
  connectString += SSID;
  connectString += "\",\"";
  connectString += PASS;
  connectString += "\"";
  esp.println(connectString);
  /*-----------------End setting up esp8266-----------------*/

}

void updateStats(int currentMoistValue)
{
  esp.println("AT+CIPSTART=\"UDP\",\"188.226.137.177\",16000");   //Prepare chip to send UDP package to server
  delay(5000);
  esp.println("AT+CIPSEND=3");       //Set length of message to be sent
  String herro = "Hej";    
  delay(5000);         
  esp.print(herro);                  //Send message
  delay(5000);
  esp.println("");
  Serial.print("Value of sensor in update function = ");
  Serial.println(currentMoistValue);
}

void waterThePlant()
{
   Serial.print("In watering method because value is over my max value: ");
   Serial.println(maxValueBefWatering);
   digitalWrite(12, HIGH);    //Start pumping
   delay(milliSecondsPump);
   digitalWrite(12,LOW);      //Stop pumping
}

void loop()
{
  int sensorValue = analogRead(A0);
  //if (sensorValue >= maxValueBefWatering){waterThePlant();}
  //Serial.print("Actual value of sensor = ");
  //Serial.println(sensorValue);
  updateStats(sensorValue);
  delay(milliSecondsDelay);
}
