#include "chuckCommands.h"

ChuckCommands::ChuckCommands(){}

void ChuckCommands::init(){
  gripper.attach(12);
  gripper.write(90,100);

  #ifdef DYNAMIXEL
  armCenter=400;
  throwStartPosition=250;
  throwEndPosition=650;
  throwingServo=2;
  #else
  armCenter=90;
  throwStartPosition=30;
  throwEndPosition=150;
  throwingServo.attach(THROWINGSERVO);
  #endif
  graspPosition=25;
  releasePosition=160;
  initialThumbPosition=140;
  rotationStartPosition=512;
}

void ChuckCommands::throwBeanBag(int releaseVelocity, int releaseDelay){
  int delayTime = 700;
  #ifdef DYNAMIXEL
  ax12SetRegister2(throwingServo,AX_GOAL_SPEED_L,50);
  SetPosition(throwingServo,throwStartPosition);
  delay(delayTime);
  ax12SetRegister2(throwingServo,AX_GOAL_SPEED_L,releaseVelocity);
  SetPosition(throwingServo,throwEndPosition);
  #else
  throwingServo.write(throwStartPosition,50);
  delay(delayTime);
  throwingServo.write(throwEndPosition,releaseVelocity);
  #endif
  delay(releaseDelay);
  releaseBeanBag();
  delay(1000);
  resetArm();
}

void ChuckCommands::moveDynamixel(int servo, int position){
  SetPosition(servo,position);
}

void ChuckCommands::moveServo(int servo, int position){
  if(servo==0){
    throwingServo.write(position);
  }else if(servo==1){
    gripper.write(position);
  }
}

void ChuckCommands::rotateArm(int rotationValue){
  ChuckCommands::moveDynamixel(2,rotationValue);
}

void ChuckCommands::graspBeanBag(){
  digitalWrite(0,HIGH); 
  gripper.write(90,100);
  delay(1000);
  digitalWrite(0,LOW);
}

void ChuckCommands::releaseBeanBag(){
  gripper.write(releasePosition,250); 
}

void ChuckCommands::changeStartThrowPosition(int position){
  throwStartPosition = position; 
}

void ChuckCommands::changeEndThrowPosition(int position){
  throwEndPosition = position; 
}

void ChuckCommands::changeGraspPosition(int position){
  graspPosition = position;
}

void ChuckCommands::changeReleasePosition(int position){
  releasePosition = position;
}

void ChuckCommands::centerArm(){
  #ifdef DYNAMIXEL
  ax12SetRegister2(throwingServo,AX_GOAL_SPEED_L,50);
  SetPosition(throwingServo,armCenter);
  #else
  throwingServo.write(armCenter,50);
  #endif
}

void ChuckCommands::centerThumb(){
  gripper.write(initialThumbPosition);
}

void ChuckCommands::resetArm(){
  centerArm();
  centerThumb();
}

void ChuckCommands::relax(int servo){
  if(servo ==0){
    Relax(1);
    Relax(2);
    #ifdef DYNAMIXEL
    Relax(3);
    #endif
  }
  Relax(servo);
}

