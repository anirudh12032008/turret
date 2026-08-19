#include "config.h"
#include "motors.h"
#include "turret_sequences.h"

MotorController motors;
TurretSequences sequences(&motors);

int flywheelSpeed = 0;
int rotationSpeed = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  motors.init();
  sequences.init(&motors);
  
  Serial.println("\n=== TURRET CONTROL SYSTEM ===");
  Serial.println("Ready for commands:");
  Serial.println("F<0-255>  - Set flywheel speed");
  Serial.println("R<-255 to 255> - Set rotation speed");
  Serial.println("S         - Stop all motors");
  Serial.println("T         - Test sequence");
  Serial.println("FIRE      - Fire sequence");
  Serial.println("LEFT      - Rotate left");
  Serial.println("RIGHT     - Rotate right");
  Serial.println("ROTATE    - Full rotation");
  Serial.println("STATUS    - Show current status");
  Serial.println("=============================\n");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    input.toUpperCase();
    
    if (input.startsWith("F")) {
      String speedStr = input.substring(1);
      if (speedStr.length() > 0) {
        int speed = speedStr.toInt();
        motors.setFlywheelSpeed(speed);
        Serial.print("Flywheel: ");
        Serial.print(speed);
        Serial.println(" RPM");
      }
    }
    else if (input.startsWith("R")) {
      String speedStr = input.substring(1);
      if (speedStr.length() > 0) {
        int speed = speedStr.toInt();
        motors.setRotationSpeed(speed);
        Serial.print("Rotation: ");
        Serial.print(speed);
        Serial.println(" PWM");
      }
    }
    else if (input == "S") {
      motors.stopAll();
      Serial.println("All motors stopped");
    }
    else if (input == "T") {
      sequences.testSequence();
    }
    else if (input == "FIRE") {
      Serial.println("FIRING...");
      sequences.fireSequence();
      Serial.println("Fire complete");
    }
    else if (input == "LEFT") {
      sequences.rotateLeft();
    }
    else if (input == "RIGHT") {
      sequences.rotateRight();
    }
    else if (input == "ROTATE") {
      sequences.rotateFull();
    }
    else if (input == "STATUS") {
      printStatus();
    }
    else {
      Serial.println("Unknown command");
    }
  }
  
  delay(10);
}

void printStatus() {
  Serial.println("\n=== TURRET STATUS ===");
  Serial.print("Flywheel Speed: ");
  Serial.println(motors.getFlywheelSpeed());
  Serial.print("Rotation Speed: ");
  Serial.println(motors.getRotationSpeed());
  Serial.println("====================\n");
}
