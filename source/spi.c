/*************************************************
 * @filename : spi.c
 * @author   : Dhiraj Bennadi
 * @compiler : gcc
 *
 * Identification of any leveraged code : None
 * Applicable Links: None
 */
#ifndef SPI_C_
#define SPI_C_

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"

#define SUCCESS                      (0)
#define FAILURE                      (1)
#define LOOPBACK_TEST_COUNT          (10)

#define PORTD_PIN0  		         (0)
#define PORTD_PIN1  		         (1)
#define PORTD_PIN2  		         (2)
#define PORTD_PIN3  		         (3)
#define PORTD_ALT2_FUNCTIONALITY     (2)
/*
 * This function initializes SPI0 Module
 *
 * Parameters: None
 *
 * Returns: None
 */
void SPI0_Init(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;

	PORTD->PCR[PORTD_PIN0] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[PORTD_PIN0] |= PORT_PCR_MUX(PORTD_ALT2_FUNCTIONALITY);

	PORTD->PCR[PORTD_PIN1] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[PORTD_PIN1] |= PORT_PCR_MUX(PORTD_ALT2_FUNCTIONALITY);

	PORTD->PCR[PORTD_PIN2] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[PORTD_PIN2] |= PORT_PCR_MUX(PORTD_ALT2_FUNCTIONALITY);

	PORTD->PCR[PORTD_PIN3] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[PORTD_PIN3] |= PORT_PCR_MUX(PORTD_ALT2_FUNCTIONALITY);

	SPI0->C1 |= SPI_C1_MSTR_MASK | SPI_C1_SSOE_MASK;

	/*Baud Rate of 1Mhz*/
	/*Baud Rate = Bus Clock / (SPPR+ 1) * 2^(SPR+1)*/
	/*SPPR = 2 , SPR = 3 generates a clock of 1 MHz*/
	SPI0->BR = SPI_BR_SPPR(2) | SPI_BR_SPR(3);

	SPI0->C1 |= SPI_C1_SPE_MASK;

}


/*
 * This function transmits a byte of data from SPI0 Module
 *
 * Parameters: unsigned char data: Data to be transmitted
 *
 * Returns: char: Data on the SPI0 buffer
 */
char SPI0_Transmit(unsigned char data)
{
  volatile char echoedData;

  /*Wait Until Tx is Ready*/
  while(!(SPI0->S & SPI_S_SPTEF_MASK))
  {
	  ;
  } /* wait until tx ready */
  SPI0->D = data; /* send data byte */

  /*Wait Until Tx is Complete*/
  while(!(SPI0->S & SPI_S_SPRF_MASK))
  {

  }
  /*Reading the data clears the SPRF Flag*/
  echoedData = SPI0->D;

  return echoedData;
}


/*
 * This function performs a test for transmission and reception
 * of bytes on the SPI0 Module
 *
 * Parameters: None
 *
 * Returns: int: SUCCESS if data transmitted and received is same
 * 				 FAILURE if data transmitted and received is not same
 */
int testSpiLoopBack(void)
{
	int i;
	uint8_t inputData[LOOPBACK_TEST_COUNT] = {'a', 'b','c','d','e', 'f','g','h','i', 'j'};
	uint8_t outputData[LOOPBACK_TEST_COUNT];

	for(i = 0; i < LOOPBACK_TEST_COUNT; i++)
	{
		outputData[i] = SPI0_Transmit(inputData[i]);
	}

	if(SUCCESS == memcmp(inputData, outputData, LOOPBACK_TEST_COUNT))
	{
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

#endif /* SPI_C_ */
