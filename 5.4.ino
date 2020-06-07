#include<dht.h>
#define dht_Apin A0 // Analog Pins for nodes
#define dht_Bpin A1 
#define dht_Cpin A2 
#define dht_Dpin A3 

//------------------------RTC
#include <Wire.h>
#include <DS3231.h>
DS3231 clock;
RTCDateTime dt;
//------------------------RTC

//------------------------SD
//2 header files for writing to SD card
#include <SD.h>
#include <SPI.h>
//Created a file object
File myFile;
//Declare variable to handle data 
int pinCS = 10;
int LED1 = 9; 
//------------------------SD
dht DHT;

//------------------------RELAY
int relayPin = 3;

void setup(){

//------------------------RELAY
  pinMode(relayPin, OUTPUT);
 
  Serial.begin(9600);
  delay(1000);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n");
  delay(1000);//Wait before accessing Sensor

  //------------------------SD
  //pin mode for SD card
  pinMode(pinCS, OUTPUT);
  pinMode(LED1, OUTPUT); 
  //------------------------SD
  
  //------------------------RTC
  Serial.println("Initialize RTC module\n");
  // Initialize DS3231
  clock.begin();
  //Send sketch compiling time to Arduino
  clock.setDateTime(__DATE__, __TIME__);    
  //------------------------RTC

  //SD Card initialization that tests whether or not there is an SD card. 
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.\n");
  }else
  {
    Serial.println("SD card initialization failed.\n");
    digitalWrite(LED1, HIGH);
    return;
  }

  //SD card creating data file
  myFile = SD.open("TEST.txt", FILE_WRITE);
 
}//end "setup()"
 
void loop(){

  //------------------------------------------RELAY
  digitalWrite(relayPin, HIGH);    // turn the relay on (HIGH is the voltage level)
  delay(20000);                   // wait for a second


    //Gets time for local scope
    dt = clock.getDateTime();

    //Declare variables to hold values for nodes
    double tempA=0;
    double tempB=0;
    double tempC=0;
    double tempD=0;
    double humA=0;
    double humB=0;
    double humC=0;
    double humD=0;
    
    //RTC To memory, puts the time stamp on the left.
    Serial.print("Time: ");
    Serial.print(dt.hour);  
    Serial.print(":");
    Serial.print(dt.minute);
    Serial.println("");

    //Prints and saves values for node A
    DHT.read11(dht_Apin);
    Serial.print("Node A:\n");
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    tempA=DHT.temperature;
    humA=DHT.humidity;
    delay(1000);

    //Prints and saves values for node B
    DHT.read11(dht_Bpin);
    Serial.print("Node B:\n");
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    tempB=DHT.temperature;
    humB=DHT.humidity;
    delay(1000);

    //Prints and saves values for node C
    DHT.read11(dht_Cpin);
    Serial.print("Node C:\n");
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    tempC=DHT.temperature;
    humC=DHT.humidity;
    delay(1000);

    //Prints and saves values for node D
    DHT.read11(dht_Dpin);
    Serial.print("Node D:\n");
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    tempD=DHT.temperature;
    humD=DHT.humidity;
    Serial.println("");
    delay(1000);

  //---------------------------------------SD
  myFile = SD.open("test.txt", FILE_WRITE);
  
  if(myFile)
  {
    //Next line of code AFTER the file is opened
    myFile.println("");

    //RTC To memory, puts the time stamp on the left.
    myFile.print(dt.hour);  myFile.print(":");
    myFile.print(dt.minute);
    myFile.print(" ; ");

    //writes the tmp and hmd data to the file. 
    myFile.print(tempA);
    myFile.print(" ; ");
    myFile.print(humA);
     myFile.print(" ; ");

    //writes the tmp and hmd data to the file. 
    myFile.print(tempB);
    myFile.print(" ; ");
    myFile.print(humB);
     myFile.print(" ; ");

    //writes the tmp and hmd data to the file. 
    myFile.print(tempC);
    myFile.print(" ; ");
    myFile.print(humC);
     myFile.print(" ; ");

    //writes the tmp and hmd data to the file. 
    myFile.print(tempD);
    myFile.print(" ; ");
    myFile.print(humD);

    //new line
    //myFile.println("");

    //close and saves the file
    myFile.close();
  }
  else
  {
    Serial.println("Error opening file");
    Serial.println("");
    digitalWrite(LED1, HIGH);
  }
//---------------------------------------SD


  digitalWrite(relayPin, LOW);    // turn the relay off by making the voltage LOW
  delay(20000);                   // wait for a second
  //------------------------------------------RELAY


    
}// end loop() 
