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
  detection_MIDDLE  = 2,
  detection_RIGHT = 3
};

const char* deviceServiceUuid = "180C";
const char* RASPCharacteristicUuid = "2A56";
const char* phoneServiceUuid = "58bcf5c0-300a-4d6a-9bd5-5346909ec528";
const char* NotifyCharacteristicUuid = "1b0380e6-400b-4858-bf41-bc8fc5b6e40b";
//String address = BLE.address();
boolean checkDistance = false;
boolean recv = false;

const int numUltrasonic=20;
char distanceUltrasonic[numUltrasonic]; //String that stores group of 4 ultrasound-detected distances from sensor Arduino
char ultra_start='<';
char ultra_end='>';
char tempChars[numUltrasonic];
int left_waist=1000;
int right_waist=1000;
int left_foot=1000;
int right_foot=1000;

int detection = -1;
int notify = -1;

BLEService detectionService(deviceServiceUuid); 
BLEByteCharacteristic detectionCharacteristic(RASPCharacteristicUuid, BLERead | BLEWrite);


void setup() {
  //Serial.begin(9600);
  Serial1.begin(9600);
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
    ////Serial.println("- Starting BLE module failed!");
    while (1);
  }

  BLE.setLocalName("Arduino1");
  BLE.setAdvertisedService(detectionService);
  detectionService.addCharacteristic(detectionCharacteristic);
  //detectionService.addCharacteristic(NotifyCharacteristic);
  BLE.addService(detectionService);
  detectionCharacteristic.writeValue(-1);
  //NotifyCharacteristic.writeValue(-1);
  BLE.advertise();

}

void loop() {
  serialEvent();
  BLE.advertise();
  BLEDevice central = BLE.central();
  ////Serial.println("- Discovering central device...");
  delay(100);

  if (central) {
    //Serial.println("* Connected to central device!");
    //Serial.print("* Device MAC address: ");
    //Serial.println(central.address());
    ////Serial.println(" ");

    while (central.connected()) {
      //serialEvent();
      if (detectionCharacteristic.written()) {
         detection = detectionCharacteristic.value();
         writedetectioninLED(detection);
         Serial1.print("o");
         delay(50);
         //recvUltrasonic();//////
         serialEvent();
         if(recv){
            parseUltrasonic();
         }
         delay(50);
         checkDist();
         
         if (checkDistance==true){
          ////Serial.println(checkDistance);
          sendtoPhone();
          checkDistance=false;
         }
         detectionCharacteristic.writeValue(-1);
         writedetectioninLED(-1);//done
       } 
    }
    
    ////Serial.println("* Disconnected to central device!");
  }
}

void writedetectioninLED(int detection) {
   ////Serial.println("- Characteristic <detection_type> has changed!");
   ////Serial.println(detection);
   switch (detection) {
      case detection_UP:
        ////Serial.println("* Actual value: UP (red LED on)");
        ////Serial.println(" ");
        digitalWrite(LEDR, LOW);
        digitalWrite(LEDG, HIGH);
        digitalWrite(LEDB, HIGH);
        digitalWrite(LED_BUILTIN, LOW);
        
        break;
      case detection_DOWN:
        ////Serial.println("* Actual value: DOWN (green LED on)");
        ////Serial.println(" ");
        digitalWrite(LEDR, HIGH);
        digitalWrite(LEDG, LOW);
        digitalWrite(LEDB, HIGH);
        digitalWrite(LED_BUILTIN, LOW);
        break;
      case detection_MIDDLE:
        ////Serial.println("* Actual value: MIDDLE (blue LED on)");
        ////Serial.println(" ");
        digitalWrite(LEDR, HIGH);
        digitalWrite(LEDG, HIGH);
        digitalWrite(LEDB, LOW);
        digitalWrite(LED_BUILTIN, LOW);
        break;
      case detection_RIGHT:
        ////Serial.println("* Actual value: RIGHT (built-in LED on)");
        ////Serial.println(" ");
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

void sendtoPhone(){
  BLE.advertise();
  BLEDevice phoneperipheral;
  //Serial.print("Try sending notify:");
  //Serial.println(notify);
  ////Serial.println("- Discovering peripheral device...");

  do
  {
    BLE.scanForUuid(phoneServiceUuid);
    phoneperipheral = BLE.available();
  } 
  while (!phoneperipheral);
  
  if (phoneperipheral) {
    ////Serial.println("* Peripheral device found!");
    ////Serial.print("* Device MAC address: ");
    ////Serial.println(phoneperipheral.address());
    ////Serial.print("* Device name: ");
    ////Serial.println(phoneperipheral.localName());
    ////Serial.print("* Advertised service UUID: ");
    ////Serial.println(phoneperipheral.advertisedServiceUuid());
    ////Serial.println(" ");
    BLE.stopScan();
    controlPeripheral(phoneperipheral);
  }
  else{
    ////Serial.println("* Connection to peripheral device failed!");
    BLE.stopScan();
  }
}

void controlPeripheral(BLEDevice peripheral) {
  ////Serial.println("- Connecting to peripheral device...");

  if (peripheral.connect()) {
    //Serial.println("* Connected to peripheral device!");
    ////Serial.println(" ");
  } else {
    ////Serial.println("* Connection to peripheral device failed!");
    ////Serial.println(" ");
    return;
  }
  ////Serial.println("- Discovering peripheral device attributes...");
  if (peripheral.discoverAttributes()) {
    //Serial.println("* Peripheral device attributes discovered!");
    ////Serial.println(" ");
  } else {
    //Serial.println("* Peripheral device attributes discovery failed!");
    ////Serial.println(" ");
    peripheral.disconnect();
    return;
  }
  BLECharacteristic NotifyCharacteristic = peripheral.characteristic(NotifyCharacteristicUuid);
  //delay(500);
    
  if (!NotifyCharacteristic) {
    //Serial.println("* Peripheral device does not have this_type characteristic!");
    peripheral.disconnect();
    return;
  } else if (!NotifyCharacteristic.canWrite()) {
    //Serial.println("* Peripheral does not have a writable gesture_type characteristic!");
    peripheral.disconnect();
    return;
  }
  while (peripheral.connected()) {
    ////Serial.println(notify);
    if(notify==1){
      NotifyCharacteristic.writeValue("1");
    }
    else if(notify==2){
      NotifyCharacteristic.writeValue("2");
    }
    else if(notify==3){
      NotifyCharacteristic.writeValue("3");
    }
    else if(notify==4){
      NotifyCharacteristic.writeValue("4");// emergency
    }
    else{
      
    }
    notify = -1;
    peripheral.disconnect();
  }
  
}

boolean recvUltrasonic(){
  static boolean recvInProgress=false;
  static byte ndx=0;
  char recvChara;
  recv = false;
  while(Serial1.available()>0){  //When serial is open for communication between Arduino boards
      recvChara=Serial1.read();
      //Serial.println(recvChara);
      if(recvInProgress==true){ //Receive in progress, serial reading not finished
        if(recvChara!=ultra_end){ //If received char is not end marker
          distanceUltrasonic[ndx]=recvChara;  //Read this char into current location of ultrasonic distance string 
          ndx++;  //Index move to the next location of ultrasonic distance string
          if(ndx>=numUltrasonic){
            ndx=numUltrasonic-1;
          }
        }
        else {  //received char is end marker
          distanceUltrasonic[ndx]='\0'; //Indicating the end of string
          recvInProgress=false;  //receive not in progress, serial reading finished
          ndx=0;  //reset index to 0
        }
      }
      else if(recvChara==ultra_start){  //receive not in progress, but serial reads start marker
        recvInProgress=true;  //so start a receiving progress
      }
      recv = true;
  }
  return recv;
}

void parseUltrasonic(){
  char * strtokStore;
  strtokStore=strtok(distanceUltrasonic,",");
  left_waist=atoi(strtokStore);
  strtokStore=strtok(NULL,",");
  right_waist=atoi(strtokStore);
  strtokStore=strtok(NULL,",");
  left_foot=atoi(strtokStore);
  strtokStore=strtok(NULL,",");
  right_foot=atoi(strtokStore);
}

void checkDist(){
  int n1 = 0;
  int n2 = 0;
  if (left_waist<50 || right_waist<50){
    ////Serial.println(left_waist);
    ////Serial.println(right_waist);
    n1 = 1; //waist detects obstacle
    checkDistance = true;
    //Serial.println( "Flag1 changed");
  }
  if(left_foot<200 || right_foot<200){
    ////Serial.println(left_foot);
    ////Serial.println(right_foot);
    n2 = 2; //foot detects obstacle
    checkDistance = true;
    //Serial.println( "Flag2 changed");
  }
  notify = n1+n2;
  left_waist=1000;
  right_waist=1000;
  left_foot=1000;
  right_foot=1000;
}
void serialEvent() {
  while(Serial1.available()){
    char inChar = (char)Serial1.read();  
    if(inChar=='D'){                 //emergency
      //BLE.disconnect();
      notify = 4;
      sendtoPhone();
      notify = -1;
      while(Serial1.available()){
        char tmp = (char)Serial1.read(); 
      }
    }
    else if( inChar == '<'){ .     //receive distance
      recvUltrasonic();
    }
  }
}
