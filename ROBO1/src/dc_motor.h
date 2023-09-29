#ifndef DC_MOTOR_H
#define DC_MOTOR_H

#include <stdint.h>

void dc_motor_init(void);
void dc_motor_run(void);
void dc_motor_1_full_run(uint8_t speed);
void dc_motor_2_full_run(uint8_t speed);
void dc_motor_3_full_run(uint8_t speed);
void dc_motor_4_full_run(uint8_t speed);
#endif // DC_MOTOR_H
