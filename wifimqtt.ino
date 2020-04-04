
/*
 * 
 * MQTT Init
 */
  
void mqttinit(){
  //MQTT
  mqtt.setServer(MQTTSERVER, MQTTPORT);
  mqtt.setCallback(callback);
  randomSeed(micros());  
  }


/*
 * Wifi & Mqtt Check Loop
 */


void mqttwifiloop(){
    if (!mqtt.connected()) {
    mqttconnect();
  }

  mqtt.loop();


   // --------------------------------------------------------------------
    //WIFI CHECK 10 Minute TIMER
    if (((millis() - wifitimer) / 1000) > 600) {
      if (WiFi.status() != WL_CONNECTED) {
        connectwifi();
      }
      wifitimer = millis();
    }
    
  }



/*
 * 
 * MQTT Connect
 */
 
//MQTT
void mqttconnect() {
  int tries = 0;
  if (mqtt.connected())return;
  while (!mqtt.connected()) {
    ArduinoOTA.handle();
    String mqttId = "ESP8266mqtt-";
    mqttId += String(random(0xffff), HEX);
    if (mqtt.connect(mqttId.c_str())) {
      if(DBG)Serial.println("Mqtt Server Connected");

      // Subscribe Here
      mqtt.subscribe(TOPIC_IN);

    } else {
      tries++;
      if (tries > 10)return;
    }

  }
}


/*
 * 
 * MQTT Callback
 */

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';

  int x = atoi((char *)payload);
  //Debug ON (Payload:1)
  DBG = ((x == 1) ? true : false);

  
  char msg[40];
  snprintf(msg, 40, "Mqtt Message IN :%2d", x );
  if(DBG)Serial.println(msg);

}

/*
 * 
 * MQTT Publish Int Long Float
 */
 
//MQTT

void publish(char* topic,char* data){
   char msg[50];
   snprintf(msg, 50, "%s", data );
   mqtt.publish(topic, msg);
   delay(100);
  }


void publish(char* topic,int data){
   char msg[10];
   snprintf(msg, 10, "%1d", data );
   mqtt.publish(topic, msg);
   delay(100);
  }

void publish(char* topic,long data){
   char msg[20];
   snprintf(msg, 20, "%1d", data );
   mqtt.publish(topic, msg);
   delay(100);
  }

void publish(char* topic,float data){
   char msg[10];
   snprintf(msg, 10, "%2f", data );
   mqtt.publish(topic, msg);
   delay(100);
  }

//###########################################################

/*
 * 
 * Wifi Functions
 */

//WIFI
void connectwifi() {
  if (DBG) Serial.println("Connecting to Wifi...");
  if (!connect_wifi(10)) {
    if (DBG) Serial.println("Cannot Connect.");
  } else {
    if (DBG) Serial.println("Connected");
    if (DBG) Serial.print("IP address: ");
    if (DBG) Serial.println(WiFi.localIP());
    delay(100);
  }
}




bool connect_wifi(int maxattempts) {
  bool conn1 = false;
  //TRY
  int trys = 0;
  while (!conn1) {
    if (trys > 0) {
      if (DBG) Serial.print("Try: ");
      if (DBG) Serial.print(trys);
    }
    conn1 = connect__wifi(ssid, password);
    trys++;

    if (trys > maxattempts)break;
  }

  return (conn1);
}



bool connect__wifi(char* ssid, char* password) {

  unsigned long timeout = millis();
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
 
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    if (((millis() - timeout) / 1000) >= 2) {
      break;
    }
  }
  if (WiFi.status() == WL_CONNECTED) return (true); else return (false);
}
