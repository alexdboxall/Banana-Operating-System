#pragma once
#include "Pile.hpp"

class DealPile : public Pile
{
public:
	bool canAdd(Card c);
	bool canAdd(Pile* p);
	void fill(int seed);
	DealPile();
	DealPile(Pile* p);
};