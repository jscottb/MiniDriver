/* 
  Dagu MiniDriver Library
  based on the Adafruit Motor shield library
  this code is public domain, enjoy!
*/

#ifndef _MiniDriver_h_
#define _MiniDriver_h_

#include <inttypes.h>
#include <avr/io.h>

#define MOTOR_L 9
#define MOTOR_L_DIRECTION 7

#define MOTOR_R 10
#define MOTOR_R_DIRECTION 8

#define FORWARD 1
#define BACKWARD 2
#define BRAKE 4
#define RELEASE 8

#define VOLTAGE_LEVEL A7

class MD_Motor {
public:
   MD_Motor(uint8_t motornum);
   bool run(uint8_t);
   void setSpeed(uint8_t);
   uint8_t getSpeed(void);
   uint8_t getState(void);
   uint8_t getDirection(void);
   int getVoltage(void);
      	
private:
   uint8_t motorspeed, motordirection, motorflags, currentspeed;
};

#endif
