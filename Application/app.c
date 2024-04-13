#include "app.h"
#include "../Card/card.h"
#include "../Server/server.h"
#include "../Terminal/terminal.h"
#include <stdio.h>
#include <stdbool.h>

void appStart()
{
	ST_cardData_t cardData;
	ST_terminalData_t terminalData;
	ST_transaction_t transactionData;
	EN_terminalError_t terminalReturn;
	EN_transState_t serverReturn;
	EN_cardError_t cardReturn;

	float MAX_AMOUNT = 0.0f;

	printf("--------------------- Welcome to our Payment Application ---------------------\n");
	printf("==============================================================================\n");
	while (true)
	{
		int userChoice = -1;
		printf("Enter 0 to Exit and 1 to enter your data\n");
		while (scanf_s("%d", &userChoice) != 1)
		{
			printf("Invalid input. Please enter an integer (0 OR 1)\n");
			printf("==============================================================================\n");
			while (getchar() != '\n') {}
		}

		switch (userChoice)
		{
		case 1:
			while (getchar() != '\n') {}
			printf("==============================================================================\n");
			//Card part
			cardReturn = getCardHolderName(&cardData);
			while (cardReturn == WRONG_NAME)
			{
				printf("**************************************************************************\n");
				printf("Please enter valid Name.\n");
				cardReturn = getCardHolderName(&cardData);
			}
			cardReturn = getCardExpiryDate(&cardData);
			while (cardReturn == WRONG_EXP_DATE)
			{
				while (getchar() != '\n') {}
				printf("**************************************************************************\n");
				printf("Please enter valid EXP Date.\n");
				cardReturn = getCardExpiryDate(&cardData);
			}
			cardReturn = getCardPAN(&cardData);
			while (cardReturn == WRONG_PAN)
			{
				while (getchar() != '\n') {}
				printf("**************************************************************************\n");
				printf("Please enter valid PAN Number.\n");
				cardReturn = getCardPAN(&cardData);
			}

			//Terminal part
			terminalReturn = getTransactionDate(&terminalData);
			while (terminalReturn == WRONG_DATE)
			{
				while (getchar() != '\n') {}
				printf("**************************************************************************\n");
				printf("Please enter valid transaction Date.\n");
				terminalReturn = getTransactionDate(&terminalData);//** cardData
			}
			terminalReturn = isCardExpired(&cardData, &terminalData);
			if (terminalReturn == EXPIRED_CARD)
			{
				printf("\nYour Card Expired !\n");
				return;
			}
			terminalReturn = setMaxAmount(&terminalData, MAX_AMOUNT);
			while (terminalReturn == INVALID_AMOUNT)
			{
				while (getchar() != '\n') {}
				printf("\nPlease enter valid Amount.\n");
				terminalReturn = setMaxAmount(&terminalData, MAX_AMOUNT);
			}
			terminalReturn = getTransactionAmount(&terminalData);
			while (terminalReturn == INVALID_AMOUNT)
			{
				while (getchar() != '\n') {}
				printf("\nPlease enter valid Amount.\n");
				terminalReturn = getTransactionAmount(&terminalData);
			}
			terminalReturn = isBelowMaxAmount(&terminalData);
			if (terminalReturn == EXCEED_MAX_AMOUNT)
			{
				printf("\nINVALID exceed maximum amount.\n");
				return;
			}

			// Saving data
			transactionData.cardHolderData = cardData;
			transactionData.terminalData = terminalData;

			// Server Part
			serverReturn = recieveTransactionData(&transactionData);
			switch (serverReturn)
			{
			case DECLINED_STOLEN_CARD:
				printf("\nSTOLEN CARD!! \n");
				break;

			case DECLINED_INSUFFECIENT_FUND:
				printf("\nINSUFFECIENT FUND.\n");
				break;

			case ACCOUNT_NOT_FOUND:
				printf("\nACCOUNT NOT FOUND\n");
				break;

			case INTERNAL_SERVER_ERROR:
				printf("\nINTERNAL SERVER ERROR\n");
				break;

			case APPROVED:
				printf("\nTransaction is approved.\n");
				printf("\nSaving transaction ...\n");
				break;
			}
			break;
		case 0:
			while (getchar() != '\n') {}
			printf("==============================================================================\n");
			printf("Thanks to use our Payment application\n");
			return;
		default:
			while (getchar() != '\n') {}
			printf("==============================================================================\n");
			printf("Please enter a valid choice (0 OR 1)\n");
			break;
		}
	}
}