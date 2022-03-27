#include "FoundationPile.hpp"

bool FoundationPile::canAdd(Card newCard)
{
	if (getHeight() == 0) {
		// only an ace can be placed on an empty foundation
		return newCard.rank == RANK_ACE;
	} else {
		// otherwise ensure the suit is the same and it is one higher 
		// than the previous card
		Card top = getTopCard();
		return top.getSuit() == newCard.getSuit() && top.isRankedOneBelow(newCard);
	}
}

bool FoundationPile::canAdd(Pile* p)
{
	// you can only move individual cards to a foundation, not a pile
	// (as they are in the wrong order, and the colours alternate)
	return false;
}

FoundationPile::FoundationPile() : Pile()
{
}

FoundationPile::FoundationPile(Pile* p) : Pile(p)
{
}

