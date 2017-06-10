// *************************************************************************************************
//  Hardware UART interface
// *************************************************************************************************


// *************************************************************************************************
// Include section

#include "project.h"
#include "RTC.h"
#include "ccxx00.h"


// *************************************************************************************************
// Defines section

// CSN pin to high
//#define CC_CSN_HIGH                    {CC_CSN_OUT |=  CC_CSN_PIN;}
// CSN pin to low
//#define CC_CSN_LOW                     {CC_CSN_OUT &= ~CC_CSN_PIN;}
// Initialize CSN pin
//#define CC_CSN_INIT                    {CC_CSN_DIR |=  CC_CSN_PIN;}

// SDI pin level read out
//#define SDI_LEVEL                      (CC_SDI_IN & CC_SDI_PIN)


// *************************************************************************************************
// Function prototype section


// *************************************************************************************************
// Implementation

void RTC_Init_v(void)
{


	RTCCTL01 |= RTCBCD + RTCHOLD + RTCMODE;
	                                            // RTC enable, BCD mode, RTC hold
	                                            // enable RTC read ready interrupt
	                                            // enable RTC time event interrupt

	RTCDAY = 0x08;
	RTCMON = 0x05;
	RTCYEARH = 0x20;
	RTCYEARL = 0x17;
	RTCHOUR = 0x06;
	RTCMIN = 0x06;
	RTCSEC = 0x06;
	RTCDOW = 0x01;

	RTCCTL01 &= ~(RTCHOLD);
}
