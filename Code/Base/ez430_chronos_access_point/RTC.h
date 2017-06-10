// *************************************************************************************************
// Public header for hardware RTC (no interrupt)
// *************************************************************************************************

#ifndef RTC_H
#define RTC_H


// *************************************************************************************************
// Include section

#include "project.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
// *************************************************************************************************
// Defines section

// DCO frequency division factor determining speed of the radio SPI interface in Hz
//  Max. value for UART1101 is 6.5MHz
#define UART_BR_DIVIDER        ((MCLK_FREQUENCY / 6500000) + 1)

// Required delay after selecting radio in us
#define UART_CSN_DELAY         (20)

// Port and pin resources for UART interface
// UART registers
#define UART_TX_BUFFER			(UCA1TXBUF)
#define UART_RX_BUFFER			(UCA1RXBUF)
#define UART_STATUS				(UCA1STAT)
#define UART_CTL0          		(UCA1CTL0)
#define UART_CTL1				(UCA1CTL1)
#define UART_BR0				(UCA1BR0)
#define UART_BR1				(UCA1BR1)
#define UART_MCTL				(UCA1MCTL)
#define UART_FLAGS				(UCA1IFG)
#define UART_RECV_BIT			(UCRXIFG)
#define UART_SEND_BIT			(UCTXIFG)
// Port and pin resource for TXD
#define UART_TXD_OUT           (P4OUT)
#define UART_TXD_DIR           (P4DIR)
#define UART_TXD_SEL           (P4SEL)
#define UART_TXD_PIN           (BIT5)
// Port and pin resource for RXD
#define UART_RXD_IN            (P4IN)
#define UART_RXD_DIR           (P4DIR)
#define UART_RXD_SEL           (P4SEL)
#define UART_RXD_PIN           (BIT4)

*/

// *************************************************************************************************
// Typedef section


// *************************************************************************************************
// API section

void RTC_Init_v(void);



#ifdef __cplusplus
}
#endif

// *************************************************************************************************
#endif // UART_H
// End of file
