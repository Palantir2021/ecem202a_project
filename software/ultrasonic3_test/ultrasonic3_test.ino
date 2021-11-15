//M202A team project - Palantir2021
//
//Middle ultrasonic module
const int echo_m=5; 
const int trig_m=4; 

//Left ultrasonic module
const int echo_l=3;
const int trig_l=2;

//Right ultrasonic module
const int echo_r=6;
const int trig_r=7;
int delay_num=0;
void setup()
{
  Serial.begin(9600);  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(echo_m,INPUT); 
  pinMode(trig_m,OUTPUT);
  pinMode(echo_l,INPUT);
  pinMode(trig_l,OUTPUT);
  pinMode(echo_r,INPUT);
  pinMode(trig_r,OUTPUT);

  
}

void loop()
{
  /******Middle distance detecting******/
  digitalWrite(trig_m,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_m,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_m,LOW); //发一个10ms的高脉冲去触发trig_m
  float distance_m = pulseIn(echo_m,HIGH);//接收高电平时间
  distance_m = distance_m/58.0;//计算距离
  Serial.print("distance_m : ");  //输出距离
  Serial.print(distance_m);
  Serial.println("cm");  //输出单位
  delay(100);   //间隔100uS
  


  /******Left distance detecting******/
  digitalWrite(trig_l,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_l,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_l,LOW); //发一个10ms的高脉冲去触发trig_m
  float distance_l = pulseIn(echo_l,HIGH);//接收高电平时间
  distance_l = distance_l/58.0;//计算距离
  Serial.print("distance_l : ");
  Serial.print(distance_l);
  Serial.println("cm");

  /******Right distance detecting******/
  digitalWrite(trig_r,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_r,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_r,LOW); //发一个10ms的高脉冲去触发trig_m
  float distance_r = pulseIn(echo_r,HIGH);//接收高电平时间
  distance_r = distance_r/58.0;//计算距离
  Serial.print("distance_r : ");
  Serial.print(distance_r);
  Serial.println("cm");

  delay(200);   //循环间隔100uS

}
