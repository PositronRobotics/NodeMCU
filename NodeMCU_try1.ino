/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  You can receive x and y coords for joystick movement within App.

  App project setup:
    Two Axis Joystick on V1 in MERGE output mode.
    MERGE mode means device will receive both x and y within 1 message
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <Wire.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "uKrfRqfljEc1KtnNXqikouIxrVut-97-";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "PreeWiFi_2GHz";
char pass[] = "pree123*";

BLYNK_WRITE(V1) {
  int x = param[0].asInt();
  int y = param[1].asInt();

  // Do something with x and y
  Serial.print("X = ");
  Serial.print(x);
  Serial.print("; Y = ");
  Serial.println(y);

  Wire.beginTransmission(8); /* begin with device address 8 */

  Wire.write("X = ");
  Wire.write(x);
  Wire.write("; Y = ");
  Wire.write(y);
  
  Wire.endTransmission();  
}

BLYNK_WRITE(V2) {
 
}

BLYNK_WRITE(V3)
{
  int valV3 = param.asInt();
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  Wire.begin(54);
  Wire.onRequest(requestEvent); 
}

void loop()
{
  Blynk.run();   
}

void requestEvent()
{
  int16_t bigNum = 1234;
  byte myArray[2];
   
  myArray[0] = (bigNum >> 8) & 0xFF;
  myArray[1] = bigNum & 0xFF;
  Wire.write(myArray, 2);
}
