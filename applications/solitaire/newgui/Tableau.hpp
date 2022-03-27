#pragma once

#include "TableauPile.hpp"
#include "DealPile.hpp"

class Tableau
{
public:

	TableauPile* visiblePile;
	TableauPile* hiddenPile;
	Tableau(Tableau* other);
	Tableau(int initialCardCount, DealPile* dealPile);
	TableauPile* getVisiblePile();
	TableauPile* getHiddenPile();
	void flipOverCard();
};
