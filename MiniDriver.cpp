/*
  Dagu MiniDriver Library
  based on the Adafruit Motor shield library
  this code is public domain, enjoy!
*/

#if (ARDUINO >= 100)
   #include "Arduino.h"
#else
   #include <avr/io.h>
   #include "WProgram.h"
#endif

#include "MiniDriver.h" 

MD_Motor::MD_Motor(uint8_t num) {
   switch (num) {
      case 1:
      case MOTOR_L:
         motorspeed =     MOTOR_L;
         motordirection = MOTOR_L_DIRECTION;
         break;

      case 2:
      case MOTOR_R:
         motorspeed =     MOTOR_R;
         motordirection = MOTOR_R_DIRECTION;
         break;

     default:
         return;
   }

   pinMode(motorspeed, OUTPUT); 
   pinMode(motordirection, OUTPUT);
}

bool MD_Motor::run(uint8_t cmds) {
   if (((FORWARD | BACKWARD) & cmds) == (FORWARD | BACKWARD)) {
      return false;
   }

   if (((BRAKE | RELEASE) & cmds) == (BRAKE | RELEASE)) {
      return false;
   }

   if ((cmds & FORWARD) == FORWARD) {
      digitalWrite(motordirection, HIGH);
      motorflags = (motorflags & (BRAKE | RELEASE)) | FORWARD;
   }

   if ((cmds & BACKWARD) == BACKWARD) {
      digitalWrite(motordirection, LOW);
      motorflags = (motorflags & (BRAKE | RELEASE)) | BACKWARD;
   }

   if ((cmds & RELEASE) == RELEASE) {
      analogWrite(motorspeed, currentspeed);
      motorflags = (motorflags & (FORWARD | BACKWARD)) | RELEASE;
   }

   if ((cmds & BRAKE) == BRAKE) {
      analogWrite(motorspeed, 0);
      motorflags = (motorflags & (FORWARD | BACKWARD)) | BRAKE;
   }

   return true;
}

void MD_Motor::setSpeed(uint8_t speed) {
   if (speed > 255) speed = 255;
   else if (speed < 0) speed = 0;

   currentspeed = speed;
   analogWrite(motorspeed, speed);
}

uint8_t MD_Motor::getSpeed(void) {
   return (uint8_t) currentspeed;
}

uint8_t MD_Motor::getState(void) {
   return motorflags & (BRAKE | RELEASE);
}

uint8_t MD_Motor::getDirection(void) {
   return motorflags & (FORWARD | BACKWARD);
}

int MD_Motor::getVoltage(void) {
   int ana_in = analogRead(VOLTAGE_LEVEL);
   return (int) (ana_in / 10);
}

