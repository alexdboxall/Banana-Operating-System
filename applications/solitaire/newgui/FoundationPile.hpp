#pragma once
#include "Pile.hpp"

class FoundationPile : public Pile
{
public:
	bool canAdd(Card newCard);
	bool canAdd(Pile* p);
	FoundationPile();
	FoundationPile(Pile* p);
};
