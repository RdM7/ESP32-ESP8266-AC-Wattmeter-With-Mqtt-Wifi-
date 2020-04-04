// WRITE EEPROM SAFE
void writee(long val){
  //Rotate EEPROM Write Address

  //Load Address from Address = 0
       long addr = readeeprom(0);  
        
        if (addr < 4){
          addr = 4; 
        }else if (addr>=MAXEEPSIZE-4){
          addr=4;
        }else{
        //Increase Number  
        addr=addr+4;  
        }
        
      eepaddress=addr;
      //Write eeprom on next address
      writeeeprom(eepaddress, val);
  }



// READ EEPROM SAFE
  long reade(){
    //Load Address from Address = 0
    long addr = readeeprom(0);  
        if (addr < 4){
          addr = 4; 
        }else if (addr>=(MAXEEPSIZE-4)){
          addr=4;
        }
        
 long dat = readeeprom(eepaddress);
  if (dat < 0)dat = 0;
  return dat;      
  }






//Read EEPROM LONG
long readeeprom(long address) {
  long four = EEPROM.read(address);
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);
 
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

  
//Write EEPROM LONG
void writeeeprom(int address, long value) {
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);
 
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
  
   if (EEPROM.commit()) {
      //Serial.println("EEPROM successfully committed");
    } else {
      //Serial.println("ERROR! EEPROM commit failed");
    }
  
}
