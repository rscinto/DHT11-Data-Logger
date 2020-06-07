# DHT11-Data-Logger
This machine uses an Arduino, SD card, DS3231, 4 x DHT 11, Red LED, 220 ohm resistor, breadboard and wire. 


The revision 5.4 of this data logger machine works by initializing the SD card after boot. If the SD card is not initialized or data is not being logged, the red LED will illuminate. If the initialization passes, the 4 sensors will log their data. One of the sensors can be used to track the board temerature if you choose. Some SD cards fail at temperatures greater than 38 celcius and the data will be lost and the card destroyed. 

The data from the card can be used like any CSV(comma separated value) file and uploaded to Excel or other graphing utilities. 

Go get that data. 


![](pictures/breadboard.jpg)
![](pictures/GraphingData.png)