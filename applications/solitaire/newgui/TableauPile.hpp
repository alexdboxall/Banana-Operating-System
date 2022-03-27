#pragma once
#include "Pile.hpp"
#include "Card.hpp"

class TableauPile : public Pile
{
public:
	bool canAdd(Card newCard);
	bool canAdd(Pile* p);
	TableauPile(Pile* p, int count);
	TableauPile();
	TableauPile(Pile* p);
};