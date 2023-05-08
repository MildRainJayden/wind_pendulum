
float Pitch, Roll, Yaw; //俯仰角
float first_Pitch, first_Roll, flag = 1;
int mode = 1;

#include <Arduino.h>
#include "motor.h"
#include "pid.h"
#include "math.h"
#include "I2Cdev.h"
#include "control_motor.h"
#include "motionSensor.h"

#define LED_PIN 13
#define BUTTON_PIN 8
int initCode = 0;
int timeCount = 0;
int timeL = 0;
int timeR = 0;
ypr_t now;


void setup()
{
	Serial.begin(9600);
	initCode = MotionSensor_init();
	pinMode(LED_PIN, OUTPUT);
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	if (initCode)
	{
		digitalWrite(LED_PIN, HIGH);
		Serial.println(MotionSensor_getErrorDetails());
	}
	timeL = millis();
}

void loop()
{
	while(digitalRead(BUTTON_PIN) == HIGH) Serial.println("PAUSE");

	now = MotionSensor_getYPR();
	Pitch = now.pitch;
	Roll = now.roll;
	// Serial.print("yaw:");
    // Serial.print(now.yaw);
    // Serial.print(", pitch:");
    // Serial.print(now.pitch);

    Serial.print("roll:");
    Serial.print(now.roll);
    Serial.print(", output:");

	timeR = millis();
	timeCount = (timeCount + timeR - timeL) % T;
	timeL = timeR;

	switch (mode)
	{
	case 0:
		reset_mode();
		break;
	case 1:
		stri_line_mode1();
		break;
	case 2:
		stri_line_mode2();
		break;
	case 3:
		stri_line_mode3();
		break;
	case 4:
		stri_line_mode4();
		break;
	case 5:
		circle_mode5();
		break;
	}
	if (flag)
	{
		first_Pitch = Pitch;
		first_Roll = Roll;
		flag = 0;
	}
}

void serialEvent()
{
    while (Serial.available())
    {
        mode = Serial.read();
    }
}