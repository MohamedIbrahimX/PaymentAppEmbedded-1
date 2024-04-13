#include <stdio.h>
#include "card.h"

static char expDate[6] = { 0 };

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    char name[25] = {0};
    printf("Please Enter Your Name [20-24] characters : ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Removing newline character

    int len = strlen(name);
    if (len < 20 || len > 24)
    {
        return WRONG_NAME;
    }
    else
    {
        strcpy(cardData->cardHolderName, name);
        return CARD_OK;
    }
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    printf("Please Enter Your Card Expiry Date in [MM/YY] Format : ");
    fgets(expDate, sizeof(expDate), stdin);
    expDate[strcspn(expDate, "\n")] = '\0'; // Removing newline character

    if (strlen(expDate) != 5 || expDate[2] != '/')
    {
        return WRONG_EXP_DATE;
    }

    int cardMonth = atoi(expDate);
    int cardYear = atoi(expDate + 3);

    if ((cardMonth > 12 || cardMonth < 1) || (cardYear < 0 || cardYear > 99))
    {
        return WRONG_EXP_DATE;
    }

    strcpy(cardData->cardExpirationDate, expDate);

    return CARD_OK;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	char panNumber[30]={0};
	

	printf("Please Enter Your PAN Number [16-19] characters : ");

	char ch;
	int i = 0;
	fseek(stdin, 0, SEEK_END);
	while ((ch = getchar()) != '\n')
	{
		panNumber[i] = ch;
		i++;
	}

	int len = strlen(panNumber);
	if (!panNumber) return WRONG_PAN;
	if (len > 19 || len < 16)
	{
		return WRONG_PAN;
	}
	else
	{
			for (int i = 0; i <= len; i++)
			{
				cardData->primaryAccountNumber[i] = panNumber[i];
			}
			return CARD_OK;
	}
}
void getCardHolderNameTest(void)
{
    ST_cardData_t cardData;
    EN_cardError_t errorResult;

    printf("Tester Name: Mohamed Ibrahim\n");
    printf("Function Name: getCardHolderName\n");
    printf("---------------------------\n");

    // Test Case 1: Valid Name
    printf("Test Case 1: Valid Name\n");
    printf("Expected Result: Card is Ok\n");
    errorResult = getCardHolderName(&cardData);
    if (errorResult == CARD_OK)
        printf("Actual Result: Card is Ok\n");
    else
        printf("Actual Result: Wrong Input\n");
    printf("---------------------------\n");

    // Test Case 2: Short Name (less than 20 characters)
    printf("Test Case 2: Short Name (less than 20 characters)\n");
    printf("Expected Result: Wrong Name\n");
    errorResult = getCardHolderName(&cardData);
    if (errorResult == WRONG_NAME)
        printf("Actual Result: Wrong Name\n");
    else
        printf("Actual Result: Card is Ok\n");
    printf("---------------------------\n");

    // Test Case 3: No input
    printf("Test Case 3: No input\n");
    printf("Expected Result: Wrong Name\n");
    errorResult = getCardHolderName(&cardData);
    if (errorResult == WRONG_NAME)
        printf("Actual Result: Wrong Name\n");
    else
        printf("Actual Result: Card is Ok\n");
    printf("---------------------------\n");

    // Test Case 4: Name Contains invalid characters
    printf("Test Case 4: Name Contains invalid characters\n");
    printf("Expected Result: Wrong Name\n");
    errorResult = getCardHolderName(&cardData);
    if (errorResult == WRONG_NAME)
        printf("Actual Result: Wrong Name\n");
    else
        printf("Actual Result: Card is Ok\n");
    printf("---------------------------\n");

}



void getCardExpiryDateTest(void)
{

    //   test card module.
    printf("//__________________|getCardExpiryDate function testCases. |________________ \n");
    printf("Tester Name: Mohamed Ibrahim\nFunction Name: getCardExpiryDate\n");

    for (uint8_t i = 0; i < 4; i++)
    {
        uint8_t expectedResult = 0;
        ST_cardData_t cardDataTest;
        uint8_t callingResult = getCardExpiryDate(&cardDataTest); // get result of calling getCardExpiryDate

        if (callingResult == CARD_OK)
        {
            printf("Test Case %d:\nIntput: %s\nExpected Result: %s\nActual Result:   %s\n", i, expDate, "CARD_OK", "CARD_OK");
        }

        else if (callingResult == WRONG_EXP_DATE)
        {
            printf("Test Case %d:\nIntput: %s\nExpected Result: %s\nActual Result:   %s\n", i, expDate, "WRONG_EXP_DATE", "WRONG_EXP_DATE");
        }
        else
        {

        }
    }
}




void getCardPANTest()
{
    // Test Case 1: Happy Case - Valid PAN (length = 16)
    printf("Test Case 1:\n");
    printf("Input Data: Valid PAN (16 digits)\n");
    printf("Expected Result: CARD_OK\n");
    ST_cardData_t cardData1;
    EN_cardError_t result1 = getCardPAN(&cardData1);
    printf("Actual Result: %s\n", result1 == CARD_OK ? "CARD_OK" : "WRONG_PAN");
    printf("\n");

    // Test Case 2: Invalid PAN (length < 16)
    printf("Test Case 2:\n");
    printf("Input Data: Invalid PAN (less than 16 digits)\n");
    printf("Expected Result: WRONG_PAN\n");
    ST_cardData_t cardData2;
    EN_cardError_t result2 = getCardPAN(&cardData2);
    printf("Actual Result: %s\n", result2 == WRONG_PAN ? "WRONG_PAN" : "CARD_OK");
    printf("\n");

    // Test Case 3: Invalid PAN (characters instead of numbers)
    printf("Test Case 3:\n");
    printf("Input Data: PAN with characters (not numbers)\n");
    printf("Expected Result: WRONG_PAN\n");
    ST_cardData_t cardData3;
    // Simulate entering characters instead of numbers
    strcpy(cardData3.primaryAccountNumber, "ABCDE12345");
    EN_cardError_t result3 = getCardPAN(&cardData3);
    if (result3 == CARD_OK)
    {
        printf("Actual Result: CARD_OK \n\n");

    }
    else
    {
        printf("Actual Result: WRONG_PAN \n\n");
    }
    printf("\n");


}
