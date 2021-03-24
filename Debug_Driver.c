#include "Debug_Driver.h"
                
void Debug_Led(char color[10],bool state)
{
	if(strcmp(color ,"Red")==0)
	{
		if(state == 1)
			PIN_WRITE_DIGITAL('F',1,"HIGH");
		else
			PIN_WRITE_DIGITAL('F',1,"LOW");
	}
	
		else if(strcmp(color ,"Blue")==0)
	{
		if(state == 1)
			PIN_WRITE_DIGITAL('F',2,"HIGH");
		else
			PIN_WRITE_DIGITAL('F',2,"LOW");
	}
	
			else if(strcmp(color ,"Green")==0)
	{
		if(state == 1)
			PIN_WRITE_DIGITAL('F',3,"HIGH");
		else
			PIN_WRITE_DIGITAL('F',3,"LOW");
	}

}
void Debug_Intialization(void)
{
  CLK_Enable('F');
  GPIO_PORT_UNLOCK('F');
        
  PIN_ANALOG_DIGITAL('F',1,"Digital");
  PIN_FUNCTION_SELECT('F',1,"General I/O");
  PIN_INPUT_OUTPUT('F',1,"Output");
        
  PIN_ANALOG_DIGITAL('F',2,"Digital");
  PIN_FUNCTION_SELECT('F',2,"General I/O");
  PIN_INPUT_OUTPUT('F',2,"Output");
	
  PIN_ANALOG_DIGITAL('F',3,"Digital");
  PIN_FUNCTION_SELECT('F',3,"General I/O");
  PIN_INPUT_OUTPUT('F',3,"Output");
  
  Debug_Led("Red",0);
  Debug_Led("Blue",0);
  Debug_Led("Green",0);
}