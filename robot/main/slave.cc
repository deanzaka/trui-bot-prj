#include <arduino/Arduino.h>
#include <Wire.h>
int delay1 = 500;
int n = 1;
int sensorValue1, sensorValue2, sensorValue3, hit, i;
int gripAction = 3;
int pullAction = 7;
int hitAction = 8;
const int threshold = 300;
byte commandByte;

void commandInput(int byteRecieved){
  commandByte = Wire.read();
}

void setup()
{
  Wire.begin(12);
  Wire.onReceive(commandInput);
  pinMode(gripAction, OUTPUT);
  pinMode(pullAction, OUTPUT);
  pinMode(hitAction, OUTPUT);

}

int main() {
  init();// this needs to be called before setup() or some functions won't work there
  setup();
  while(true){
    if((commandByte & B00000001) == 1) digitalWrite(gripAction, HIGH); else if ((commandByte & B00000100) == 0) digitalWrite(gripAction, LOW);
    if((commandByte & B00000010)>>1 == 1) digitalWrite(pullAction, HIGH); else if((commandByte & B00000100)>>1 == 0) digitalWrite(pullAction, LOW);
    if((commandByte & B00000100)>>2 == 1) digitalWrite(hitAction, HIGH); else if((commandByte & B00000100)>>2 == 0) digitalWrite(hitAction, LOW);
    if((commandByte & B00001000)>>3 == 1) {
      digitalWrite(gripAction, HIGH); //pegang
      delay(delay1);
      digitalWrite(pullAction, HIGH); //turun
      delay(delay1*4);
      digitalWrite(gripAction, LOW);  //lepas
      hit = 1;
      while(hit == 1){
        sensorValue1 = analogRead(14);   
        sensorValue2 = analogRead(15);
        sensorValue3 = analogRead(16);
        if((sensorValue1 < threshold) || (sensorValue2 < threshold) || (sensorValue3 < threshold)){
          digitalWrite(hitAction, HIGH);
          delay(delay1*3);
          digitalWrite(pullAction, LOW);
          digitalWrite(hitAction, LOW);
          hit = 0;
        }
      }
    }
  }
  return 0;
}
