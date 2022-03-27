
#pragma once

enum class Suit
{
	Heart,
	Diamond,
	Spade,
	Club,
};

#define	RANK_ACE		1
#define	RANK_JACK		11
#define	RANK_QUEEN		12
#define	RANK_KING		13

class Card
{
public:
	Suit suit;
	int rank;

	Card();

	Card(Suit _suit, int _rank);
	Suit getSuit();
	int getRank();
	bool isRed();
	bool isBlack();
	bool isAlternateColour(Card other);
	bool isRankedOneAbove(Card other);
	bool isRankedOneBelow(Card other);
};
