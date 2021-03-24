#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include <string.h>




#ifndef __Clock_Driver_H__
#define __Clock_Driver_H__


#define CLK_5Mhz        (0x09)
#define CLK_6Mhz        (0x0B)
#define CLK_8Mhz        (0x0E)
#define CLK_10Mhz       (0x10)
#define CLK_12Mhz       (0x11)
#define CLK_16Mhz       (0x15)
#define CLK_18Mhz       (0x17)
#define CLK_20Mhz       (0x18)
#define CLK_24Mhz       (0x19)
#define CLK_25Mhz       (0x1A)


extern void Set_Clock_MHz(int Crystal_Frequency_Mhz, int System_Clock);                                    //Clock for Port



#endif