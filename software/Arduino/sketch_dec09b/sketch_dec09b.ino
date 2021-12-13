#include <ArduinoBLE.h>


int greeting = 0; 
BLEService greetingService("180C");  // User defined service

BLEStringCharacteristic greetingCharacteristic("2A56",  // standard 16-bit characteristic UUID
    BLERead| BLEWrite, 2); // remote clients will only be able to read this

void setup() {
  int greeting = 0; 
  Serial.begin(9600);    // initialize serial communication
  while (!Serial);

  pinMode(LED_BUILTIN, OUTPUT); // initialize the built-in LED pin

  if (!BLE.begin()) {   // initialize BLE
    Serial.println("starting BLE failed!");
    while (1);
  }

  BLE.setLocalName("Arduino1");  // Set name for connection
  BLE.setAdvertisedService(greetingService); // Advertise service
  greetingService.addCharacteristic(greetingCharacteristic); // Add characteristic to service
  BLE.addService(greetingService); // Add service
  greetingCharacteristic.writeValue(-1); // Set greeting string

  BLE.advertise();  // Start advertising
  Serial.print("Peripheral device MAC: ");
  Serial.println(BLE.address());
  Serial.println("Waiting for connections...");
}

void loop() {
  BLEDevice central = BLE.central();  // Wait for a BLE central to connect
  Serial.println("- Discovering central device...");
  delay(500);
  // if a central is connected to the peripheral:
  if (central) {
    Serial.print("Connected to central MAC: ");
    // print the central's BT address:
    Serial.println(central.address());
    // turn on the LED to indicate the connection:
    digitalWrite(LED_BUILTIN, HIGH);

    while (central.connected()){
      if (greetingCharacteristic.written()) {
        greeting = greetingCharacteristic.value();
        Serial.print(greeting);
      }
    }
    Serial.print("Disconnected from central MAC: ");
    Serial.println(central.address());
       // keep looping while connected
  }
    // when the central disconnects, turn off the LED:
    digitalWrite(LED_BUILTIN, LOW);
    //Serial.print("Disconnected from central MAC: ");
    
}
