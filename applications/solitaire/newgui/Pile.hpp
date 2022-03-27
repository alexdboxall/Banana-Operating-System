#pragma once
#include "Card.hpp"

class Pile
{
public:
	virtual bool canAdd(Card c) = 0;
	virtual bool canAdd(Pile* p) = 0;

	Card cards[64];
	int numCards;

	Pile(Pile* other);
	Card getBottomCard();
	Card getTopCard();
	Card removeTopCard();
	Card removeBottomCard();
	int getHeight();
	void forceAddCard(Card c);
	bool addCard(Card c);
	void forceAddPile(Pile* p);
	bool addPile(Pile* p);
	Pile();
	Pile(Pile* other, int amount);
};
