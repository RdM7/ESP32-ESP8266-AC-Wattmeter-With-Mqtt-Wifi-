# ESP32 / ESP8266 Based AC Wattmeter With Mqtt (Wifi)
ESP32/ESP8266 Based WattMeter ( Blue clamp SCT013-050 Current Coil or any Current Coil )  

## Requirements:
- ESP32 / ESP8266 Module
- 500R Resistor
- 22PF Capacitor (Optional)

- Any Current Coil

## Connections:
- Solder 500R as Load Resistor between two terminals of Current Coil, 
- Connect to ESP Analog Pin and To Ground.
- With 22 PF Capacitor on Analog pin to Ground.

## Preparing:
-The firmware will compile on both ESP32 & ESP8266 Modules, You can choose Analog input pin like:

-In includes.h edit inputPin 
```
#define inputPin  A0
```

## Calibrate Watts:
- In wattmeter.ino tweak the average multiplier (8.25) to match your actual load (at current time)
- if you are using same coil like me, you don't need to calibrate.
```
average = (average * 8.25); // Calibrated to set Var:average to Actual Watts
```

- When your load is same as current actual load, then you can calculate costs.


## Coil Used by Me:

![Current Coil](https://i.ibb.co/SrZK2KD/coil.jpg)

## Output

### Used with Raspberry Pi (Grafana)

![Grafaba](https://i.ibb.co/bJGrxrj/coil.jpg)

