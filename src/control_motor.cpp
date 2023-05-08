#include "control_motor.h"

//引脚定义

#define PWMA 9
#define PWMB 10

#define A1 4
#define A2 7
#define _B1 12
#define B2 13



void motor_A(int a){
  if(a>0)
  {
    if(a>255){a=255;}
  digitalWrite(A1,HIGH);
  digitalWrite(A2,LOW);
  analogWrite(PWMA,a);
  }
  else
  {
    if(a<-255){a=-255;}
  digitalWrite(A1,LOW);
  digitalWrite(A2,HIGH);
  analogWrite(PWMA,abs(a));
  }
}

void motor_B(int b){
  if(b>0)
  {
    if(b>255){b=255;}
  digitalWrite(_B1,HIGH);
  digitalWrite(B2,LOW);
  analogWrite(PWMB,abs(b));
  }
  else
  {
    if(b<-255){b=-255;}
  digitalWrite(_B1,LOW);
  digitalWrite(B2,HIGH);
  analogWrite(PWMB,abs(b));
  }
}

void motorInitial()
{
pinMode(A1,OUTPUT);
pinMode(A2,OUTPUT);
pinMode(PWMA,OUTPUT);
pinMode(_B1,OUTPUT);
pinMode(B2,OUTPUT);
}