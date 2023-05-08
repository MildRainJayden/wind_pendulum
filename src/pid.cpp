#include "pid.h"
#include "math.h"
extern float Pitch,Roll,Yaw; 		//欧拉角
float kp_pit,kd_pit;
float kp_rol,kd_rol;
float I_limit;


     float D_date_pitch=0,D_date_roll=0;
     float  I_error_pitch,out_date;                //当前的误差
     float  Last_error_pitch=0;      //上一次的误差


int PID_pitch_Count(float set_point,float input_date)   
{

  I_error_pitch = set_point - input_date;
  D_date_pitch=I_error_pitch-Last_error_pitch;
  out_date=kp_pit*I_error_pitch+kd_pit*(I_error_pitch-Last_error_pitch);
	Last_error_pitch=I_error_pitch;	
	if(out_date>=900)
	{ 
		out_date=900;   
	}           //输出限幅
	if(out_date<=-900) 
	{
		out_date=-900;
	}
	return 255*(out_date/900);
}



int PID_roll_Count(float set_point,float input_date)   
{
	float  I_error_roll,out_date;                //当前的误差
  static float  Last_error_roll=0;      //上一次的误差
	I_error_roll = set_point - input_date;
	D_date_roll=I_error_roll-Last_error_roll;
	out_date=kp_rol*I_error_roll+kd_rol*(I_error_roll-Last_error_roll);
	Last_error_roll=I_error_roll;
	if(out_date>=900)
	{ 
		out_date=900;   
	}           //输出限幅
	if(out_date<=-900) 
	{
		out_date=-900;
	}
	return 255*(out_date/900);
}



