#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include <string.h>
#include <math.h>




#ifndef __ADC_Driver_H__
#define __ADC_Driver_H__


extern void CLK_ADC_Enable(int ADC_module);                                         //Clock for Port
extern void ACTIVE_SAMPLE_SEQUENCER_ENABLE(int ADC_module,int sequencer_module,char type[10]);           //Enable or Disable Analog and Digital
extern void ADC_EMAX_SELECTION(int ADC_module,int sequencer_module,char type[10]);          //General i/o or Alternative Function
extern void ADC_INPUT_CHANNEL(int ADC_module,int sequencer_module,int channel);             //Input or Output
extern void ADC_CONTROL_MODE(int ADC_module,int sequencer_module,char type[10]);          //Pullup or Pulldown

extern void ADC_START_CONVERSION(int ADC_module,int sequencer_module,char type[10]);          //Pullup or Pulldown
extern void ADC_SAMPLES_AVERAGE(int ADC_module,int number_samples);                             //Pullup or Pulldown
extern float ADC_READ(int ADC_module,int sequencer_module, float factor);             //To Write Data
extern bool ADC_FLAG_READ(int ADC_module,int sequencer_module);                           //To Read Data
extern void ADC_FLAG_CLEAR(int ADC_module,int sequencer_module);                           //To Read Data


#endif