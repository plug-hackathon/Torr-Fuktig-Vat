#include <SoftwareSerial.h>   //Library for serial communication 

// Headers for the temperaturelogging 
#include <OneWire.h>
#include <DallasTemperature.h>

//Headers for communication
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#define ONE_WIRE_BUS 2

//Server settings
byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02};
char server[] = "188.226.137.177";
// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

/*Change the value to modify when the watering should start. Dry air
 is approximately 650, very dry soil is approximately 610. Very moist
 soil yields approximately 200.*/
int maxValueBefWatering = 450; 

/* Change of the following variable for the amount of seconds in between
 sampling for program logic (interval inbetween checking the moist 
 sensor).*/
int milliSecondsDelay = 20000;
 /* This integer sets how long the pump will be on for when the waterMe
 method is called for the first time in a row. It will increase with
 each lap.*/
int milliSecondsPump = 1000;

/* This counter keeps track on how many times in a row the watering
 method has been called*/
int counter = 0;

/* Following variable declares output port of pump relay*/
int pumpPort = 9;

// Setup a oneWire instance on pin 2
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

//Setup
void setup() 
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);   
  pinMode(pumpPort, OUTPUT);    //Output for the water pump
  sensors.begin();        //One wire sensors 
  int started = Ethernet.begin(mac);
  if (started == 0) {Serial.println("Connection error");}
  // print your local IP address:
  printIPAddress();
}

void updateStats(int currentMoistValue, double currentTemp)
{
  Serial.print("\nUpdate function values from sensors: \nMoist = " + String(currentMoistValue) + "\nTemperature = " + String(currentTemp) + "\n");
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");
  if (client.connect(server, 8000)) 
  {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("POST /post/ HTTP/1.1");
    client.println("Host: 188.226.137.177");
    client.println("User-Agent: " + String(currentMoistValue) + "," + String(currentTemp)); // Here we enter the data
    client.println("");
    delay(1000);
    client.stop();
    Serial.println("Client stop");
  } 
  else 
  {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void waterThePlant()
{
   Serial.println("In watering method because value is over my max value: " + String(maxValueBefWatering));
   digitalWrite(pumpPort, HIGH);    //Start pumping
   /*Because it is hard to predict how long the pump will need to be on for it increases 
    with the value of extraMilliseconds each time it pumps in row with the amount of 
    milliseconds specified below. Starting out at 0 * some constant and increasing with
    1 * same constant and so on. After it passes a lap without watering it will reset*/ 
   int extraMilliseconds = counter * 500;     
   Serial.println("It has been " + String(counter) + " laps in a row of watering, it will now pump for " + String(extraMilliseconds) + " extra millis.");
   delay(milliSecondsPump + extraMilliseconds);
   digitalWrite(pumpPort,LOW);      //Stop pumping
}

void printIPAddress()
{
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) 
  {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
  Serial.println();
}

void loop()
{
  int moistSensorValue = analogRead(A0);
  if (moistSensorValue >= maxValueBefWatering)
  {
    waterThePlant();
    counter++;    //For extra pump time
  }
  else { counter = 0;}    //Resetting for right starting value for watering time next watering session
  sensors.requestTemperatures();
  double temp = sensors.getTempCByIndex(0);
  updateStats(moistSensorValue, temp);
  Serial.println("Actual value of moist sensor = " + String(moistSensorValue) + "\nActual temperature measured = " + String(temp) + "\n");
  delay(milliSecondsDelay);
}

