#include "chuckCommands.h"
#include "SerialCommand.h"
#include "ax12.h"

boolean ledState = false;
ChuckCommands cCommands;
SerialCommand sCmd(Serial);

void setup(){
  cCommands.init();
  pinMode(0,OUTPUT);
  cCommands.resetArm();
  Serial.begin(115200);
  
  // creating new serialcommands "serial command"  "callback function name"
  sCmd.addCommand("toggleLED",                  serialcommandToggleLED);
  sCmd.addCommand("torqueOff",                  serialcommandTorqueOff);
  sCmd.addCommand("graspBeanBag",               serialcommandGraspBeanBag);
  sCmd.addCommand("releaseBeanBag",             serialcommandReleaseBeanBag);
  sCmd.addCommand("throwBeanBag",               serialcommandThrowBeanBag);
  sCmd.addCommand("rotateArm",                  serialcommandRotateArm);
  sCmd.addCommand("centerArm",                  serialcommandCenterArm);
  sCmd.addCommand("centerThumb",                serialcommandCenterThumb);
  sCmd.addCommand("resetArm",                   serialcommandResetArm);
  sCmd.addCommand("setThrowPosition",           serialcommandSetThrowPosition);
// -------------10------------------------
  sCmd.addCommand("setGripperPosition",         serialcommandSetGripperPosition);
  sCmd.addCommand("setDynamixelPosition",       serialcommandSetDynamixelPosition);
  sCmd.addCommand("setServoPosition",           serialcommandSetServoPosition);
  delay(2000);
}

void loop(){
    sCmd.readSerial();
}

void serialcommandToggleLED(SerialCommand this_scmd){
    ledState = !ledState;
    digitalWrite(0,ledState);
}

void serialcommandTorqueOff(SerialCommand this_scmd){
    cCommands.relax(atoi(this_scmd.next()));
}

void serialcommandSetDynamixelPosition(SerialCommand this_scmd){
    cCommands.moveDynamixel(atoi(this_scmd.next()),atoi(this_scmd.next()));
}

void serialcommandSetServoPosition(SerialCommand this_scmd){
  cCommands.moveServo(atoi(this_scmd.next()),atoi(this_scmd.next()));
}

void serialcommandGraspBeanBag(SerialCommand this_scmd){
  cCommands.graspBeanBag();
}

void serialcommandReleaseBeanBag(SerialCommand this_scmd){
  cCommands.releaseBeanBag();
}

void serialcommandThrowBeanBag(SerialCommand this_scmd){
  cCommands.throwBeanBag(atoi(this_scmd.next()),atoi(this_scmd.next()));
}

void serialcommandCenterArm(SerialCommand this_scmd){
  cCommands.centerArm();
}

void serialcommandCenterThumb(SerialCommand this_scmd){
  cCommands.centerThumb();
}

void serialcommandSetGripperPosition(SerialCommand this_scmd){
  String gripperLocation = this_scmd.next();
  if(gripperLocation == "grab"){
    cCommands.changeGraspPosition(atoi(this_scmd.next()));
  }else if(gripperLocation == "release"){
    cCommands.changeReleasePosition(atoi(this_scmd.next()));
  }
}

void serialcommandSetThrowPosition(SerialCommand this_scmd){
  String setPosition = this_scmd.next();
  if(setPosition=="start"){
    cCommands.changeStartThrowPosition(atoi(this_scmd.next()));
  }else if (setPosition =="end"){
    cCommands.changeEndThrowPosition(atoi(this_scmd.next()));
  }
}

void serialcommandRotateArm(SerialCommand this_scmd){
  int rotationValue = atoi(this_scmd.next());
  cCommands.rotateArm(rotationValue);
}

void serialcommandResetArm(SerialCommand this_scmd){
  cCommands.resetArm();
}

