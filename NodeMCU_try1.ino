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
  int m1 = param.asInt();

  Wire.beginTransmission(8); /* begin with device address 8 */

  if(m1==1)
  {
    Wire.write("m1=1");
  }
  else
  {
    Wire.write("m1=0");
  }
  
  Wire.endTransmission();  
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  Wire.begin(D1, D2);

  Wire.beginTransmission(8); /* begin with device address 8 */

  Wire.write("NodeMCU starts");
  
  Wire.endTransmission();    
}

void loop()
{
  Blynk.run();   
}
