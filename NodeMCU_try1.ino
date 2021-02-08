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

WidgetTerminal terminal(V4);

void setup()
{
  // Debug console
  Serial.begin(9600);

  Serial.print("PT100");

  Blynk.begin(auth, ssid, pass);

  Wire.begin(D1, D2);

  Wire.beginTransmission(8); /* begin with device address 8 */

  Wire.write("NodeMCU starts");
  
  Wire.endTransmission();

  terminal.clear();
}

BLYNK_WRITE(V1)
{
  int x = param[0].asInt();
  int y = param[1].asInt();

  // Do something with x and y
  Serial.print("X = ");
  Serial.print(x);
  Serial.print("; Y = ");
  Serial.println(y);

  Wire.beginTransmission(8); /* begin with device address 8 */

  SendJoystickVal_Vehicle(x,y);
  
  Wire.endTransmission();  
}

BLYNK_WRITE(V4)
{
  char values[3];
  
  Serial.print("Terminal input2:");
  Serial.print(param.asStr());
  Serial.println();
  
  sprintf(values,param.asStr());

  Wire.beginTransmission(8);
  Wire.write(values, 3);
  Wire.endTransmission();  
}

BLYNK_WRITE(V2)
{
  int valV2 = param.asInt();

  Wire.beginTransmission(8); /* begin with device address 8 */

  SendInt(2,valV2);

  Serial.print("V2=");
  Serial.println(valV2);
  
  Wire.endTransmission();  
}

BLYNK_WRITE(V3)
{
  int valV3 = param.asInt();

  Wire.beginTransmission(8); /* begin with device address 8 */

  SendInt(3,valV3);

  Serial.print("V3=");
  Serial.println(valV3);
  
  Wire.endTransmission();  
}

void SendInt(int ID, int value)
{
    char values[3];
    sprintf(values,"V%1d%1d",ID,value);

    Wire.write(values, 3);
}

void SendJoystickVal_Vehicle(int x, int y)
{
    char values[4];
    sprintf(values,"J1%01d%01d",x,y);

    Wire.write(values, 4);
}

void loop()
{
  String rcmd = "";
  
  Blynk.run();

  Wire.requestFrom(8, 26);
  while (0 <Wire.available())
  {
    //char c = Wire.read();      /* receive byte as a character */
    //Serial.print(c);           /* print the character */
    rcmd += (char)Wire.read();
  }

  if((rcmd[0]=='A')&&(rcmd[1]=='R'))
  {
    Serial.print("Recd Cmd:");
    Serial.println(rcmd);

    terminal.print("NodeMCU:") ;
    terminal.println(rcmd);
    terminal.flush();    
  }
  
  delay(500);
}
