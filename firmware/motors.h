#ifndef MOTORS_H
#define MOTORS_H

#include "config.h"

class MotorController {
private:
  int flywheelSpeed;
  int rotationSpeed;
  unsigned long lastFlywheelUpdate;
  unsigned long lastRotationUpdate;

public:
  MotorController();
  
  void init();
  
  void setFlywheelSpeed(int speed);
  void setRotationSpeed(int speed);
  
  int getFlywheelSpeed();
  int getRotationSpeed();
  
  void stopAll();
  void stopFlywheel();
  void stopRotation();
  
private:
  void setMotorSpeed(int pwmPin, int dirPin, int speed);
  void setPWM(int pin, int speed);
  void setDirection(int pin, int direction);
  int constrain(int value, int minVal, int maxVal);
};

#endif
