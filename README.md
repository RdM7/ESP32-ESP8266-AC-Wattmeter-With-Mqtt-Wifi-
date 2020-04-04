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


## Coil Used by Me:


![Current Coil](https://i.ibb.co/dKgHTqc/50-A-Non-invasive-AC-Current-Sensor-15-A-750x750-66373-1561065443.jpg)


## Output

### Used with Raspberry Pi (Grafana)

![Grafaba](https://i.ibb.co/pzq2Nw2/wattmeter.jpg)

