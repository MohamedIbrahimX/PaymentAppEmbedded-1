#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include <stdio.h>


ST_terminalData_t termTest =
{
    500.0,
    1000.0,
    "28/09/2023"
};

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {

    char c;
    int count = 0;
    char dayStr[3], monthStr[3], yearStr[5];
    int day, month, year;
    printf("Please, Enter a valid transaction Date in the format of dd/mm/yyyy: ");
    while ((c = getchar()) != '\n')
    {
        if (count < 11)
        {
            if (c != '/' && (c < '0' || c > '9'))
            {
                return WRONG_DATE;
            }
            termData->transactionDate[count++] = c;
        }
    }


    if (count != 10 || termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/')
    {
        return WRONG_DATE;
    }
    sscanf_s((const char*)termData->transactionDate, "%2s/%2s/%4s", dayStr, sizeof(dayStr), monthStr, sizeof(monthStr), yearStr, sizeof(yearStr));
    //sscanf((const char*)termData->transactionDate, "%2s/%2s/%4s", dayStr, monthStr, yearStr);
    day = atoi(dayStr);
    month = atoi(monthStr);
    year = atoi(yearStr);

    if (day < 1 || day > 31 || month < 1 || month > 12 || year <= 0 || year > 2024) {
        return WRONG_DATE;
    }
    return TERMINAL_OK;
}

void getTransactionDateTest(void) {
    printf("Tester Name: Mohamed Ibrahim\n");
    printf("Function Name: getTransactionDate\n\n");

    // Test Case 1: Happy scenario (valid date)
    printf("Test Case 1:\n");
    printf("Input Data: Enter a valid date (dd/mm/yyyy)\n");
    printf("Expected Result: TERMINAL_OK\n");
    ST_terminalData_t termData1;
    printf("Enter date: ");
    EN_terminalError_t result1 = getTransactionDate(&termData1);
    printf("Actual Result: %s\n\n", result1 == TERMINAL_OK ? "TERMINAL_OK" : "WRONG_DATE");

    // Test Case 2: Invalid date format (less than 10 characters)
    printf("Test Case 2:\n");
    printf("Input Data: Enter a date with less than 10 characters\n");
    printf("Expected Result: WRONG_DATE\n");
    ST_terminalData_t termData2;
    printf("Enter date: ");
    EN_terminalError_t result2 = getTransactionDate(&termData2);
    printf("Actual Result: %s\n\n", result2 == WRONG_DATE ? "WRONG_DATE" : "TERMINAL_OK");

    // Test Case 3: Invalid date format (more than 10 characters)
    printf("Test Case 3:\n");
    printf("Input Data: Enter a date with more than 10 characters\n");
    printf("Expected Result: WRONG_DATE\n");
    ST_terminalData_t termData3;
    printf("Enter date: ");
    EN_terminalError_t result3 = getTransactionDate(&termData3);
    printf("Actual Result: %s\n\n", result3 == WRONG_DATE ? "WRONG_DATE" : "TERMINAL_OK");

}



EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {

    int cardDay, cardMonth;
    sscanf_s(cardData->cardExpirationDate, "%2d/%2d", &cardDay, &cardMonth);

    int transDay, transMonth;
    sscanf_s(termData->transactionDate, "%2d/%2d", &transDay, &transMonth);

    if (cardMonth < transMonth)
        return EXPIRED_CARD;
    else if (cardMonth > transMonth)
        return TERMINAL_OK;
    else {
        if (cardDay < transDay)
            return EXPIRED_CARD;
        else if (cardDay > transDay)
            return TERMINAL_OK;
        else
            return TERMINAL_OK;
    }
}


void isCardExpriedTest(void)
{

    uint8_t cardDataTestCases[5][6] = { "10/22", "12/23", "12/25", "05/20", "10/19" };                             //Test cases values
    uint8_t TerminalTestCases[5][11] = { "05/11/2022", "09/12/2022", "23/12/2020", "15/06/2020", "23/12/2019" };                           //  Test cases values
    uint8_t TestCasesResult[5] = { EXPIRED_CARD, TERMINAL_OK, TERMINAL_OK, EXPIRED_CARD, EXPIRED_CARD };           //Test cases expected result

    ST_cardData_t cardDataTest;
    ST_terminalData_t cardTerminalTest; //   test card module.
    printf("//______|isCardExpried function testCases. |______ \n");
    printf("Tester Name: Mohamed Ibrahim\nFunction Name: isCardExpried\n");

    for (uint8_t i = 0; i < 5; i++)
    {
        strcpy(cardDataTest.cardExpirationDate, cardDataTestCases[i]);                     //update test card module  with test case
        strcpy(cardTerminalTest.transactionDate, TerminalTestCases[i]);                   //update test card module  with test case

        uint8_t callingResult = isCardExpired(&cardDataTest, &cardTerminalTest);          //get result of calling getCardExpiryDate
        if (TestCasesResult[i] == TERMINAL_OK && callingResult == TERMINAL_OK)
        {
            printf("Test Case %d:\nIntput: %s\nExpected Result:%s\nActual Result: %s\n", i, cardDataTestCases[i], "TERMINAL_OK", "TERMINAL_OK");
        }
        else if (TestCasesResult[i] == EXPIRED_CARD && callingResult == TERMINAL_OK)
        {
            printf("Test Case %d:\nIntput: %s\nExpected Result:%s\nActual Result: %s\n", i, cardDataTestCases[i], "EXPIRED_CARD", "TERMINAL_OK");
        }
        else if (TestCasesResult[i] == EXPIRED_CARD && callingResult == EXPIRED_CARD)
        {
            printf("Test Case %d:\nIntput: %s\nExpected Result:%s\nActual Result: %s\n", i, cardDataTestCases[i], "EXPIRED_CARD", "EXPIRED_CARD");
        }
        else if (TestCasesResult[i] == TERMINAL_OK && callingResult == EXPIRED_CARD)
        {
            printf("Test Case %d:\nIntput: %s\nExpected Result:%s\nActual Result: %s\n", i, cardDataTestCases[i], "TERMINAL_OK", "EXPIRED_CARD");
        }
        else
        {
            /* DO NOTHING. */
        }
    }
}



EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
    printf("Please, Set the Maximum Amount per transaction: ");

    while (scanf_s("%f", &maxAmount) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\nPlease enter a valid Amount: ");
    }
    if (maxAmount <= 0)
        return INVALID_MAX_AMOUNT;
    else
        termData->maxTransAmount = maxAmount;
        return TERMINAL_OK;

}

void setMaxAmountTest(void)
{
    float enteredMaxAmount;                 //Variable to store the entered max amount
    ST_terminalData_t termData;             //Structure to hold terminal data
    EN_terminalError_t errorResult;         //Variable to store the error result

    printf("Tester Name:MOhamed Ibrahim\n");
    printf("Function Name: setMaxAmount\n");
    printf("---------------------------\n");

    //Test Case 1: check if the entered amount is Valid (more than 0.0)
    printf("Test Case 1: Valid Amount (more than 0.0)\n");
    printf("Enter Max Amount: \n");                         //Prompt the user to enter the max amount
    scanf_s("%f", &enteredMaxAmount);                         //Read the user's input and store it in enteredMaxAmount
    printf("Expected Result: maxAmount is Valid\n");
    errorResult = setMaxAmount(&termData, enteredMaxAmount);
    if (errorResult == TERMINAL_OK)
        printf("Actual Result: maxAmount is Valid\n");
    else
        printf("Actual Result: Invalid Amount\n");
    printf("---------------------------\n");

    // Test Case 2: if the entered max amount equals 0.0
    printf("Test Case 2: Valid Amount (equals 0.0)\n");
    printf("Enter Max Amount: \n");                        //Prompt the user to enter the max amount
    scanf_s("%f", &enteredMaxAmount);                        //Read the user's input and store it in enteredMaxAmount
    printf("Expected Result: maxAmount is Invalid\n");
    errorResult = setMaxAmount(&termData, enteredMaxAmount);
    if (errorResult == TERMINAL_OK)
        printf("Actual Result: Amount is Valid\n");
    else
        printf("Actual Result: maxAmount is Invalid\n");
    printf("---------------------------\n");

    //Test Case 3: if the entered max amount is less than 0.0
    printf("Test Case 3: Invalid Amount (less than 0.0)\n");
    printf("Enter Max Amount: \n");                     //Prompt the user to enter the max amount
    scanf_s("%f", &enteredMaxAmount);                     //Read the user's input and store it in enteredMaxAmount
    printf("Expected Result: maxAmount is Invalid\n");
    errorResult = setMaxAmount(&termData, enteredMaxAmount);
    if (errorResult == TERMINAL_OK)
        printf("Actual Result: Amount is Valid\n");
    else
        printf("Actual Result: maxAmount is Invalid\n");
    printf("---------------------------\n");
}



EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
    printf("Please, Enter valid Amount Transaction (don't exceed the max amount): ");
    while (scanf_s("%f", &termData->transAmount) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\nPlease enter a valid Amount: ");
    }
    if (termData->transAmount <= 0)
        return INVALID_AMOUNT;
    else
        return TERMINAL_OK;

}

void getTransactionAmountTest(void)
{
    ST_terminalData_t termData;
    EN_terminalError_t errorResult;

    printf("Tester Name: Mohamed Ibrahim\n");
    printf("Function Name: getTransactionAmount\n");
    printf("---------------------------\n");

    //Test Case 1: check if the entered amount is Valid (more than 0.0)

    printf("Test Case 1: Valid Amount\n");
    printf("Expected Result: Amount is Valid\n");
    errorResult = getTransactionAmount(&termData);
    if (errorResult == TERMINAL_OK)
        printf("Actual Result: Amount is Valid\n");
    else
        printf("Actual Result: Invalid Amount\n");
    printf("---------------------------\n");

    //Test Case 2: if the entered amount equals 0.0
    printf("Test Case 2: invalid Amount (equals 0.0)\n");
    printf("Expected Result: Amount is inValid\n");
    errorResult = getTransactionAmount(&termData);
    if (errorResult == TERMINAL_OK)
        printf("Actual Result: Amount is Valid\n");
    else
        printf("Actual Result: Invalid Amount\n");
    printf("---------------------------\n");

    //Test Case 3: if the entered amount less 0.0
    printf("Test Case 3: invalid Amount (less than 0.0)\n");
    printf("Expected Result: Amount is inValid\n");
    errorResult = getTransactionAmount(&termData);
    if (errorResult == TERMINAL_OK)
        printf("Actual Result: Amount is Valid\n");
    else
        printf("Actual Result: Invalid Amount\n");
    printf("---------------------------\n");
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
    if (termData->transAmount > termData->maxTransAmount)
        return EXCEED_MAX_AMOUNT;
    else
        return TERMINAL_OK;
}


void isBelowMaxAmountTest(void)
{
    EN_terminalError_t errorResult; // Variable to store the error result

    printf("Tester Name: Mohamed Ibrahim\n");
    printf("Function Name: isBelowMaxAmount\n");
    printf("Max amount is set here for testing = 1000.0\n");
    printf("---------------------------\n");

    //Test Case 1: check if the entered amount is Valid (Means is below the max amount)
    printf("Test Case 1: Valid Amount (below the max amount)\n");
    printf("Expected Result: Amount is Valid\n");
    errorResult = isBelowMaxAmount(&termTest);
    if (errorResult == TERMINAL_OK)
        printf("Actual Result: Amount is Valid\n");
    else
        printf("Actual Result: Invalid Amount\n");
    printf("---------------------------\n");

    //Test Case 2: if the entered amount equals the max amount

    printf("Test Case 2: Valid Amount (equals the max amount)\n");
    printf("Expected Result: Amount is Valid\n");
    errorResult = isBelowMaxAmount(&termTest);
    if (errorResult == TERMINAL_OK)
        printf("Actual Result: Amount is Valid\n");
    else
        printf("Actual Result: Invalid Amount\n");
    printf("---------------------------\n");

    //Test Case 3: if the entered amount exceeds the max amount

    printf("Test Case 3: invalid Amount (exceeds the max amount)\n");
    printf("Expected Result: Invalid Amount\n");
    errorResult = isBelowMaxAmount(&termTest);
    if (errorResult == TERMINAL_OK)
        printf("Actual Result: Amount is Valid\n");
    else
        printf("Actual Result: Invalid Amount\n");
    printf("---------------------------\n");
}