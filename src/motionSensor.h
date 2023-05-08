#ifndef _MOTION_SENSOR_H_
#define _MOTION_SENSOR_H_

// Header
#include "Arduino.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

// Type defition
#define INTERRUPT_PIN 2
#define FIX_VALUE 30.0
struct ypr_t {float yaw, pitch, roll;};

// Function defition
int MotionSensor_init();       // initialize. return !0 when error
ypr_t MotionSensor_getYPR();    // read and get yaw/pitch/roll
ypr_t MotionSensor_getYPRFixed();    // read and get yaw/pitch/roll, fixed
String MotionSensor_getErrorDetails();  // return "" when no error

// Private Function
void __dmpDataReady();  // set interrupt flag true
float __abs(float x);
#endif
