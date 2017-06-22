// *************************************************************************************************
//  Hardware UART interface
// *************************************************************************************************


// *************************************************************************************************
// Include section

#include "project.h"
#include "UART.h"
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

u8 rxBuffer[50];
u8 txBuffer[50];

volatile u8 rxCompleteFlag = 0;
volatile u8 txCompleteFlag = 1;

u8 txIdx = 0;
u8 rxIdx = 0;

u8 intBuffer = 0;
// *************************************************************************************************
// Setup UART pins.
// *************************************************************************************************
void UART_Init_v(void)
{
  UART_CTL1 |= UCSWRST;
  UART_CTL1 |= UCSSEL1;
  UART_BR0 = 104;						// BR 9600
  UART_BR1 = 0;
  UART_MCTL = 0x31;
  UART_CTL1 &= ~UCSWRST;              // Start UART hardware
  UCA1IFG = 0;

  UCA1IE = 0x3;
  // Pins to UART function
  UART_TXD_SEL |= UART_TXD_PIN;
  UART_RXD_SEL |= UART_RXD_PIN;
  UART_TXD_DIR |= UART_TXD_PIN;
  __enable_interrupt();
}


// *************************************************************************************************
// Send command byte array async. Will wait until last transmission is done
// *************************************************************************************************
void UART_send_async(u8 *pData_u8)
{
	while(!txCompleteFlag);

	// copy command
	while((*pData_u8) != 0x0D)
	{
		txBuffer[txIdx] = (*pData_u8);
		txIdx++; pData_u8++;
	}

	// copy 0x0D into last position
	txBuffer[txIdx] = (*pData_u8);

	// start transmission
	txIdx = 0;
	txCompleteFlag = 0;
	UART_TX_BUFFER = txBuffer[0];
}

// *************************************************************************************************
// Receive data Async. If available, will copy the RX buffer to buffer parameter
// *************************************************************************************************
u8 UART_recv_async(u8 *buffer)
{
	if (rxCompleteFlag)
	{
		while (rxBuffer[rxIdx] != 0x0D)
		{
			(*buffer) = rxBuffer[rxIdx];
			buffer++; rxIdx++;
		}

		(*buffer) = 0x0D;

		rxCompleteFlag = 0;
		rxIdx = 0;

		return 1;
	}
	return 0;
}

#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
    switch(__even_in_range(UCA1IV,4))
    {
    case 0:     // Vector 0 - no interrupt
        break;

    case 2:     // Vector 2 - RX data
    	if (rxCompleteFlag == 0)
		{
			rxBuffer[rxIdx] = UART_RX_BUFFER;

			if (rxBuffer[rxIdx] == 0x0D)
			{
				rxCompleteFlag = 1;
				rxIdx = 0;
			}
			else
			{
				rxCompleteFlag = 0;
				rxIdx++;
			}
		}
    	break;

    case 4:     // Vector 4 - TX buffer empty
    	if (txCompleteFlag == 0)
		{
			if (txBuffer[txIdx] == 0x0D)
			{
				txCompleteFlag = 1;
				txIdx = 0;
			}
			else
			{
				txCompleteFlag = 0;
				txIdx++;
				UART_TX_BUFFER = txBuffer[txIdx];
			}
		}

        break;

    default:
        break;
    }
}

/*
 * ======== UNMI_ISR ========
 */
/*#pragma vector = USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
	if (UCA0IFG & UCTXIFG)
	{
		// handle TX logic
		if (txCompleteFlag == 0)
		{
			UART_TX_BUFFER = txBuffer[txIdx];

			if (txBuffer[txIdx] == 0x0D)
			{
				txCompleteFlag = 1;
				txIdx = 0;
			}
			else
			{
				txCompleteFlag = 0;
				txIdx++;
			}
		}
		// clear interrupt flag
		UCA0IFG &= ~(UCTXIFG);
	}

	if (UCA0IFG & UCRXIFG)
	{
		//handle RX logic
		if (rxCompleteFlag == 0)
		{
			rxBuffer[rxIdx] = UART_RX_BUFFER;

			if (rxBuffer[rxIdx] == 0x0D)
			{
				rxCompleteFlag = 1;
				rxIdx = 0;
			}
			else
			{
				rxCompleteFlag = 0;
				rxIdx++;
			}
		}
		// clear interrupt flag
		UCA0IFG &= ~(UCRXIFG);
	}
}*/

// *************************************************************************************************
// End of file
