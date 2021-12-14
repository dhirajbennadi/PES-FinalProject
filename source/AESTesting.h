/*************************************************
 * @filename : AESTesting.h
 * @author   : Dhiraj Bennadi
 * @compiler : gcc
 *
 * Identification of any leveraged code : None
 * Applicable Links: None
 */

#ifndef AESTESTING_H_
#define AESTESTING_H_

/*
 * This function tests the AES Encryption and Decryption for
 * different values of strings (String Length 16 bytes)
 *
 * Parameters: uint8_t* str: String to be printed
 * 			   uint8_t length: Length of the string to be printed
 *
 * Returns: SUCCESS, if encryption and decryption is successful
 *          FAILURE, if encryption and decryption is not successful
 */
int testAESEncryptionDecryption(void);

/*
 * This function tests the AES Encryption and Decryption for
 * different values of strings (String Length 64 bytes)
 *
 * Parameters: uint8_t* str: String to be printed
 * 			   uint8_t length: Length of the string to be printed
 *
 * Returns: SUCCESS, if encryption and decryption is successful
 *          FAILURE, if encryption and decryption is not successful
 */
int testAESEncryptionDecryption2(void);

#endif /* AESTESTING_H_ */
