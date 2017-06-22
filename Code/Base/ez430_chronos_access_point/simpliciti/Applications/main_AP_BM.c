/**********************************************************************************************
  Copyright 2004-2007 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights granted under
  the terms of a software license agreement between the user who downloaded the software,
  his/her employer (which must be your employer) and Texas Instruments Incorporated (the
  "License"). You may not use this Software unless you agree to abide by the terms of the
  License. The License limits your use, and you acknowledge, that the Software may not be
  modified, copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio frequency
  transceiver, which is integrated into your product. Other than for the foregoing purpose,
  you may not use, reproduce, copy, prepare derivative works of, modify, distribute,
  perform, display or sell this Software and/or its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS”
  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY
  WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
  IN NO EVENT SHALL TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE
  THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY
  INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST
  DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY
  THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/


// *************************************************************************************************
// Include section
#include <string.h>
#include "bsp.h"
#include "mrfi.h"
#include "bsp_leds.h"
//#include "bsp_buttons.h"
#include "nwk_types.h"
#include "nwk_api.h"
#include "nwk_frame.h"
#include "nwk.h"
#include "simpliciti.h"
#include "project.h"
#include "UART.h"
#include <time.h>


// *************************************************************************************************
// Defines section
#define BIT0                   (0x0001)
#define BIT1                   (0x0002)
#define BIT2                   (0x0004)
#define BIT3                   (0x0008)
#define BIT4                   (0x0010)
#define BIT5                   (0x0020)
#define BIT6                   (0x0040)
#define BIT7                   (0x0080)
#define BIT8                   (0x0100)
#define BIT9                   (0x0200)
#define BITA                   (0x0400)
#define BITB                   (0x0800)
#define BITC                   (0x1000)
#define BITD                   (0x2000)
#define BITE                   (0x4000)
#define BITF                   (0x8000)

/* SmartCare related defines */
#define NO_ALARM		0x00
#define FALL			0x01
#define HEARTRATE		0x02
#define EMERGENCY		0x04
#define MEDICINE		0x08
#define NO_COMMS		0x10
#define LOW_BATT		0x20

#define NO_CMD			0x00
#define CMD_STATUS		0x01
#define CMD_DATE		0x02
#define CMD_TIME		0x04
#define CMD_MEDICINE	0x08

// *************************************************************************************************
// Prototypes section

/* callback handler */
uint8_t sCB(linkID_t);


// *************************************************************************************************
// Extern section
extern uint8_t sInit_done;


// *************************************************************************************************
// Global Variable section

/* reserve space for the maximum possible peer Link IDs */
static linkID_t linkID0;
static uint8_t  sNumCurrentPeers = 0;

/* work loop semaphores */
static volatile uint8_t sPeerFrameSem = 0;
static volatile uint8_t sJoinSem = 0;

volatile unsigned char simpliciti_flag;
unsigned char simpliciti_data[SIMPLICITI_MAX_PAYLOAD_LENGTH];
unsigned char ed_data[SIMPLICITI_MAX_PAYLOAD_LENGTH];

/* SmartCare related variables */
u8 status_code = NO_ALARM;
u8 newDataFlag = 0;
u8 DateTimeChangedFlag = 0;
u8 MedicineChangedFlag = 0;
u8 AlarmChangedFlag = 0;

u8 t_batt[3];
u8 t_signal[3];
u8 t_temperature[3];
u8 t_heart[3];
u8 t_day[2];
u8 t_month[2];
u8 t_year[4];
u8 t_hour[2];
u8 t_minute[2];
u8 t_second[2];
u8 t_dow[2];

u8 watch_day[2];
u8 watch_month[2];
u8 watch_year[4];
u8 watch_hour[2];
u8 watch_minute[2];
u8 watch_second[2];
u8 watch_dow[2];

u8 t_medhour[25];

u8 stringBuffer[50];

// AP main routine
void simpliciti_main(void)
{
  bspIState_t intState;
  uint8_t j;
  uint8_t len;
  uint32_t led_toggle = 0;
  uint8_t   pwr;
  uint8_t temp = 0;
  uint16_t temp16 = 0;

  // Init variables
  simpliciti_flag = SIMPLICITI_STATUS_LINKING;

  // Initialize Timer A1
  BSP_Init();

  // Init SimpliciTI
  SMPL_Init(sCB);

  // Set output power to +1.1dBm (868MHz) / +1.3dBm (915MHz)
  pwr = IOCTL_LEVEL_2;
  SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SETPWR, &pwr);

   // LED off
  BSP_TURN_OFF_LED1();

  uint8_t cmdBuffer[50];

  uint8_t recvBuffer[50];

  t_batt[0] = '0';
  t_batt[1] = '9';
  t_batt[2] = '1';
  t_signal[0] = '0';
  t_signal[1] = '9';
  t_signal[2] = '2';
  t_temperature[0] = '0';
  t_temperature[1] = '1';
  t_temperature[2] = '8';
  t_heart[0] = '0';
  t_heart[1] = '6';
  t_heart[2] = '6';

  status_code = 0;

  t_day[0] = 0x30 + ((RTCDAY & 0xF0) >> 4);
  t_day[1] = 0x30 + (RTCDAY & 0x0F);

  t_month[0] = 0x30 + ((RTCMON & 0xF0) >> 4);
  t_month[1] = 0x30 + (RTCMON & 0x0F);

  t_year[0] = 0x32;
  t_year[1] = 0x30;
  t_year[2] = 0x30 + ((RTCYEARL & 0xF0) >> 4);
  t_year[3] = 0x30 + (RTCYEARL & 0x0F);

  t_hour[0] = 0x30 + ((RTCHOUR & 0xF0) >> 4);
  t_hour[1] = 0x30 + (RTCHOUR & 0x0F);

  t_minute[0] = 0x30 + ((RTCMIN & 0xF0) >> 4);
  t_minute[1] = 0x30 + (RTCMIN & 0x0F);

  t_second[0] = 0x30 + ((RTCSEC & 0xF0) >> 4);
  t_second[1] = 0x30 + (RTCSEC & 0x0F);

  t_dow[0] = 0x30;
  t_dow[1] = RTCDOW + 0x30;

  newDataFlag = 0;

  /* main work loop */
  while (1)
  {
    // Wait for the Join semaphore to be set by the receipt of a Join frame from a
    //device that supports an End Device.
    if (sJoinSem && !sNumCurrentPeers)
    {
      /* listen for a new connection */
      while (1)
      {
        if (SMPL_SUCCESS == SMPL_LinkListen(&linkID0))
        {
          // We have a connection
          simpliciti_flag = SIMPLICITI_STATUS_LINKED;
          BSP_TURN_ON_LED1();
          break;
        }
        //BSP_TOGGLE_LED1();
      }

      sNumCurrentPeers++;

      BSP_ENTER_CRITICAL_SECTION(intState);
      sJoinSem--;
      BSP_EXIT_CRITICAL_SECTION(intState);
    }

    /* Have we received a frame on one of the ED connections?
     * No critical section -- it doesn't really matter much if we miss a poll
     */
    if (sPeerFrameSem)
    {
      // Continuously try to receive end device packets
      if (SMPL_SUCCESS == SMPL_Receive(linkID0, ed_data, &len))
      {
    	  simpliciti_data[0] = SYNC_AP_CMD_NOP;
        {
          // Indicate received packet
          //BSP_TOGGLE_LED1();

          // Decode end device packet
          switch (ed_data[0])
          {
              case SYNC_ED_TYPE_R2R:
            	  BSP_TOGGLE_LED1();
                                    // Send reply
                                    if (getFlag(simpliciti_flag, SIMPLICITI_TRIGGER_SEND_CMD))
                                    {
                                      // Clear flag
                                      clearFlag(simpliciti_flag, SIMPLICITI_TRIGGER_SEND_CMD);
                                      // Command data was set by USB buffer previously
                                      len = BM_SYNC_DATA_LENGTH;
                                    }
                                    else // No command currently available
                                    {
                                      simpliciti_data[0] = SYNC_AP_CMD_NOP;
                                      simpliciti_data[1] = 0x55;
                                      len = 2;
                                    }

                                    // Send reply packet to end device
                                    SMPL_Send(linkID0, simpliciti_data, len);
                                    break;

            case SYNC_ED_TYPE_MEMORY:
            case SYNC_ED_TYPE_STATUS:
                                    // If buffer is empty, copy received end device data to intermediate buffer
                                    if (!simpliciti_sync_buffer_status)
                                    {
                                      for (j=0; j<BM_SYNC_DATA_LENGTH; j++) simpliciti_data[j] = ed_data[j];
                                      simpliciti_sync_buffer_status = 1;
                                    }
                                    // Set buffer status to full
                                    break;

            case 'R':
            	BSP_TOGGLE_LED1();

            					temp = ed_data[1];

            					t_batt[0] = (temp / 100) + 0x30;
            					temp = temp % 100;
            					t_batt[1] = (temp / 10) + 0x30;
            					temp = temp % 10;
            					t_batt[2] = temp + 0x30;

            					temp = ed_data[2];

            					t_signal[0] = (temp / 100) + 0x30;
								temp = temp % 100;
								t_signal[1] = (temp / 10) + 0x30;
								temp = temp % 10;
								t_signal[2] = temp + 0x30;

								temp = ed_data[3];

								t_temperature[0] = (temp / 100) + 0x30;
								temp = temp % 100;
								t_temperature[1] = (temp / 10) + 0x30;
								temp = temp % 10;
								t_temperature[2] = temp + 0x30;

								temp = ed_data[4];

								t_heart[0] = (temp / 100) + 0x30;
								temp = temp % 100;
								t_heart[1] = (temp / 10) + 0x30;
								temp = temp % 10;
								t_heart[2] = temp + 0x30;

            					status_code = ed_data[5];

            					newDataFlag = 1;

            					if (AlarmChangedFlag != 0)
            					{
            						simpliciti_data[0] = 'R';
            						simpliciti_data[1] = 0x40;
            						simpliciti_data[2] = 0x0D;
            						status_code = 0;
            						AlarmChangedFlag = 0;
            					}
            					else
            					{
            						simpliciti_data[0] = 'R';
            						simpliciti_data[1] = 0x00;
            						simpliciti_data[2] = 0x0D;
            					}

            					len = 3;
            					SMPL_Send(linkID0, simpliciti_data, len);

            					break;

			case 'D':

				BSP_TOGGLE_LED1();
				newDataFlag++;
				if (DateTimeChangedFlag == 1)
				{
					simpliciti_data[0] = 'D';
					simpliciti_data[1] = (RTCDAY & 0x0F) + 10*((RTCDAY & 0xF0) >> 4);
					simpliciti_data[2] = (RTCMON & 0x0F) + 10*((RTCMON & 0xF0) >> 4);
					temp16 = ((RTCYEARH & 0xF0) >> 4) * 1000 + (RTCYEARH & 0x0F) * 100 + ((RTCYEARL & 0xF0) >> 4) * 10 + (RTCYEARL & 0x0F);
					simpliciti_data[3] = (uint8_t) (temp16 & 0x00FF);
					simpliciti_data[4] = (uint8_t) ((temp16 & 0xFF00) >> 8);
					simpliciti_data[5] = (RTCHOUR & 0x0F) + 10*((RTCHOUR & 0xF0) >> 4);
					simpliciti_data[6] = (RTCMIN & 0x0F) + 10*((RTCMIN & 0xF0) >> 4);
					simpliciti_data[7] = (RTCSEC & 0x0F) + 10*((RTCSEC & 0xF0) >> 4);
					simpliciti_data[8] = RTCDOW;
					simpliciti_data[9] = 0x0D;

					len = 10;
					SMPL_Send(linkID0, simpliciti_data, len);

					DateTimeChangedFlag = 0;
				}
				else
				{
					RTCHOUR = (0xF0 & ((ed_data[5]/10) << 4)) | (0x0F & (ed_data[5]%10));
					RTCMIN = (0xF0 & ((ed_data[6]/10) << 4)) | (0x0F & (ed_data[6]%10));
					RTCSEC = (0xF0 & ((ed_data[7]/10) << 4)) | (0x0F & (ed_data[7]%10));
					RTCDAY = (0xF0 & ((ed_data[1]/10) << 4)) | (0x0F & (ed_data[1]%10));
					RTCMON = (0xF0 & ((ed_data[2]/10) << 4)) | (0x0F & (ed_data[2]%10));
					temp16 = ed_data[4]*256 + ed_data[3];
					temp = temp16/100;
					RTCYEARH = (0xF0 & ((temp/10) << 4)) | (0x0F & (temp%10));
					temp = temp16%100;
					RTCYEARL = (0xF0 & ((temp/10) << 4)) | (0x0F & (temp%10));

					RTCDOW = ed_data[8];

					simpliciti_data[0] ='D';

					simpliciti_data[1] = 0x0D;

					len = 2;
					SMPL_Send(linkID0, simpliciti_data, len);
				}


            	break;
			case 'H':

				BSP_TOGGLE_LED1();

            					if (MedicineChangedFlag == 1)
            					{
            						u8 i = 0;
            						for (i = 0; i < 18; i++)
            						{
            							simpliciti_data[i] = t_medhour[i];
            						}

            						len = 18;
            						SMPL_Send(linkID0, simpliciti_data, len);

            						MedicineChangedFlag = 0;
            					}
            					else
            					{
            						simpliciti_data[0] ='H';

									simpliciti_data[1] = 0x0D;

									len = 2;
									SMPL_Send(linkID0, simpliciti_data, len);
            					}
            					break;

          }
        }
      }

		if (UART_recv_async(recvBuffer))
		{
			if (recvBuffer[0] == 'R')	// ler dados
			{
				if (newDataFlag == 2)
				{

					t_day[0] = 0x30 + ((RTCDAY & 0xF0) >> 4);
					t_day[1] = 0x30 + (RTCDAY & 0x0F);

					t_month[0] = 0x30 + ((RTCMON & 0xF0) >> 4);
					t_month[1] = 0x30 + (RTCMON & 0x0F);

					t_year[0] = 0x32;
					t_year[1] = 0x30;
					t_year[2] = 0x30 + ((RTCYEARL & 0xF0) >> 4);
					t_year[3] = 0x30 + (RTCYEARL & 0x0F);

					t_hour[0] = 0x30 + ((RTCHOUR & 0xF0) >> 4);
					t_hour[1] = 0x30 + (RTCHOUR & 0x0F);

					t_minute[0] = 0x30 + ((RTCMIN & 0xF0) >> 4);
					t_minute[1] = 0x30 + (RTCMIN & 0x0F);

					t_second[0] = 0x30 + ((RTCSEC & 0xF0) >> 4);
					t_second[1] = 0x30 + (RTCSEC & 0x0F);

					t_dow[0] = 0x30;
					t_dow[1] = RTCDOW + 0x30;

					  cmdBuffer[0] = 'R';

					  cmdBuffer[1] = t_batt[0];
					  cmdBuffer[2] = t_batt[1];
					  cmdBuffer[3] = t_batt[2];

					  cmdBuffer[4] = ',';

					  cmdBuffer[5] = t_signal[0];
					  cmdBuffer[6] = t_signal[1];
					  cmdBuffer[7] = t_signal[2];

					  cmdBuffer[8] = ',';

					  cmdBuffer[9] = t_temperature[0];
					  cmdBuffer[10] = t_temperature[1];
					  cmdBuffer[11] = t_temperature[2];

					  cmdBuffer[12] = ',';

					  cmdBuffer[13] = t_heart[0];
					  cmdBuffer[14] = t_heart[1];
					  cmdBuffer[15] = t_heart[2];

					  cmdBuffer[16] = ',';

					  cmdBuffer[17] = ((status_code>>4) & 0x0F) + 0x30;
					  cmdBuffer[18] = (status_code & 0x0F) + 0x30;

					  cmdBuffer[19] = ',';

					  cmdBuffer[20] = t_day[0];
					  cmdBuffer[21] = t_day[1];

					  cmdBuffer[22] = ',';

					  cmdBuffer[23] = t_month[0];
					  cmdBuffer[24] = t_month[1];

					  cmdBuffer[25] = ',';

					  cmdBuffer[26] = t_year[0];
					  cmdBuffer[27] = t_year[1];
					  cmdBuffer[28] = t_year[2];
					  cmdBuffer[29] = t_year[3];

					  cmdBuffer[30] = ',';

					  cmdBuffer[31] = t_hour[0];
					  cmdBuffer[32] = t_hour[1];

					  cmdBuffer[33] = ',';

					  cmdBuffer[34] = t_minute[0];
					  cmdBuffer[35] = t_minute[1];

					  cmdBuffer[36] = ',';

					  cmdBuffer[37] = t_second[0];
					  cmdBuffer[38] = t_second[1];

					  cmdBuffer[39] = ',';

					  cmdBuffer[40] = t_dow[0];
					  cmdBuffer[41] = t_dow[1];

					  cmdBuffer[42] = 0x0D;

					  newDataFlag = 0;
				  }
				  else
				  {
					  cmdBuffer[0] = 'E';
					  cmdBuffer[1] = 0x0D;
				  }
				  UART_send_async(cmdBuffer);
			  }
			  else if (recvBuffer[0] == 'D') // programar data
			  {
				  t_day[0] = recvBuffer[1];
				  t_day[1] = recvBuffer[2];

				  t_month[0] = recvBuffer[4];
				  t_month[1] = recvBuffer[5];

				  t_year[0] = recvBuffer[7];
				  t_year[1] = recvBuffer[8];
				  t_year[2] = recvBuffer[9];
				  t_year[3] = recvBuffer[10];

				  t_hour[0] = recvBuffer[12];
				  t_hour[1] = recvBuffer[13];

				  t_minute[0] = recvBuffer[15];
				  t_minute[1] = recvBuffer[16];

				  t_second[0] = recvBuffer[18];
				  t_second[1] = recvBuffer[19];

				  t_dow[0] = recvBuffer[21];
				  t_dow[1] = recvBuffer[22];

					RTCDAY = ((t_day[0]-0x30) << 4) | (t_day[1] - 0x30);
					RTCMON = ((t_month[0]-0x30) << 4) | (t_month[1] - 0x30);
					RTCYEARH = ((t_year[0]-0x30) << 4) | (t_year[1] - 0x30);
					RTCYEARL = ((t_year[2]-0x30) << 4) | (t_year[3] - 0x30);
					RTCHOUR = ((t_hour[0]-0x30) << 4) | (t_hour[1] - 0x30);
					RTCMIN = ((t_minute[0]-0x30) << 4) | (t_minute[1] - 0x30);
					RTCSEC = ((t_second[0]-0x30) << 4) | (t_second[1] - 0x30);
					RTCDOW = ((t_dow[0]-0x30) << 4) | (t_dow[1] - 0x30);

				  cmdBuffer[0] = 'D';
				  cmdBuffer[1] = 0x0D;

				  UART_send_async(cmdBuffer);

				  DateTimeChangedFlag = 1;
			  }
			  else if (recvBuffer[0] == 'H') // programar hora remedio
			  {
				  t_medhour[0] = 'H';

				  if (recvBuffer[1] != '-')
				  {
					  t_medhour[1] = (recvBuffer[1]-0x30)*10 + (recvBuffer[2]-0x30);
					  t_medhour[2] = (recvBuffer[4]-0x30)*10 + (recvBuffer[5]-0x30);
				  }
				  else
				  {
					  t_medhour[1] = 99;
					  t_medhour[2] = 99;
				  }

				  if (recvBuffer[7] != '-')
				  {
					  t_medhour[3] = (recvBuffer[7]-0x30)*10 + (recvBuffer[8]-0x30);
					  t_medhour[4] = (recvBuffer[10]-0x30)*10 + (recvBuffer[11]-0x30);
				  }
				  else
				  {
					  t_medhour[3] = 99;
					  t_medhour[4] = 99;
				  }

				  if (recvBuffer[13] != '-')
				  {
					  t_medhour[5] = (recvBuffer[13]-0x30)*10 + (recvBuffer[14]-0x30);
					  t_medhour[6] = (recvBuffer[16]-0x30)*10 + (recvBuffer[17]-0x30);
				  }
				  else
				  {
					  t_medhour[5] = 99;
					  t_medhour[6] = 99;
				  }

				  if (recvBuffer[19] != '-')
				  {
					  t_medhour[7] = (recvBuffer[19]-0x30)*10 + (recvBuffer[20]-0x30);
					  t_medhour[8] = (recvBuffer[22]-0x30)*10 + (recvBuffer[23]-0x30);
				  }
				  else
				  {
					  t_medhour[7] = 99;
					  t_medhour[8] = 99;
				  }

				  if (recvBuffer[25] != '-')
				  {
					  t_medhour[9] = (recvBuffer[25]-0x30)*10 + (recvBuffer[26]-0x30);
					  t_medhour[10] = (recvBuffer[28]-0x30)*10 + (recvBuffer[29]-0x30);
				  }
				  else
				  {
					  t_medhour[9] = 99;
					  t_medhour[10] = 99;
				  }

				  if (recvBuffer[31] != '-')
				  {
					  t_medhour[11] = (recvBuffer[31]-0x30)*10 + (recvBuffer[32]-0x30);
					  t_medhour[12] = (recvBuffer[34]-0x30)*10 + (recvBuffer[35]-0x30);
				  }
				  else
				  {
					  t_medhour[11] = 99;
					  t_medhour[12] = 99;
				  }

				  if (recvBuffer[37] != '-')
				  {
					  t_medhour[13] = (recvBuffer[37]-0x30)*10 + (recvBuffer[38]-0x30);
					  t_medhour[14] = (recvBuffer[40]-0x30)*10 + (recvBuffer[41]-0x30);
				  }
				  else
				  {
					  t_medhour[13] = 99;
					  t_medhour[14] = 99;
				  }

				  if (recvBuffer[43] != '-')
				  {
					  t_medhour[15] = (recvBuffer[43]-0x30)*10 + (recvBuffer[44]-0x30);
					  t_medhour[16] = (recvBuffer[46]-0x30)*10 + (recvBuffer[47]-0x30);
				  }
				  else
				  {
					  t_medhour[15] = 99;
					  t_medhour[16] = 99;
				  }
				  t_medhour[17] = 0x0D;

				  cmdBuffer[0] = 'H';
				  cmdBuffer[1] = 0x0D;

				  UART_send_async(cmdBuffer);

				  MedicineChangedFlag = 1;
			  }
			  else if (recvBuffer[0] == 'C')	// limpar alarme
			  {
				  AlarmChangedFlag = 1;
			  }
		  }

    }

    // Exit function if SIMPLICITI_TRIGGER_STOP flag bit is set in USB driver
    if (getFlag(simpliciti_flag, SIMPLICITI_TRIGGER_STOP))
    {
      // Clean up after SimpliciTI and enable restarting the stack
      MRFI_RxIdle();
      linkID0 = 0;
      sNumCurrentPeers = 0;
      sJoinSem = 0;
      sPeerFrameSem = 0;
      sInit_done = 0;
      // LED off
      BSP_TURN_OFF_LED1();
      return;
    }

    // Blink slowly to indicate that access point is on
    if (!sNumCurrentPeers)
    {
      if (led_toggle++>150000)
      {
        //BSP_TOGGLE_LED1();
        led_toggle = 0;
      }
    }
  }
}

/* Runs in ISR context. Reading the frame should be done in the */
/* application thread not in the ISR thread. */
uint8_t sCB(linkID_t lid)
{
  if (lid)
  {
    sPeerFrameSem++;
  }
  else
  {
    sJoinSem++;
  }

  /* leave frame to be read by application. */
  return 0;
}
