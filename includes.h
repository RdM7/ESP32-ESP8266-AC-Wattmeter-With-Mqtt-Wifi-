#include <Arduino.h>

#if defined(ESP32)
// ESP32 
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#else
// ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#endif
//OTA
#include <ArduinoOTA.h>
//MQTT
#include <PubSubClient.h>
//NTP
#include <TimeLib.h>
#include <NtpClientLib.h>
//EEPROM
#include <EEPROM.h>



//NTP
NTPSyncEvent_t ntpEvent; 

//NTP TIMEZONE
int8_t timeZone = 5; //Hours (+ or -)
int8_t minutesTimeZone = 30; //(Minutes)


//Don't Modift (System Variables)
bool dosync = false; // Will turn True if a time even has been triggered
#define NTP_SYNC_INTERVAL 600 // 10 Mins


//WIFI 
char* ssid = "XXXXXXXX";
char* password = "XXXXXXXX";


//MQTT
const char* MQTTSERVER = "192.168.100.100";
const int   MQTTPORT     =        1883;
WiFiClient espClient;
PubSubClient mqtt(espClient);

#define TOPIC "feeds/wattmeter/"
#define TOPIC_WATTS TOPIC "watts"
#define TOPIC_LASTDAYEXPENSE TOPIC "lastdaybill"
#define TOPIC_TODAYBILL TOPIC "todaybill"

#define TOPIC_IN TOPIC "debug"
//Receive Mqtt Message : "feeds/wattmeter/debug" with payload "1" to turn on debug serial.

//OTA
#define OTA_NAME "Wattmeter"

//Debug Serial
bool DBG = false;

//Led Blink with Every Mqtt Push
#define LED 2
#define inputPin  A0

//Enable Wattmeter Function
bool wattmeter_en = true;

//EEPROM Address 0-3 will be used for address rotation.
//Eeprom Address (From 4-MAX) (Will Rotate on Write)
int eepaddress = 4;
#if defined(SPI_FLASH_SEC_SIZE)
#define MAXEEPSIZE  SPI_FLASH_SEC_SIZE 
#else
#define MAXEEPSIZE  512
#endif

// Smoothing
#define  pulsetime  40 // good value: 100
#define  numReadings  200  // good value: 50

int readings[numReadings];     
int readIndex = 0;     
long total = 0;         
float average = 0.0;       
int watt = 0;


long timer1 = 0;
long timer2 = 0;
long wifitimer = 0;
long timereeprom =0;
//Cost Calculation
#define costperkw 8

long timercostcount=0;
float costtoday=0.000;
int lastdate=0;
int todaydate=0;
