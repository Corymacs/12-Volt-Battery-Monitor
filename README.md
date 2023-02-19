# 12-Volt-Battery-Monitor

I created this project to keep an eye on the 12 volt battery of my electric car. It connects to two different WIFI networks and uses the app Blynk to keep an eye on different information about the battery.

Use of this code requires an APP created on https://blynk.io/  
Blynk is free with minor use which this program will fall under. There is some to learn with Blynk so I will let you putter around with it and learn it yourself for now until I can get enough time to make a tutorial. But trust me if I can figure it out so can you.
The Virtual pins you will be interested in for the template you will create with Blynk are as follows...  
V0 = Voltage  
V1 = Current  
V2 = Temperature  
V3 = Humidity  
  
As for the parts involved all of them I sourced from amazon for cheap. Atleast in my opinion it is a pretty inexpensive project and it gets you far more information then a store bought monitor. Parts list is...  
"Arduino with WIFI built in for the brains of the project"  
x1 Arduino ESP8266 NodeMCU             https://a.co/d/1botgaY   //Amazon Canada  
  
"Note you will not be running thr current through this board so it is important to remove the onboard 100 ohm resistor"              
x1 INA226 Current shunt board          https://a.co/d/3lF1AP3   //Amazon Canada  
  
"This charges the batteries the project uses when the car is running"  
x1 Lithium Battery Charger             https://a.co/d/2Bajnij   //Amazon Canada  
  
"This is where the project gets its temp and humidity data from"  
x1 DHT22 temp sensor                   https://a.co/d/4hKodbF   //Amazon Canada  
  
"This is used to convert the 12 volts to 5 volts as this is what the arduino and add-ons require" ******Important must be tuned using the onboard potentiometer before connection the output as they come out of the box set for max output and will destroy the arduino******  
x1 Buck Convertor                      https://a.co/d/huEWUPX   //Amazon Canada  
  
"Used to cut power to the onboard battery charger when the vehicle is not charging."  
x1 3.3 volt relay                      https://a.co/d/6uYpilo   //Amazon Canada  
  
"I have included the gerber file for my custom PCB which makes this project simple. Use the link plus the archive in the GIT to order. It is quite inexpensive and make the project easy."  
x1 Custom PCB                          https://docs.easyeda.com/en/PCB/Order-PCB  
  
"I included a link but I bought these in a kit of 250 of various transistors since they are so cheap"  
x1 NPN Transistor                      https://a.co/d/2Ppdc7c   //Amazon Canada 
  
"I bought all resistors in a kit of various resistors."  
x2 10K OHM Resistors                   https://a.co/d/9ZvcVaE   //Amazon Canada  
x1 1K OHM Resistor  
x1 2.2K OHM Resistor  
  
"This is used to prevent a voltage spike from the relay shut off"  
1x Diode                               https://a.co/d/i0Az8r3   //Amazon Canada  
  
"These are used to connect the various componants to the board. Such as the Arduino, buck convertor and the INA 226 board'  
1x Pin Headers                         https://a.co/d/htn4DyZ   //Amazon Canada  
  
If you used my custom PCB the PCB is marked with all the component locations and should be fairly straight forward to build. Again I cant stress this enough the buck convertor must be connected to 12 volts then use a multimeter to calibrate the output to 5 volts using the onboard potentiometer. If the PCB is built without this being done 12 volts will be supplied to all the componants downstream and they are only meant for 5 volts.  
There are 6 connections on the PCB. Two are for the onboard battery which are polarity sensative, the square connection is nagative. Two are for the power connection from the vehicle which is polarity sensative, the square connection is negative. Two are for the shunt, these are not polarity sensative, just connect one to the negative of the vehicle battery and connect the other to where the battery ground cable connects to the battery.  
  
Thanks for looking at my project and if you do decide to build the project dont be afraid to contact me with questions or updates. Also I would love to see pictures of your completed projects.  

Cory  
Cory.MacSween@Gmail.com  