/*************************************************
 * @filename : main.c
 * @author   : Dhiraj Bennadi
 * @compiler : gcc
 *
 * Identification of any leveraged code : None
 * Applicable Links: None
 */

/*Standard File Inclusions*/
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include <string.h>
#include <stdint.h>

/*User Defined File Inclusions*/
#include "AESTesting.h"
#include "spi.h"

/*
 * Main function
 *
 * Parameters: None
 *
 * Returns: int.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    int result = 0;

    SPI0_Init();

    result += testSpiLoopBack();

    if(result == 0)
    {
    	PRINTF("SPI Loopback test passed\n\r");
    }

    result += testAESEncryptionDecryption();
    result += testAESEncryptionDecryption2();

    if(result == 0)
    {
    	PRINTF("All Tests Cases for Encryption and Decryption Passed\n\r");
    }
    else
    {
    	PRINTF("Encryption and Decryption Test cases failed\n\r");
    }

    return 0;

}
