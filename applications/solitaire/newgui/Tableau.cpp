
#include "Tableau.hpp"

Tableau::Tableau(Tableau* other)
{
	visiblePile = new TableauPile(other->visiblePile);
	hiddenPile = new TableauPile(other->hiddenPile);
}

Tableau::Tableau(int initialCardCount, DealPile* dealPile)
{
	visiblePile = new TableauPile();
	hiddenPile = new TableauPile();

	while (initialCardCount-- != 0) {
		hiddenPile->forceAddCard(dealPile->removeTopCard());
	}

	flipOverCard();
}

TableauPile* Tableau::getVisiblePile()
{
	return visiblePile;
}

TableauPile* Tableau::getHiddenPile()
{
	return hiddenPile;
}

void Tableau::flipOverCard()
{
	if (hiddenPile->getHeight() != 0 && visiblePile->getHeight() == 0) {
		visiblePile->forceAddCard(hiddenPile->removeTopCard());
	}
}
