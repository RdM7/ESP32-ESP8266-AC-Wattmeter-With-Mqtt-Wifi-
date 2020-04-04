void ntpinit(){
  
  //NTP
  NTP.onNTPSyncEvent ([](NTPSyncEvent_t event) {
    ntpEvent = event;
    dosync = true;
  });

  NTP.begin ("pool.ntp.org", timeZone, false, minutesTimeZone);
  NTP.setInterval (5); //Do not change

  }


  
//NTP
bool ntp_sync_response (NTPSyncEvent_t ntpEvent) {
  if (ntpEvent) {
    if(DBG)Serial.println("Time Sync error: ");
    if (ntpEvent == noResponse)
      if(DBG)Serial.println("NTP server not reachable");
    else if (ntpEvent == invalidAddress)
      if(DBG)Serial.println("Invalid NTP server address");
  } else {
    if(DBG)Serial.println("Got NTP time");
  }
  //Return Success or Error
  return ((ntpEvent == 0) ? true : false);
}
