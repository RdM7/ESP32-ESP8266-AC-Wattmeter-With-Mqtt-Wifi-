/*
 * ESP32/ESP8266 Based WattMeter ( Blue clamp SCT013-050 Current Coil or any Current Coil )
 * The Readings to be sent to MQTT Server (With Wifi Connection)
 *  
 * Can Calibrate variables (As Required)
 *  
 * Connection: 500R as Load Resistor between two terminals of Current Coil, Connect to ESP Analog Pin and To Ground.
 * With 22 PF Capacitor on Analog pin to Ground.
 * 
 * Created by Ajay Kumar 
 * Email: ajaybnl@gmail.com
 * 
 * v0.1
 * 
 * Dev Url : https://github.com/ajaybnl/ESP32-ESP8266-AC-Wattmeter-With-Mqtt-Wifi-
 * 
 * 
 * 
 */


 //All Declarations are int this file:

#include "includes.h"


void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  //Serial Begin
  if (DBG) Serial.begin(115200);

  //Connect to Wifi
  connectwifi();

  mqttinit();

  ntpinit();

  // Smoothing Data Fill
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }


  //OTA
  ArduinoOTA.setHostname(OTA_NAME);
  ArduinoOTA.begin();

  //WIFI
  wifitimer = millis();

  //EEPROM
  EEPROM.begin(MAXEEPSIZE);

  lastdate = day();

  //Load last cost
  long dat = reade();
  costtoday = (float)dat;

}





void loop() {
  //OTA
  ArduinoOTA.handle();

  mqttwifiloop();

  checkwatts();


  // OTA Fix: Multiple Calls:
  ArduinoOTA.handle();
}



void blink() {
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
}
