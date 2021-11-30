#include <LobotServoController.h>

LobotServoController myse;
unsigned long duration1;
unsigned long duration2;
unsigned long duration3;
unsigned long duration4;

void setup() {
 pinMode(9, INPUT);
  pinMode(4, INPUT);
   pinMode(5, INPUT);
    pinMode(6, INPUT);
  Serial.begin(9600);
 while(!Serial);
 myse.runActionGroup(0,1);
delay(1500);



}

void loop() {
   duration1 = pulseIn(9, HIGH);//右油门左右
   duration2 = pulseIn(4, HIGH);//左油门上下
   //duration3 = pulseIn(5, HIGH);//右油门上下
   //duration4 = pulseIn(6, HIGH);//左油门左右

if(duration2>1350&&duration2<1550&&duration1>1350&&duration1<1550){
 myse.runActionGroup(0,2);
delay(2000);
myse.stopActionGroup();
}
  
 if(duration2>1750){
 myse.runActionGroup(1,0);
 }

if(duration2<1200&&duration2>800){
myse.runActionGroup(2,0);
}

//////////////////////////

   
 /*if(duration4>1750){
 myse.runActionGroup(4,0);
 }

if(duration4<1200&&duration4>800){
myse.runActionGroup(3,0);
}*/

//////////////////////////


 if(duration1>1750){
 myse.runActionGroup(12,0);
 }

if(duration1<1200&&duration1>800){
myse.runActionGroup(11,0);
}

}
////////////////////////


 
