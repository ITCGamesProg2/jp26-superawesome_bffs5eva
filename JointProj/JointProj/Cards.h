#pragma once

#include <cstdlib>

class Cards
{
public:
	int calculateValue();			//calculates the value of a hand [poker rules]
									
private:
	void generateHand();			//generates a hand of cards

	enum CardType { Heart, Diamond, Club, Spade };

	const static int CARDS_PER_HAND{ 5 };

	//can change to one std::pair array later
	CardType m_cardType[CARDS_PER_HAND];
	int m_cardNumber[CARDS_PER_HAND];
};