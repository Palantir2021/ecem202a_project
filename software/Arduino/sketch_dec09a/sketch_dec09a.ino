/*
  BLE_Peripheral.ino

  This program uses the ArduinoBLE library to set-up an Arduino Nano 33 BLE 
  as a peripheral device and specifies a service and a characteristic. Depending 
  of the value of the specified characteristic, an on-board LED gets on. 

  The circuit:
  - Arduino Nano 33 BLE. 

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>
      
enum {
  detection_NONE  = -1,
  detection_UP    = 0,
  detection_DOWN  = 1,
  detection_LEFT  = 2,
  detection_RIGHT = 3
};

const char* deviceServiceUuid = "180C";
const char* deviceServiceCharacteristicUuid = "2A56";
String address = BLE.address();

int detection = -1;

BLEService detectionService(deviceServiceUuid); 
BLEByteCharacteristic detectionCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);


void setup() {
  Serial.begin(9600);
  while (!Serial);  
  
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
  digitalWrite(LED_BUILTIN, LOW);

  
  if (!BLE.begin()) {
    //Serial.println("- Starting BLE module failed!");
    while (1);
  }

  BLE.setLocalName("Arduino1");
  BLE.setAdvertisedService(detectionService);
  detectionService.addCharacteristic(detectionCharacteristic);
  BLE.addService(detectionService);
  detectionCharacteristic.writeValue(-1);
  BLE.advertise();
  
  Serial.print("Local address is: ");
  Serial.println(address);
  //Serial.println("Nano 33 BLE (Peripheral Device)");
  //Serial.println(" ");
}

void loop() {
  BLEDevice central = BLE.central();
  //Serial.println("- Discovering central device...");
  delay(500);

  if (central) {
    //Serial.println("* Connected to central device!");
    //Serial.print("* Device MAC address: ");
    //Serial.println(central.address());
    //Serial.println(" ");

    while (central.connected()) {
      if (detectionCharacteristic.written()) {
         detection = detectionCharacteristic.value();
         writedetection(detection);
       }
    }
    
    //Serial.println("* Disconnected to central device!");
  }
}

void writedetection(int detection) {
  //Serial.println("- Characteristic <detection_type> has changed!");
  
   switch (detection) {
      case detection_UP:
        //Serial.println("* Actual value: UP (red LED on)");
        //Serial.println(" ");
        digitalWrite(LEDR, LOW);
        digitalWrite(LEDG, HIGH);
        digitalWrite(LEDB, HIGH);
        digitalWrite(LED_BUILTIN, LOW);
        break;
      case detection_DOWN:
        //Serial.println("* Actual value: DOWN (green LED on)");
        //Serial.println(" ");
        digitalWrite(LEDR, HIGH);
        digitalWrite(LEDG, LOW);
        digitalWrite(LEDB, HIGH);
        digitalWrite(LED_BUILTIN, LOW);
        break;
      case detection_LEFT:
        //Serial.println("* Actual value: LEFT (blue LED on)");
        //Serial.println(" ");
        digitalWrite(LEDR, HIGH);
        digitalWrite(LEDG, HIGH);
        digitalWrite(LEDB, LOW);
        digitalWrite(LED_BUILTIN, LOW);
        break;
      case detection_RIGHT:
        //Serial.println("* Actual value: RIGHT (built-in LED on)");
        //Serial.println(" ");
        digitalWrite(LEDR, HIGH);
        digitalWrite(LEDG, HIGH);
        digitalWrite(LEDB, HIGH);
        digitalWrite(LED_BUILTIN, HIGH);
        break;
      default:
        digitalWrite(LEDR, HIGH);
        digitalWrite(LEDG, HIGH);
        digitalWrite(LEDB, HIGH);
        digitalWrite(LED_BUILTIN, LOW);
        break;
    }      
}
