#include "Pile.hpp"
#include "Card.hpp"

Pile::Pile(Pile* other)
{
	for (int i = 0; i < other->numCards; ++i) {
		cards[i] = Card(other->cards[i].suit, other->cards[i].rank);
	}
	numCards = other->numCards;
}

Card Pile::getBottomCard()
{
	return cards[numCards - 1];
}

Card Pile::getTopCard()
{
	return cards[0];
}

Card Pile::removeTopCard()
{
	Card ret = getTopCard();
	for (int i = 0; i < 63; ++i) {
		cards[i] = cards[i + 1];
	}
	numCards--;
	return ret;
}

Card Pile::removeBottomCard()
{
	Card ret = getBottomCard();
	numCards--;
	return ret;
}

int Pile::getHeight()
{
	return numCards;
}

void Pile::forceAddCard(Card c)
{
	for (int i = 63; i > 0; --i) {
		cards[i] = cards[i - 1];
	}
	cards[0] = c;
	numCards++;
}

bool Pile::addCard(Card c)
{
	if (!canAdd(c)) {
		return false;
	}

	forceAddCard(c);

	return true;
}

void Pile::forceAddPile(Pile* p)
{
	while (p->getHeight() != 0) {
		forceAddCard(p->removeBottomCard());
	}
}

bool Pile::addPile(Pile* p)
{
	if (p->getHeight() == 1) {
		return addCard(p->getTopCard());
	}
	if (!canAdd(p)) {
		return false;
	}

	while (p->getHeight() != 0) {
		forceAddCard(p->removeBottomCard());
	}

	return true;
}

Pile::Pile()
{
	numCards = 0;
}

Pile::Pile(Pile* other, int amount)
{
	while (amount-- != 0 && other->getHeight() != 0) {
		cards[numCards++] = other->removeTopCard();
	}
}