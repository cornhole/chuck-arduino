#include <Arduino.h>

#include "VarSpeedServo.h"
#include "ax12.h"

#ifndef CHUCKCOMMANDS_H
#define CHUCKCOMMANDS_H

//comment to use regular servo 
//#define DYNAMIXEL  true
#define GRIPPERSERVO 12
#define THROWINGSERVO 15
class ChuckCommands{
  public:
    ChuckCommands();
    void init();
    void throwBeanBag(int,int);
    void moveDynamixel(int,int);
    void moveServo(int,int);
    void rotateArm(int);
    void graspBeanBag();
    void releaseBeanBag();
    void changeStartThrowPosition(int);
    void changeEndThrowPosition(int);
    void changeGraspPosition(int);
    void changeReleasePosition(int);
    void centerArm();
    void centerThumb();
    void resetArm();
    void relax(int);
  private:
  int graspPosition,
      releasePosition,
      initialThumbPosition,
      throwStartPosition,
      throwEndPosition,
      rotationStartPosition,
      armCenter;

    VarSpeedServo gripper;
    //servo declarations
    #ifdef DYNAMIXEL
    int throwingServo;
    enum  {roll=1,yaw=2};
    #else
    VarSpeedServo throwingServo;
    #endif
};
#endif

