#ifndef SERVO_H
#define SERVO_H

#include "pwm.h"

// PWM test for servo motors
pwm_t * servo1_init(void);
pwm_t * servo2_init(void);

int theta1(float angle);

#endif 
