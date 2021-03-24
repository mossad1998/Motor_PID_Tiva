#include "tm4c123gh6pm.h"
#include "GPIO_Driver.h"
#include "ADC_Driver.h"
#include "PWM_Driver.h"
#include <stdint.h>
#include "stdio.h"

#define  ARM_CM_DEMCR      (*(uint32_t *)0xE000EDFC)

#define  ARM_CM_DWT_CTRL   (*(uint32_t *)0xE0001000)

#define  ARM_CM_DWT_CYCCNT (*(uint32_t *)0xE0001004)


void PORTE_Initialization();
void ADC_Initialization();
float Driver_Angle(void);
float Vehicle_Angle(void);
void PortA_Intialization(void);
void PWM_Intialization(void);
void Delay(unsigned long counter);
float voltage;
char text[40];

void main()
{
  PORTE_Initialization();
  ADC_Initialization();
  PWM_Intialization();
	
    while(1)
    {
      float error = Vehicle_Angle()-Driver_Angle();
      if(error > 0)
      {
        PIN_WRITE_DIGITAL('A',6,"LOW");
      }
      else if(error < 0)
      {
      PIN_WRITE_DIGITAL('A',6,"HIGH");
      }
      //sprintf(text,"Error:%0.3f,\n", error);
      //printf("%s",text);

      
    }
}

void PORTE_Initialization()
{
  CLK_Enable('E');                                         //Enable Port E clock
  GPIO_PORT_UNLOCK('E');                                   //Unlock for port
  
  PIN_CONTROL_UNLOCK('E',1);                               //Make Changes To Pin 2E
  PIN_INPUT_OUTPUT('E',1,"Input");                         //Pin 2E as Input
  PIN_FUNCTION_SELECT('E',1,"Alternative");                //Pin 2E Alternative
  PIN_CONFIGURE('E',1,"ADC");                          //Disable PCTL
  PIN_ANALOG_DIGITAL('E',1,"Analog");                      //Pin 2E Analog
  
  PIN_CONTROL_UNLOCK('E',3);                               //Make Changes To Pin 2E
  PIN_INPUT_OUTPUT('E',3,"Input");                         //Pin 2E as Input
  PIN_FUNCTION_SELECT('E',3,"Alternative");                //Pin 2E Alternative
  PIN_CONFIGURE('E',3,"ADC");                          //Disable PCTL
  PIN_ANALOG_DIGITAL('E',3,"Analog");                      //Pin 2E Analog
}

void ADC_Initialization()
{
  CLK_ADC_Enable(0);
  
  ACTIVE_SAMPLE_SEQUENCER_ENABLE(0,2,"Disable");
  ADC_EMAX_SELECTION(0,2,"Processor");
  ADC_INPUT_CHANNEL(0,2,2);
  ADC_SAMPLES_AVERAGE(0,64);
  ADC_CONTROL_MODE(0,2,"Sequence");
  ADC_CONTROL_MODE(0,2,"Interrupt");
  ACTIVE_SAMPLE_SEQUENCER_ENABLE(0,2,"Enable");
  
  ACTIVE_SAMPLE_SEQUENCER_ENABLE(0,3,"Disable");
  ADC_EMAX_SELECTION(0,3,"Processor");
  ADC_INPUT_CHANNEL(0,3,0);
  ADC_SAMPLES_AVERAGE(0,64);
  ADC_CONTROL_MODE(0,3,"Sequence");
  ADC_CONTROL_MODE(0,3,"Interrupt");
  ACTIVE_SAMPLE_SEQUENCER_ENABLE(0,3,"Enable");
}

float Driver_Angle(void)
{
    //E1_Pin
    ADC_START_CONVERSION(0,2,"Start");                    
    while(ADC_FLAG_READ(0,2)) ;                                            
    voltage = ADC_READ(0,2,0.000805664);                      //E1
    voltage = (voltage*270/3.3)-90;
    ADC_FLAG_CLEAR(0,2);
    //sprintf(text,"Driver_Angle:%0.3f,\n", voltage);
    //printf("%s",text);
    //Delay(2000);
    return voltage;
}

float Vehicle_Angle(void)
{
    //E3_Pin
    ADC_START_CONVERSION(0,3,"Start");                                 
    while(ADC_FLAG_READ(0,3)) ;                                           
    voltage = ADC_READ(0,3,0.000805664);                      //E3
    voltage = (voltage*270/3.3)-133.5;
    ADC_FLAG_CLEAR(0,3);
    //sprintf(text,"Steering_Angle:%0.3f,\n", voltage);
    //printf("%s",text);
    //Delay(2000);
    return voltage;

}

void PortA_Intialization(void)
{
  CLK_Enable('A');
  
  PIN_ANALOG_DIGITAL('A',7,"Digital");
  PIN_ANALOG_DIGITAL('A',6,"Digital");
  
  PIN_FUNCTION_SELECT('A',7,"General I/O");
  PIN_FUNCTION_SELECT('A',6,"General I/O");
  
  PIN_INPUT_OUTPUT('A',7,"Output");
  PIN_INPUT_OUTPUT('A',6,"Output");
}

void PWM_Intialization(void)
{
  CLK_PWM_Enable(0);
  CLK_Enable('B');
  PIN_FUNCTION_SELECT('B',7,"Alternative");
  PIN_CONFIGURE('B',7,"PWM");
  PIN_ANALOG_DIGITAL('B',7,"Digital");
  Use_PWM_Divisor(80,40);
  PWM_Generator_Enable(0,0,"Disable");
  PWM_Action_For_Load(0,0,'B',"LOW");
  PWM_Action_Comparator_Down(0,0,'B',"HIGH");
  PWM_Set_Frequency(0,0,1000,40);
  PWM_Set_Duty_Cycle(0,0,'B',10);
  PWM_Generator_Enable(0,0,"Enable");
  PWM_Module_Start(0);
}

void Delay(unsigned long counter)
{
	unsigned long i = 0;
	
	for(i=0; i< counter*1000; i++);
}