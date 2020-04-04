
/*
 * 
 * Check Watts from ADC (Multiple Timers)
 */

void checkwatts() {
  // if Wattmeter enabled
  if (wattmeter_en) {

    //Read Max Value in 1 PulseTime
    int i = analogRead(inputPin);
    if (i > watt) watt = i;

// OTA Fix: Multiple Calls:
    ArduinoOTA.handle();



// --------------------------------------------------------------------
    //Capture Max Value & Smoothing
    if (((millis() - timer2)) >= pulsetime) {
      timer2 = millis();
      total = total - readings[readIndex];
      readings[readIndex] = watt;
      watt = 0;
      total = total + readings[readIndex];
      readIndex = readIndex + 1;
      if (readIndex >= numReadings) {
        readIndex = 0;
      }
    }



    // --------------------------------------------------------------------
    //Calculate Watts and Send WATTS Message every 3 secs
    if (((millis() - timer1) / 1000 ) >= 3) {
      timer1 = millis();
      average = (total / numReadings);
      average = (average * 8.25); // Calibrated to set Var:average to Actual Watts

      // Cost per 3 seconds
      float costper3sec = ((((average / 1000) * costperkw) / 3600) * 3); 
      costper3sec = (costper3sec / 100) * 66.6; 

      //Calculate total cost for today
      if (costper3sec > 0) costtoday = costtoday + costper3sec;

      publish(TOPIC_WATTS, average);
      average = 0;     
      
    }


// OTA Fix: Multiple Calls:
    ArduinoOTA.handle();


   



    // --------------------------------------------------------------------
    //Write eeprom every hour
    if (((millis() - timereeprom) / 1000) >= 3600) {
      timereeprom = millis();
      long w = costtoday;
      writeeeprom(eepaddress, w);
    }




    // --------------------------------------------------------------------
    //every minute timer
    if (((millis() - timercostcount) / 1000) >= 60) {
      timercostcount = millis();
      todaydate = day();
      publish(TOPIC_TODAYBILL, costtoday);

      //Detect Next Date
      if (lastdate != todaydate) {
        lastdate = todaydate;
        //Send Mqtt of last day expense
        int estimatemonthlybill = (costtoday * 30);
        publish(TOPIC_LASTDAYEXPENSE, costtoday);
        publish("feeds/wattmeter/lastdayesmonthbill", estimatemonthlybill);

        //Write Zero for new day costtoday
        costtoday = 0;
        writee(costtoday);
      }

    }
    // --------------------------------------------------------------------


  }
}
