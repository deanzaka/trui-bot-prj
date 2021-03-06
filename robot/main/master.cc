//Rosserial Node for the RBMT02
//@author: lintang
//
//
#include <arduino/Arduino.h>
#include <Wire.h>
#include <ros_lib/ros.h>
#include <ros_lib/geometry_msgs/Twist.h>

//Robot Kinematic Properties
#define L 0.45 //in meters, distance from wheel to center
#define R 0.1 //in meters, radius of wheel

//Speed Limiting Factor
#define rot_speedFactor 1//0.1
#define trans_speedXFactor 1//0.3
#define trans_speedYFactor 1//2.2


#define debugPin 13
#define hitPin 20
#define risePin 21
#define miscPneu1 22
#define miscPneu2 23
#define reset1 41
#define reset2 42
#define reset3 43

#define initialSpeed 0

//ros::NodeHandle nh;
//geometry_msgs::Twist twist_msg;

//ros::Publisher chatter("embedded_chat", &twist_msg);


int sendspeed1,sendspeed2,sendspeed3,hitBuffer;
float speedX,speedY,speedW;
int serveCommand;

// void assignSpeed( const geometry_msgs::Twist& rbmt_vel){
// float v1,v2,v3;

// //      Vy
// //      ^
// //      |
// //      |
// //      |-------> Vx

// // sqrt(3.0)/2.0, -1.0/2.0, -1.0,
// //   0.0        ,  1.0    , -1.0
// //-sqrt(3.0)/2.0, -1.0/2.0, -1.0;

// speedX = rbmt_vel.linear.x;
// speedY = rbmt_vel.linear.y;
// speedW = rbmt_vel.angular.z;
// serveCommand = (int)rbmt_vel.angular.y;
// //if(rbmt_vel.angular.x == 1) serveCommand = digitalWrite(hitPin,HIGH); else digitalWrite(hitPin,LOW);

// speedX = -trans_speedXFactor*speedX;
// speedY = trans_speedYFactor*speedY;

// v1 = (-sqrt(3.0)/2.0)*speedY + speedX/2 + rot_speedFactor*L*speedW;
// v2 = -speedX + rot_speedFactor*L*speedW; 
// v3 = (sqrt(3.0)/2.0)*speedY + speedX/2  + rot_speedFactor*L*speedW;


// sendspeed1 = v1/R*9.55; //Covert rad/s to RPM 
// sendspeed2 = v2/R*9.55; //Covert rad/s to RPM
// sendspeed3 = v3/R*9.55; //Covert rad/s to RPM 
// }

//ros::Subscriber<geometry_msgs::Twist> sub("read_velocity", &assignSpeed );

void toggleReset(){

// digitalWrite(reset1,HIGH);
// digitalWrite(reset2,HIGH);
// digitalWrite(reset3,HIGH);
// delay(500);
digitalWrite(reset1,LOW);
digitalWrite(reset2,LOW);
digitalWrite(reset3,LOW);
delay(500);
digitalWrite(reset1,HIGH);
digitalWrite(reset2,HIGH);
digitalWrite(reset3,HIGH);
}

void wireServe(byte wireData){
  Wire.beginTransmission(12);
  Wire.write(wireData);
  Wire.endTransmission();
}

int main() {

  //Timer0  
  //Setting   Divisor     Frequency
  //0x01        1           62500
  //0x02        8           7812.5
  //0x03        64          976.5625   <--DEFAULT
  //0x04        256         244.140625
  //0x05        1024        61.03515625

  //TCCR0B = TCCR0B & 0b11111000 | <setting>;
  const uint8_t header= 0xCE;
  const uint8_t footer= 0xEE;

  const uint8_t hit_mode= 0x0A;
  const uint8_t position_mode= 0x0B;
  const uint8_t hit_flag = 0x0F;
  const uint8_t rise_flag =0xF0;
  
  int fromSerial_1[2];
  int fromSerial_2[2];
  int fromSerial_3[2];

  init(); //Mandatory arduino setups, hardware registers etc
  Wire.begin(); //Start wire Comm
  // nh.initNode(); //Init board as a ROS Node
  // nh.advertise(chatter);
  // nh.subscribe(sub);

  // Serial.begin(115200);
  Serial1.begin(9600);
  Serial2.begin(9600);    
  Serial3.begin(9600);
  pinMode(hitPin,OUTPUT);
  pinMode(risePin,OUTPUT);
  pinMode(miscPneu1,OUTPUT);
  pinMode(miscPneu2,OUTPUT);

  pinMode(reset1,OUTPUT);
  pinMode(reset2,OUTPUT);
  pinMode(reset3,OUTPUT);
  digitalWrite(hitPin,LOW);
  digitalWrite(risePin,LOW);
  digitalWrite(miscPneu1,LOW);
  digitalWrite(miscPneu2,LOW);

  delay(1000);
  toggleReset();
  delay(500);

  speedX = 0;
  speedY = 0;
  speedW = 0;
  while (true){
    

  // if(nh.connected()){
  //   if(!nh.connected()){
  //   //   while(true){
  //       sendspeed1 = 0;
  //       sendspeed2 = 0;
  //       sendspeed3 = 0;
  //   //   }
  //   }
  // } 

    // if(Serial1.available()){//&& Serial1.read() == 0xCE){
    //   fromSerial_1[0] = Serial1.read();
    //   // fromSerial_1[1] = Serial1.read();
    //   twist_msg.linear.x = (fromSerial_1[0]);// | (fromSerial_1[1]<<8));
    // }

    // if(Serial2.available()){// && Serial2.read() == 0xCE){
    //   fromSerial_2[0] = Serial2.read();
    //   // fromSerial_2[1] = Serial2.read();
    //   twist_msg.linear.y = (fromSerial_2[0]);// | (fromSerial_2[1]<<8));
    // }

    // if(Serial3.available()){// && Serial3.read() == 0xCE){
    //   fromSerial_3[0] = Serial3.read();
    //   // fromSerial_3[1] = Serial3.read();
    //   twist_msg.linear.z = (fromSerial_3[0]);// | (fromSerial_3[1]<<8));
    // }

    // twist_msg.angular.x = sendspeed1;
    // twist_msg.angular.y = sendspeed2;
    // twist_msg.angular.z = sendspeed3;

    // chatter.publish( &twist_msg );
    
    uint8_t buffer1[7];
    uint8_t buffer2[7];
    uint8_t buffer3[7];


    buffer1[0]= header;
    buffer1[6]= footer;
    buffer1[1]= (sendspeed1 & 0x00FF);
    buffer1[2]= ((sendspeed1 & 0xFF00)>>8);
    buffer1[3]= 0;
    uint16_t checksum1= buffer1[0] + buffer1[1] + buffer1[2] + buffer1[6];
    buffer1[4]= checksum1 & 0x00FF;
    buffer1[5]= (checksum1 & 0xFF00) >> 8;


    analogWrite(13,buffer1[1]);

    buffer2[0]= header;
    buffer2[6]= footer;
    buffer2[1]= (sendspeed2 & 0x00FF);
    buffer2[2]= ((sendspeed2 & 0xFF00)>>8);
    buffer2[3]= 0;
    uint16_t checksum2= buffer2[0] + buffer2[1] + buffer2[2] + buffer2[6];
    buffer2[4]= checksum2 & 0x00FF;
    buffer2[5]= (checksum2 & 0xFF00) >> 8;


    buffer3[0]= header;
    buffer3[6]= footer;
    buffer3[1]= (sendspeed3 & 0x00FF);
    buffer3[2]= ((sendspeed3 & 0xFF00)>>8);
    buffer3[3]= 0;
    uint16_t checksum3= buffer3[0] + buffer3[1] + buffer3[2] + buffer3[6];
    buffer3[4]= checksum3 & 0x00FF;
    buffer3[5]= (checksum3 & 0xFF00) >> 8;

    //For normal operation
    Serial1.write(buffer1, 7);
    Serial2.write(buffer2, 7);
    Serial3.write(buffer3, 7);
    serveCommand = (serveCommand | 1<<3);
    wireServe(serveCommand);

    delay(1);
  // nh.spinOnce();
  




  
  }
  return 0;
}