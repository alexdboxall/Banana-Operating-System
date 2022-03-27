
#include "TableauPile.hpp"

bool TableauPile::canAdd(Card newCard)
{
	if (getHeight() == 0) {
		// only kings are allowed to be placed on an empty pile
		return newCard.rank == RANK_KING;

	} else {
		// otherwise ensure that the top card is of a different colour
		// and has a value one above the new card
		Card top = getTopCard();
		return top.isAlternateColour(newCard) && top.isRankedOneAbove(newCard);
	}
}

bool TableauPile::canAdd(Pile* p)
{
	// we can add a pile as long as we can add its bottom card
	return canAdd(p->getBottomCard());
}

TableauPile::TableauPile(Pile* p, int count) : Pile(p, count)
{

}

TableauPile::TableauPile() : Pile()
{
}

TableauPile::TableauPile(Pile* p) : Pile(p)
{

}
