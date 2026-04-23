#include "../include/Cards.h"

Cards::Cards()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; j <= 13; j++)
        {
            m_deck.push_back({ static_cast<CardType>(i), j });
        }
    }
}

void Cards::shuffleDeck()
{
    for (int i = m_deck.size() - 1; i > 0; i--)
    {
        int swaper = rand() % (i + 1);
        std::swap(m_deck[i], m_deck[swaper]);
    }
}

void Cards::generateHand()
{
    if (m_deck.size() < m_CARDS_PER_HAND)
    {
        m_deck.clear();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 1; j <= 13; j++)
            {
                m_deck.push_back({ static_cast<CardType>(i), j });
            }
        }
    }

    shuffleDeck();

    m_hand.clear();

    for (int i = 0; i < m_CARDS_PER_HAND; i++)
    {
        m_hand.push_back(m_deck.back());
        m_deck.pop_back();
    }
}

int Cards::calculateValue()
{
    int value = 0;
    generateHand();

    //count occurrences
    int count[14] = { 0 };
    int typeCount[4] = { 0 };

    for (const auto& card : m_hand)
    {
        count[card.second]++;
        typeCount[card.first]++;
    }

    //flags for types of hands
    bool pair = false;
    bool twoPair = false;
    bool three = false;
    bool four = false;

    int pairsFound = 0;

    //get duplicates
    for (int i = 1; i <= 13; i++)
    {
        if (count[i] == 2) pairsFound++;
        if (count[i] == 3) three = true; //eg. 7C, 7H, 7D, 9S, KD - three of kind
        if (count[i] == 4) four = true; //eg. 7C, 7H, 7D, 7S, KD - three of kind
    }

    if (pairsFound == 1) pair = true; //eg. 7C, 7H, 2D, 9S, KD - the two 7 are a pair
    if (pairsFound == 2) twoPair = true; //eg. 7C, 7H, 9D, 9S, KD - two 7, two 9 -> two pairs

    bool fullHouse = three && pair; //eg. 7C, 7H, 7D, 9D, 9S - three of kind and pair

    bool flush = false;
    for (int i = 0; i < 4; i++)
    {
        if (typeCount[i] == 5) flush = true; //eg. 7H, 9H, KH, JH, 3H - all same suit
    }

    //check straight
    bool straight = false;
    for (int i = 1; i <= 9; i++)
    {
        if (count[i] && count[i + 1] && count[i + 2] && count[i + 3] && count[i + 4])
        {
            straight = true; //eg. 5D, 6S, 7H, 8C, 9D - row of numbers
            break;
        }
    }

    bool straightFlush = straight && flush; //eg. 5H, 6H, 7H, 8H, 9H - both number row and same suit

    //scoring based on hand
    if (straightFlush) value = 200;
    else if (four) value = 150;
    else if (fullHouse) value = 120;
    else if (flush) value = 100;
    else if (straight) value = 80;
    else if (three) value = 60;
    else if (twoPair) value = 40;
    else if (pair) value = 20;
    else
    {
        //fallback, no combinations
        for (int i = 0; i < m_CARDS_PER_HAND; i++)
        {
            value = value + m_hand.at(i).second;
        }

        value = value / 5; //less than for no combo
    }

    return value;
}