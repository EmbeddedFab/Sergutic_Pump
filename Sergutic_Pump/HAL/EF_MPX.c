

#include "EF_MPX.h"
#include "../ServiceLayer/std_types.h"
#include "../MCAL/EF_ADC.h"
#include "../MCAL/EF_DIO.h"



/* Pump MPX connected to (AIN1)Analag channel 1 which it's output on PE2 pin */
#define MPX_ADC_CHANNEL       0
#define MPX_PUMP_ADC_NUMBER   1       /* PE2 for AIN1 */


#define MAX_LEVELS              1024    /* Max Levels of ADC Voltage Levels = 12^(12bit) */
#define V_REF_VALUE             4.7     /* Vreference which ADC module was Connected to it Internally */
#define V_MPX_SOURCE            4.7       /* Vsource for the MPX Module */

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
void EF_void_MPX_init()
{
	EF_void_ADC_init ();

}



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
float EF_float_MPX_GetPressure_mmHg ()
{
    U16_t ADCdata = 0;
    double floatADCdata = 0;         /* Variable to get Analog Value */
    double floatPressure_kpa  = 0;   /* Converted Pressure in Kpa */
    double floatPressure_mBar = 0;   /* Converted Pressure in mili Bar */
    double floatPressure_mmHg = 0;   /* Converted Pressure in milimeter Hg */


    EF_void_ADC_init ();
//todo remove comment
    ADCdata = EF_u16_ADC_read (MPX_ADC_CHANNEL);



   /* P(kpa) = ((Vadc/Vs) - 0,04)/.009
    * if Vadc is volt ,so Vs will be 5v(connected to Mpx)
    * else if (Vadc is ratio) ,Vs will be the max of Number Level (here: 2^(12)=4096 )
    * P = ((Vadc/Vs) - 0,04)/.009  =  ((Vadc/4096) - 0,04)/.009 */
    floatADCdata = ((double)ADCdata * V_REF_VALUE)/MAX_LEVELS;

    //todo : remove
    floatPressure_kpa =  ( ((double)floatADCdata / V_MPX_SOURCE) - 0.04 ) * (1/0.009);  //(1kpa*10 = 1mbar )

    /* not to return negative values */
    if (floatPressure_kpa > 0)
    {
        /* 1 kPa = 10 mbar*/
        floatPressure_mBar  = floatPressure_kpa * 10;
        /* 1 mbar = 0.75006375541921 mmHg */
        floatPressure_mmHg  = floatPressure_mBar * 0.75 ;
    }
    else
    {
        floatPressure_mmHg = 0;
    }

    return floatPressure_mmHg;

}




