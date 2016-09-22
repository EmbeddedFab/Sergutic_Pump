#ifndef _EF_MPX_H_
#define _EF_MPX_H_

#include "../ServiceLayer/std_types.h"


enum {
    MPX_PUMP
}TypeMPX_AdcEnums;

/*********************************************************************
* Function    : EF_void_MPX_init( U8_t MPX_Number);
*
* DESCRIPTION : this function is used to init ADC module to use it with MPX
*
* PARAMETERS  : MPX_Number: define which MPX used (MPX_MAIN or MPX_SECOND) to
*               change the corresponding ADC channl for it
*
* Return Value: None
***********************************************************************/
void  EF_void_MPX_init();

/*********************************************************************
* Function    : EF_float_MPX_GetPressure_mmHg ( U8_t MPX_Number);
*
* DESCRIPTION : this function is used to convert the analog Voltage Value from
*               MPX to Pressure Value in mmHg

* PARAMETERS  : MPX_Number: define which MPX used (MPX_MAIN or MPX_SECOND) to
*               change the corresponding ADC channl for it
*
* Return Value: return pressure value from Mpx in mmHg
***********************************************************************/
float EF_float_MPX_GetPressure_mmHg ();


#endif


