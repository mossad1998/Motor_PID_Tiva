#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "tm4c123gh6pm.h"
#include <string.h>
#include "Debug_Driver.h"




#ifndef __PWM_Driver_H__
#define __PWM_Driver_H__


extern void CLK_PWM_Enable(int PWM_module);                                     //Clock for Port
extern void Use_PWM_Divisor(int System_Clock,int PWM_Clock);                     //Enable or Disable Analog and Digital
extern void PWM_Generator_Enable(int PWM_module,int Generator,char type[10]);   //General i/o or Alternative Function
extern void PWM_Action_For_Load(int PWM_module,int Generator,char Comparator,char type[10]);             //Input or Output
extern void PWM_Action_Comparator_Down(int PWM_module,int Generator,char Comparator,char type[10]);             //Input or Output
extern void PWM_Set_Frequency(int PWM_module,int Generator,int Frequency,int PWM_Clock_MHz);          //Pullup or Pulldown
extern void PWM_Set_Duty_Cycle(int PWM_module,int Generator,char Comparator,int Duty);          //Pullup or Pulldown
extern void PWM_Module_Start(int PWM_module);                           //To Read Data


#endif