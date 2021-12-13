//M202A team project - Palantir2021
//Control logic for sensor Arduino
//Reference: https://forum.arduino.cc/t/serial-input-basics-updated/382007/3


/*****
 * Ultrasonic modules setup
 * Wiring:
 * 2,3,4,5,6,7,8,9 - D2, D3, D4, D5, D6, D7, D8, D9
 * All Vcc of Ultrasonic modules - Vin of Arduino
 * All Gnd of Ultrasonic modules - GND of Arduino
*****/
//int enable_detect=0;
//Left waist ultrasonic module
const int echo_wl=2;
const int trig_wl=3;
int left_waist=1000;
//Right waist ultrasonic module
const int echo_wr=4; 
const int trig_wr=5; 
int right_waist=1000;
//Left foot ultrasonic module
const int echo_fl=6;
const int trig_fl=7;
int left_foot=1000;
//Right foot ultrasonic module
const int echo_fr=8; 
const int trig_fr=9;
int right_foot=1000;
String readdata = "";
void setup(){
  //Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(echo_wl,INPUT); 
  pinMode(trig_wl,OUTPUT);
  pinMode(echo_wr,INPUT);
  pinMode(trig_wr,OUTPUT);
  pinMode(echo_fl,INPUT);
  pinMode(trig_fl,OUTPUT);
  pinMode(echo_fr,INPUT);
  pinMode(trig_fr,OUTPUT);  
}

void loop(){
  serialEvent();
  basicTask();
}
void serialEvent() {
  
   while(Serial1.available() > 0)         
  {
    //if(char(Serial.read())=='\n')
    //  break;
    readdata  =  readdata  +char(Serial1.read());
    //delay(2);
  }
    //Everytime sensor Arduino gets something from controller Arduino
    //It conducts a group of detection for left & right waist and left & right foot
    //So it needs controller Arduino to send something continuously
    //Nothing comes from controller, which means there's no need to use ultrasonic modules; sensor Arduino does nothing
    // get enable_detect:
    //Serial.print(readdata);
    if (readdata == "o") {
    /******START DETECTION******/
    /***Left waist***/
    digitalWrite(trig_wl,LOW);
    delayMicroseconds(2);
    digitalWrite(trig_wl,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_wl,LOW); //Send a 10ms high pulse to trig trig_wr
    left_waist = (pulseIn(echo_wl,HIGH))/58.0;//Receive echoed signal
    /***Right waist***/
    digitalWrite(trig_wr,LOW);
    delayMicroseconds(2);
    digitalWrite(trig_wr,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_wr,LOW);
    right_waist = (pulseIn(echo_wr,HIGH))/58.0;
    /***Left foot***/
    digitalWrite(trig_fl,LOW);
    delayMicroseconds(2);
    digitalWrite(trig_fl,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_fl,LOW);
    left_foot = (pulseIn(echo_fl,HIGH))/58.0;
    /***Right foot***/
    digitalWrite(trig_fr,LOW);
    delayMicroseconds(2);
    digitalWrite(trig_fr,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_fr,LOW);
    right_foot = (pulseIn(echo_fr,HIGH))/58.0;
    delay(100);
    /***SEND DISTANCES***/
    serialWriteDistances();
    
  }
  readdata = "";
  
}

void basicTask(){
   /***Left foot***/
    digitalWrite(trig_fl,LOW);
    delayMicroseconds(2);
    digitalWrite(trig_fl,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_fl,LOW);
    left_foot = (pulseIn(echo_fl,HIGH))/58.0;
    /***Right foot***/
    digitalWrite(trig_fr,LOW);
    delayMicroseconds(2);
    digitalWrite(trig_fr,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_fr,LOW);
    right_foot = (pulseIn(echo_fr,HIGH))/58.0;
    delay(50);
    if(left_foot<30||right_foot<30){
      Serial1.print("D");
    }
}
//Function of sending <left_waist,right_waist,left_foot,right_foot> to controller Arduino
void serialWriteDistances(){
   Serial1.print('<');
   Serial1.print('<');
   Serial1.print(String(left_waist));
   Serial1.print(',');
   Serial1.print(String(right_waist));
   Serial1.print(',');
   Serial1.print(left_foot);
   Serial1.print(',');
   Serial1.print(right_foot);
   Serial1.println('>');
   
}
