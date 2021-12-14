/*************************************************
 * @filename : AESTesting.c
 * @author   : Dhiraj Bennadi
 * @compiler : gcc
 *
 * Identification of any leveraged code : None
 * Applicable Links: None
 */
#ifndef AESTESTING_C_
#define AESTESTING_C_

/*Standard file inclusions*/
#include <stdint.h>
#include "fsl_debug_console.h"

/*User defined file inclusions*/
#include "AESTesting.h"
#include "AES.h"
#include "spi.h"


/*MACROS*/
#define SUCCESS 0
#define FAILURE 1

/*AES Algorithm Key Size*/
#define KEY_SIZE 				    16
/*AES Algorithm IV Size*/
#define INITIALIZATION_VECTOR_SIZE  16

/*Automated Tests 1 Input String Size*/
#define TEST_1_INPUT_SIZE           16
/*Automated Tests 2 Input String Size*/
#define TEST_2_INPUT_SIZE           64

static void test_encrypt_cbc(uint8_t *Key, uint8_t *Iv,
		uint8_t *CipherText , uint8_t length);
static void test_decrypt_cbc(uint8_t *Key, uint8_t *cipherText ,
		uint8_t *Iv, uint8_t length);
static void printString(uint8_t *buffer, uint8_t length);

typedef struct {
	uint8_t InputString[TEST_1_INPUT_SIZE];
	uint8_t Key[KEY_SIZE];
	uint8_t InitializationVector[INITIALIZATION_VECTOR_SIZE];
} test_matrix_t;

typedef struct {
	uint8_t InputString[TEST_2_INPUT_SIZE];
	uint8_t Key[KEY_SIZE];
	uint8_t InitializationVector[INITIALIZATION_VECTOR_SIZE];
} test_matrix_t2;

/*
 * This function decrypts the encryption message into plaintext
 *
 * Parameters: uint8_t *Key: Secret Key to encrypt the message
 * 			   uint8_t *cipherText: Ciphertext to decrypt
 * 			   uint8_t *Iv: Initialization Vector to introduce randomness
 * 			   uint8_t length: Length of the encrypted text
 *
 * Returns: None
 */
static void test_decrypt_cbc(uint8_t *Key, uint8_t *cipherText , uint8_t *Iv, uint8_t length)
{
	struct AES_ctx ctx;
	/*Initialization of AES Context Structure*/
	AES_init_ctx_iv(&ctx, Key, Iv);
	/*Decryption of Cipher Text*/
	AES_CBC_decrypt_buffer(&ctx, cipherText, length);

}

/*
 * This function prints the value of the string in Hex
 *
 * Parameters: uint8_t* str: String to be printed
 * 			   uint8_t length: Length of the string to be printed
 *
 * Returns: None
 */
static void printHexString(uint8_t* str , uint8_t length)
{
	unsigned char i;
	for (i = 0; i < length; ++i)
	{
		PRINTF("%x", str[i]);
	}
	PRINTF("\n");
}

/*
 * This function encrypts the plaintext
 *
 * Parameters: uint8_t *Key: Secret Key to encrypt the message
 * 			   uint8_t *cipherText: Text to encrypt and store result
 * 			   uint8_t *Iv: Initialization Vector to introduce randomness
 * 			   uint8_t length: Length of the encrypted text
 *
 * Returns: None
 */
static void test_encrypt_cbc(uint8_t *Key, uint8_t *Iv,
		uint8_t *CipherText , uint8_t length)
{
	struct AES_ctx ctx;
	/*Initialization of AES Context Structure*/
	AES_init_ctx_iv(&ctx, Key, Iv);
	/*Encryption of Text*/
	AES_CBC_encrypt_buffer(&ctx, CipherText, length);

}

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
int testAESEncryptionDecryption(void)
{
	uint8_t cipherText[TEST_1_INPUT_SIZE];
	uint8_t plainText[TEST_1_INPUT_SIZE];
	uint8_t textToDecrypt[TEST_1_INPUT_SIZE];
	int testsPassed = 0;
	int i,j;
	test_matrix_t tests[] =
	{
			/*Plaintext , Secret Key, Initialization Vector*/
			{"DhirajDecember21" , "DhirajNovember21" , "DhirajOctober512"},
			{"DhirajDecember22" , "DhirajNovember22" , "DhirajOctober512"},
			{"DhirajDecember23" , "DhirajNovember23" , "DhirajOctober512"},
			{"DhirajPES2021" , "DhirajNovember23" , "DhirajOctober512"},
	};

	const int num_tests = sizeof(tests) / sizeof(test_matrix_t);

	for(i = 0; i < num_tests; i++)
	{
		PRINTF("InputText = ");
		printString(tests[i].InputString , sizeof(tests[i].InputString));
		memcpy(cipherText, tests[i].InputString, sizeof(tests[i].InputString));
		test_encrypt_cbc(tests[i].Key , tests[i].InitializationVector , cipherText, sizeof(tests[i].InputString));

		PRINTF("CipherText = ");
		printHexString(cipherText, sizeof(tests[i].InputString));

		/*Transmits the Encrypted text over SPI bus*/
		for(j = 0; j < sizeof(tests[i].InputString);j++)
		{
			textToDecrypt[j] = SPI0_Transmit(cipherText[j]);
		}

		test_decrypt_cbc(tests[i].Key , textToDecrypt,
				tests[i].InitializationVector, sizeof(tests[i].InputString));

		memcpy(plainText, textToDecrypt, sizeof(tests[i].InputString));
		PRINTF("OutputText = ");
		printString(plainText , sizeof(tests[i].InputString));

		if(SUCCESS == memcmp(tests[i].InputString, plainText, sizeof(tests[i].InputString)))
		{
			testsPassed++;
		}


	}

	if(testsPassed == num_tests)
	{
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}


}


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
int testAESEncryptionDecryption2()
{
	uint8_t cipherText[TEST_2_INPUT_SIZE];
	uint8_t plainText[TEST_2_INPUT_SIZE];
	uint8_t textToDecrypt[TEST_2_INPUT_SIZE];
	int testsPassed = 0;
	int i,j;
	test_matrix_t2 tests[] =
	{
			/*Plaintext , Secret Key, Initialization Vector*/
			{"DhirajDecember21DhirajDecember21" , "DhirajNovember21" , "DhirajOctober512"},
			{"DhirajDecember22DhirajDecember22" , "DhirajNovember22" , "DhirajOctober512"},
			{"DhirajDecember23DhirajDecember23" , "DhirajNovember23" , "DhirajOctober512"},
			{"DhirajPES2021DhirajPES2021" , "DhirajNovember23" , "DhirajOctober512"},
	};

	const int num_tests = sizeof(tests) / sizeof(test_matrix_t2);

	for(i = 0; i < num_tests; i++)
	{
		PRINTF("InputText = ");
		printString(tests[i].InputString , sizeof(tests[i].InputString));
		memcpy(cipherText, tests[i].InputString, sizeof(tests[i].InputString));
		test_encrypt_cbc(tests[i].Key , tests[i].InitializationVector , cipherText, sizeof(tests[i].InputString));

		PRINTF("CipherText = ");
		printHexString(cipherText, sizeof(tests[i].InputString));

		/*Transmits the Encrypted text over SPI bus*/
		for(j = 0; j < sizeof(tests[i].InputString);j++)
		{
			textToDecrypt[j] = SPI0_Transmit(cipherText[j]);
		}

		test_decrypt_cbc(tests[i].Key , textToDecrypt,
				tests[i].InitializationVector, sizeof(tests[i].InputString));

		memcpy(plainText, textToDecrypt, sizeof(tests[i].InputString));
		PRINTF("OutputText = ");
		printString(plainText , sizeof(tests[i].InputString));

		if(SUCCESS == memcmp(tests[i].InputString, plainText, sizeof(tests[i].InputString)))
		{
			testsPassed++;
		}

	}

	if(testsPassed == num_tests)
	{
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}


}


/*
 * This function prints the value of string in ASCII
 *
 * Parameters: uint8_t* buffer: String to be printed
 * 			   uint8_t length: Length of the string to be printed
 *
 * Returns: None
 */
static void printString(uint8_t *buffer, uint8_t length)
{
	int index;
	for(index = 0; index < length; index++)
	{
		PRINTF("%c", buffer[index]);
	}
	PRINTF("\n\r");
}

#endif /* AESTESTING_C_ */
