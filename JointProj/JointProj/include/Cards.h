#pragma once

#include <cstdlib>
#include <algorithm>
#include <vector>

class Cards
{
public:
	Cards();

	int calculateValue();			//calculates the value of a hand [poker rules]

private:
	void shuffleDeck();
	void generateHand();			//generates a hand of cards

	enum CardType { Heart, Diamond, Club, Spade };

	const static int m_CARDS_PER_DECK{ 52 };
	std::vector<std::pair<CardType, int>> m_deck;

	const static int m_CARDS_PER_HAND{ 5 };
	std::vector<std::pair<CardType, int>> m_hand;
};