
#include "Card.hpp"

Card::Card(Suit _suit, int _rank)
{
	suit = _suit;
	rank = _rank;
}

Card::Card()
{
	suit = Suit::Club;
	rank = 3;
}

Suit Card::getSuit()
{
	return suit;
}

int Card::getRank()
{
	return rank;
}

bool Card::isRed()
{
	return suit == Suit::Heart || suit == Suit::Diamond;
}

bool Card::isBlack()
{
	return suit == Suit::Spade || suit == Suit::Club;
}

bool Card::isAlternateColour(Card other)
{
	return (isRed() && other.isBlack()) || (isBlack() && other.isRed());
}

bool Card::isRankedOneAbove(Card other)
{
	return rank == other.rank + 1;
}

bool Card::isRankedOneBelow(Card other)
{
	return rank == other.rank - 1;
}