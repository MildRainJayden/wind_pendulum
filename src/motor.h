#ifndef _MOTOR_H
#define _MOTOR_H
#include "Arduino.h"

#define T 1350
// #define PI  3.141592653589793f

void reset_mode(void);
void stri_line_mode1(void);
void stri_line_mode2(void);//45度
void stri_line_mode3(void);//30度
void stri_line_mode4(void);//150度
void circle_mode5(void);//画圆

void pitch_run(int speed);
void roll_run(int speed);
#endif

