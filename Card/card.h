//Header guard 
#ifndef CARD_H
#define CARD_H

#include <stdint.h>
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
    CARD_OK, 
    WRONG_NAME, 
    WRONG_EXP_DATE, 
    WRONG_PAN
}EN_cardError_t;


//typedef enum cardState
//{
//    BLOCKED = 0,
//    RUNNING
//} cardState;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

//Testing functions
void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);

//End of the header guard
#endif
