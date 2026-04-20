#include "../include/Cards.h"

void Cards::generateHand()
{
    for (int i = 0; i < m_CARDS_PER_HAND; i++)
    {
        m_cardType[i] = static_cast<CardType>(rand() % 4);
        m_cardNumber[i] = (rand() % 13) + 1;
    }
}

int Cards::calculateValue()
{
    int value = 0;
    generateHand();

    for (int i = 0; i < m_CARDS_PER_HAND; i++)
    {
        //calculate value of card hand
    }

    value = rand() % 20;    //temporary

    return value;
}