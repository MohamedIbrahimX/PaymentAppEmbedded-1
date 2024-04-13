#include "Application/app.h"
#include "Card/card.h"
#include "Server/server.h"
#include "Terminal/terminal.h"

int main()
{
	////Card Testing functions
	//getCardHolderNameTest();
	//getCardExpiryDateTest();
	//getCardPANTest();

	////Terminal Testing functions Declaration
	//getTransactionAmountTest();
	//isBelowMaxAmountTest();
	//setMaxAmountTest();
	//getTransactionDateTest();


	////Server Testing functions
	//recieveTransactionDataTest();
	//isBlockedAccountTest();
	//listSavedTransactions();
	//saveTransactionTest();
	//isValidAccountTest();
	//isAmountAvailableTest();

    appStart();
    return 0;
}
