/*************************************************
 * @filename : spi.h
 * @author   : Dhiraj Bennadi
 * @compiler : gcc
 *
 * Identification of any leveraged code : None
 * Applicable Links: None
 */

#ifndef SPI_H_
#define SPI_H_


/*
 * This function performs a test for transmission and reception
 * of bytes on the SPI0 Module
 *
 * Parameters: None
 *
 * Returns: int: SUCCESS if data transmitted and received is same
 * 				 FAILURE if data transmitted and received is not same
 */
int testSpiLoopBack(void);

/*
 * This function initializes SPI0 Module
 *
 * Parameters: None
 *
 * Returns: None
 */
void SPI0_Init(void);

/*
 * This function transmits a byte of data from SPI0 Module
 *
 * Parameters: unsigned char data: Data to be transmitted
 *
 * Returns: char: Data on the SPI0 buffer
 */
char SPI0_Transmit(unsigned char data);

#endif /* SPI_H_ */
