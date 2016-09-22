/*
 * main.c
 *
 *  Created on: 2 Dec 2015
 *      Author: EmbeddedFab
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>


#include "MCAL/EF_SpechialTimer.h"
#include "HAL/EF_MPX.h"
#include "MCAL/EF_UART.h"
#include "MCAL/EF_DIO.h"
#include "ServiceLayer/std_types.h"
#include "MCAL/EF_ADC.h"
#include "MCAL/EF_PWM.h"

#define PUMP_PORT       'd'
#define PUMP_PIN         6
int main(void)
{
    volatile double pressure_Pump = 0;
    volatile U8_t   PumpDuty	  = 10 ;

    PumpDuty = 50;
    _delay_ms(3000);

    EF_void_MPX_init();

    EF_void_TimerInit();
    /* pin for Driver to pump as Mpl */
    EF_void_PWM_init (TIMER_0);
    static UART_cfg_str  uart_cfg = {9600, 8, ONE_STOP_BIT, NO_PARITY, FALSE, FALSE, TRUE, TRUE};
    EF_void_UART_Init(&uart_cfg);
	EF_void_TimerCreate ( TEN_mSECOND_TIMER_ID , 10);



    while (1)
    {
    	pressure_Pump =  EF_float_MPX_GetPressure_mmHg ();

    	//    	EF_void_UART_SendArray((U8_t*)"Pump: ", sizeof("Pump: "));
    	EF_void_UART_Send_Integer ( (U16_t)pressure_Pump);
    	EF_void_UART_SendArray((U8_t*)"\r\n", sizeof("\r\n"));

		EF_S8_DIO_ClearPin ( PUMP_PORT, PUMP_PIN );

    	if ( pressure_Pump < 600 )
    	{
    		EF_void_TimerStart ( TEN_mSECOND_TIMER_ID );
    		PumpDuty = 2;

    		while ( pressure_Pump < 600 )
    		{
    			/**********************************************/
    			EF_S8_DIO_SetPin ( PUMP_PORT , PUMP_PIN );
    			_delay_ms (PumpDuty);
    			EF_S8_DIO_ClearPin ( PUMP_PORT, PUMP_PIN );
    			_delay_ms ( 20 - PumpDuty);
    			/**********************************************/

    			if ( EF_BOOLEAN_TimerCheck(TEN_mSECOND_TIMER_ID))
    			{
    				if (PumpDuty <= 10)
    				{
    					PumpDuty = PumpDuty + 2;
    				}

    				EF_void_TimerStop(TEN_mSECOND_TIMER_ID);
    				EF_void_TimerReset(TEN_mSECOND_TIMER_ID);
        	    	EF_void_UART_SendArray((U8_t*)"timr\r\n", sizeof("timr\r\n"));
    				EF_void_TimerStart ( TEN_mSECOND_TIMER_ID );
    			}

    			pressure_Pump =  EF_float_MPX_GetPressure_mmHg ();
    	    	EF_void_UART_Send_Integer ( (U16_t)pressure_Pump);
    	    	EF_void_UART_SendArray((U8_t*)"\r\n", sizeof("\r\n"));
    		}

    	}

    }


}


