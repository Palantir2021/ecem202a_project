//M202A team project - Palantir2021
/*
Wiring:
2,3,4,5,6,7,8,9 - D2, D3, D4, D5, D6, D7, D8, D9
All Vcc of Ultrasonic modules - Vin of Arduino
All Gnd of Ultrasonic modules - GND of Arduino
*/

//Left waist ultrasonic module
const int echo_wl=2;
const int trig_wl=3;

//Right waist ultrasonic module
const int echo_wr=4; 
const int trig_wr=5; 

//Left foot ultrasonic module
const int echo_fl=6;
const int trig_fl=7;

//Right foot ultrasonic module
const int echo_fr=8; 
const int trig_fr=9; 




int delay_num=0;
void setup()
{
  Serial.begin(9600);  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(echo_wr,INPUT); 
  pinMode(trig_wr,OUTPUT);
  pinMode(echo_wl,INPUT);
  pinMode(trig_wl,OUTPUT);
  pinMode(echo_fl,INPUT);
  pinMode(trig_fl,OUTPUT);
  pinMode(echo_fr,INPUT);
  pinMode(trig_fr,OUTPUT);
  
}

void loop()
{
  /******Left waist distance detecting******/
  digitalWrite(trig_wr,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_wr,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_wr,LOW); //发一个10ms的高脉冲去触发trig_wr
  float left_waist = pulseIn(echo_wr,HIGH);//接收高电平时间
  left_waist = left_waist/58.0;//计算距离
  Serial.print("left_waist : ");  //输出距离
  Serial.print(left_waist);
  Serial.println("cm");  //输出单位
  //delay(100);   //间隔100uS
  


  /******Right waist distance detecting******/
  digitalWrite(trig_wl,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_wl,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_wl,LOW); //发一个10ms的高脉冲去触发trig_wl
  float right_waist = pulseIn(echo_wl,HIGH);//接收高电平时间
  right_waist = right_waist/58.0;//计算距离
  Serial.print("right_waist : ");
  Serial.print(right_waist);
  Serial.println("cm");

  /******Left foot distance detecting******/
  digitalWrite(trig_fl,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_fl,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_fl,LOW); //发一个10ms的高脉冲去触发trig_wr
  float left_foot = pulseIn(echo_fl,HIGH);//接收高电平时间
  left_foot = left_foot/58.0;//计算距离
  Serial.print("left_foot : ");
  Serial.print(left_foot);
  Serial.println("cm");

  
  /******Right foot distance detecting******/
  digitalWrite(trig_fr,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_fr,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_fr,LOW); //发一个10ms的高脉冲去触发trig_wr
  float right_foot = pulseIn(echo_fl,HIGH);//接收高电平时间
  right_foot = right_foot/58.0;//计算距离
  Serial.print("right_foot : ");
  Serial.print(right_foot);
  Serial.println("cm");

  delay(500);   //循环间隔100uS

}
