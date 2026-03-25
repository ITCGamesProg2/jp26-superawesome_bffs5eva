#pragma once

class Cards
{
public:
	void generateHand();			//generates a hand of cards
	int calculateValue();			//calculates the value of a hand [poker rules]
									
private:
	enum CardType { Heart, Diamond, Club, Spade };

	//can change to one std::pair array later
	CardType cardType[5];
	int cardNumber[5];
};