#include "motor.h"
#include "pid.h"
#include "math.h"
#include "control_motor.h"
#include "motionSensor.h"

float set_value[2],real_value[2];
int output_value[2];
extern float Pitch;
extern float Roll;
extern float first_Pitch,first_Roll;
extern float kp_pit,kd_pit;
extern float kp_rol,kd_rol;
extern int timeCount;
float step=8;


void reset_mode(void)   //自稳
{
	kp_rol=25;
	kd_rol=4;
	output_value[1]=PID_roll_Count(first_Roll,Roll);	
	roll_run(output_value[1]);
}


void stri_line_mode1(void)   //pitch0度
{
	kp_rol=30;
	kd_rol=5;
	int roll_set;
	roll_set=0;
	output_value[1]=PID_roll_Count(roll_set,Roll);
	roll_run(output_value[1]);
	Serial.println(output_value[1]);
}


void stri_line_mode2(void)//40度
{
	kp_rol=25;
	kd_rol=1;
	int roll_set;
	float amp_roll=20;
	roll_set=amp_roll*sin(2.0*PI*timeCount/T);
	output_value[1]=PID_roll_Count(roll_set,Roll);
	roll_run(output_value[1]);
	Serial.println(output_value[1]);
// 	kp_pit=25;kd_pit=800;
// 	kp_rol=25;kd_rol=800;
//   static int count=0;
// 	int pitch_set,roll_set;
// 	float amp_pitch=10.606;
// 	float amp_roll=10.606;
// 	count+=10;         //十毫秒计算一次PID
// 	pitch_set=amp_pitch*sin(2.0*PI*count/T);
// 	roll_set=amp_roll*sin(2.0*PI*count/T);
// 	if(count>=1350) count=0;
// 	output_value[0]=PID_pitch_Count(pitch_set,Pitch);
// 	output_value[1]=PID_roll_Count(roll_set,Roll);
//   	pitch_run(output_value[0]);
// 	roll_run(output_value[1]);
}


void stri_line_mode3(void)//30度
{
	kp_rol=20;
	kd_rol=1;
	int roll_set;
	float amp_roll=15;
	roll_set=amp_roll*sin(2.0*PI*timeCount/T);
	output_value[1]=PID_roll_Count(roll_set,Roll);
	roll_run(output_value[1]);
	Serial.println(output_value[1]);
}


void stri_line_mode4(void)//150度
{
// 	kp_pit=25;kd_pit=800;
// 	kp_rol=25;kd_rol=800;
//   static int count=0;
// 	int pitch_set,roll_set;
// 	float amp_pitch=8*1.61;
// 	float amp_roll=8;
// 	count+=10;         //十毫秒计算一次PID
// 	pitch_set=amp_pitch*sin(2.0*PI*count/T);
// 	roll_set=amp_roll*sin(2.0*PI*count/T);
// 	if(count>=1350) count=0;
// 	output_value[0]=PID_pitch_Count(pitch_set,Pitch);
// 	output_value[1]=PID_roll_Count(roll_set,Roll);
//   pitch_run(output_value[0]);
// 	roll_run(output_value[1]);
}


void circle_mode5(void)//画圆
{
// 	kp_pit=25;kd_pit=800;
// 	kp_rol=25;kd_rol=800;
	
//   static int angle=0;
// 	float pitch_set,roll_set;
// 	angle+=step;
//   if(angle>=1080) angle=0;	
// 	pitch_set=15.0*sin(angle*PI/540.0);
// 	roll_set=18*cos(angle*PI/540.0);
// 	output_value[0]=PID_pitch_Count(pitch_set,Pitch);
// 	output_value[1]=PID_roll_Count(roll_set,Roll);
//   pitch_run(output_value[0]);
// 	roll_run(output_value[1]);
}

void pitch_run(int speed)
{
  if(speed>=0)  
	{
		motor_A(speed);
		motor_B(0);
	}
  else         
	{			
		motor_A(0);
		motor_B(-speed);
	}
}

void roll_run(int speed)
{
  if(speed>=0)  
	{
		motor_A(speed);
		motor_B(0);
	}	
  else         
	{
		motor_A(0);
		motor_B(-speed);
	}
}