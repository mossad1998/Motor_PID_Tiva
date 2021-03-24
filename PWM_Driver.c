#include "PWM_Driver.h"

volatile uint32_t PWM_Load_Value;
volatile uint32_t* PWM_CTL_R[]={&PWM0_0_CTL_R,&PWM0_1_CTL_R,&PWM0_2_CTL_R,&PWM0_3_CTL_R,      //Array of AFSEL Registers for each port
                              &PWM1_0_CTL_R,&PWM1_1_CTL_R,&PWM1_2_CTL_R,&PWM1_3_CTL_R};

volatile uint32_t* PWM_GENA_R[]={&PWM0_0_GENA_R,&PWM0_1_GENA_R,&PWM0_2_GENA_R,&PWM0_3_GENA_R,              //Array of DIR Registers for each port
                                 &PWM1_0_GENA_R,&PWM1_1_GENA_R,&PWM1_2_GENA_R,&PWM1_3_GENA_R};

volatile uint32_t* PWM_GENB_R[]={&PWM0_0_GENB_R,&PWM0_1_GENB_R,&PWM0_2_GENB_R,&PWM0_3_GENB_R,              //Array of DIR Registers for each port
                                 &PWM1_0_GENB_R,&PWM1_1_GENB_R,&PWM1_2_GENB_R,&PWM1_3_GENB_R};

volatile uint32_t* PWM_Load_R[]={&PWM0_0_LOAD_R,&PWM0_1_LOAD_R,&PWM0_2_LOAD_R,&PWM0_3_LOAD_R,              //Array of DIR Registers for each port
                                 &PWM1_0_LOAD_R,&PWM1_1_LOAD_R,&PWM1_2_LOAD_R,&PWM1_3_LOAD_R};

volatile uint32_t* PWM_CMPB_R[]={&PWM0_0_CMPB_R,&PWM0_1_CMPB_R,&PWM0_2_CMPB_R,&PWM0_3_CMPB_R,              //Array of DIR Registers for each port
                                 &PWM1_0_CMPB_R,&PWM1_1_CMPB_R,&PWM1_2_CMPB_R,&PWM1_3_CMPB_R};

volatile uint32_t* PWM_CMPA_R[]={&PWM0_0_CMPA_R,&PWM0_1_CMPA_R,&PWM0_2_CMPA_R,&PWM0_3_CMPA_R,              //Array of DIR Registers for each port
                                 &PWM1_0_CMPA_R,&PWM1_1_CMPA_R,&PWM1_2_CMPA_R,&PWM1_3_CMPA_R};
                  

void CLK_PWM_Enable(int PWM_module)                                                             //To Eable CLK for specific port
{
  SYSCTL_RCGCPWM_R |= 1UL << PWM_module;    
  volatile uint32_t dummy = SYSCTL_RCGCPWM_R ;                                             
}
void Use_PWM_Divisor(int System_Clock,int PWM_Clock)                                    //To choose digital or analog
{
  SYSCTL_RCC_R |= 0x100000;                                                     //Use PWM divider
  SYSCTL_RCC_R &= ~(0xE0000);                                                   //Clear Divison fields
  uint32_t division = System_Clock/PWM_Clock;
  uint32_t divisor = (int)(log(division)/log(2))-1;
  SYSCTL_RCC_R |= divisor << 17;

}
void PWM_Generator_Enable(int PWM_module,int Generator,char type[10])
{
  int index = Generator +4*PWM_module;
    if(strcmp(type , "Enable")==0)
  {
    *PWM_CTL_R[index] |= 1UL << 0;                                                         //To Enable DEN
  }
  else if (strcmp(type , "Disable")==0)
  {
    *PWM_CTL_R[index] &= ~(1UL << 0);                                                      //To Disable DEN
  }

}
void PWM_Action_For_Load(int PWM_module,int Generator,char Comparator,char type[10])
{
  int index = Generator +4*PWM_module;
  if(Comparator == 'A')
  {
    if(strcmp(type , "HIGH")==0)
    {
      *PWM_GENA_R[index] |= 0x3 << 2;                                                         //To Enable DEN
    }
    else if(strcmp(type , "LOW")==0)
    {
      *PWM_GENA_R[index] |= 0x2 << 2;                                                         //To Enable DEN
    }
  }
  else if(Comparator == 'B')
  {
      if(strcmp(type , "HIGH")==0)
    {
      *PWM_GENB_R[index] |= 0x3 << 2;                                                         //To Enable DEN
    }
    else if(strcmp(type , "LOW")==0)
    {
      *PWM_GENB_R[index] |= 0x2 << 2;                                                         //To Enable DEN
    }
  }
}
void PWM_Action_Comparator_Down(int PWM_module,int Generator,char Comparator,char type[10])
{
  int index = Generator +4*PWM_module;
  if(Comparator == 'A')
  {
    if(strcmp(type , "HIGH")==0)
    {
      *PWM_GENA_R[index] |= 0x3 << 6;                                                         //To Enable DEN
    }
    else if(strcmp(type , "LOW")==0)
    {
      *PWM_GENA_R[index] |= 0x2 << 6;                                                         //To Enable DEN
    }
  }
  else if(Comparator == 'B')
  {
      if(strcmp(type , "HIGH")==0)
    {
      *PWM_GENB_R[index] |= 0x3 << 10;                                                         //To Enable DEN
    }
    else if(strcmp(type , "LOW")==0)
    {
      *PWM_GENB_R[index] |= 0x2 << 10;                                                         //To Enable DEN
    }
  }
}
void PWM_Set_Frequency(int PWM_module,int Generator,int Frequency,int PWM_Clock_MHz)
{
 int period = PWM_Clock_MHz*1000000/Frequency;
 int bits = (int)(log(period)/log(2));
 if (bits >16)
 {
    Debug_Led("Red",1);
    printf("Load Bits is Greater than 16");
 }
 PWM_Load_Value = period;
 int index = Generator +4*PWM_module;
 *PWM_Load_R[index] = period - 1;
}

void PWM_Set_Duty_Cycle(int PWM_module,int Generator,char Comparator,int Duty)
{
 int duty = Duty*PWM_Load_Value/100;
 int bits = (int)(log(duty)/log(2));
 if (bits >16)
 {
    Debug_Led("RED",1);
    printf("Load Bits is Greater than 16");
 }
  int index = Generator +4*PWM_module;
  if(Comparator == 'A')
  {
    *PWM_CMPA_R[index] = duty-1;
  }
  else if(Comparator == 'B')
  {
    *PWM_CMPB_R[index] = duty-1;                                                         //To Enable DEN
                                                                 //To Enable DEN
  }
}
void PWM_Module_Start(int PWM_module)
{
  PWM0_ENABLE_R |= 0x00000002;
}