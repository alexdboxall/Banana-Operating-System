
#include "DealPile.hpp"
#include <stdlib.h>
#include <stdio.h>

bool DealPile::canAdd(Card c)
{
	return false;
}

bool DealPile::canAdd(Pile* p)
{
	return false;
}

void DealPile::fill(int seed)
{
	// add one card of every suit
	for (int rank = RANK_ACE; rank <= RANK_KING; ++rank) {
		forceAddCard(Card(Suit::Club, rank));
		forceAddCard(Card(Suit::Spade, rank));
		forceAddCard(Card(Suit::Diamond, rank));
		forceAddCard(Card(Suit::Heart, rank));
	}

	for (int i = 0; i < 1000; ++i) {
		int card1 = rand() % 52;
		int card2 = rand() % 52;

		Suit tempSuit = cards[card1].suit;
		int tempRank = cards[card1].rank;

		cards[card1].suit = cards[card2].suit;
		cards[card1].rank = cards[card2].rank;

		cards[card2].suit = tempSuit;
		cards[card2].rank = tempRank;
	}
}

DealPile::DealPile() : Pile()
{
}

DealPile::DealPile(Pile* p) : Pile(p)
{
}