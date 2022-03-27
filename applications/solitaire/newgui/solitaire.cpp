#include "solitaire.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

Solitaire::Solitaire(Solitaire* other)
{
	firstMoveTimestamp = other->firstMoveTimestamp;
	winSeconds = other->winSeconds;
	score = other->score;
	previousPenaltyTime = other->previousPenaltyTime;
	resets = other->resets;
	holdOrigin = other->holdOrigin;
	undoState = other->undoState;
	numberOfUndos = other->numberOfUndos;
	options = other->options;

	holding = new TableauPile(other->holding);
	dealPile = new DealPile(other->dealPile);
	showingPile = new DealPile(other->showingPile);
	discardPile = new DealPile(other->discardPile);

	for (int i = 0; i < 4; ++i) {
		foundations[i] = new FoundationPile(other->foundations[i]);
	}
	for (int i = 0; i < 7; ++i) {
		tableau[i] = new Tableau(other->tableau[i]);
	}
}

Solitaire::Solitaire(GameOptions opt)
{
	holding = new TableauPile();
	resets = 0;
	undoState = nullptr;
	winSeconds = 0;
	firstMoveTimestamp = 0;
	previousPenaltyTime = 0;
	options = opt;

	for (int i = 0; i < 4; ++i) {
		foundations[i] = new FoundationPile();
	}

	score = opt.initialScore;

	//create the piles
	dealPile = new DealPile();
	showingPile = new DealPile();
	discardPile = new DealPile();

	seed = opt.useSeed ? opt.initialSeed : rand();
	dealPile->fill(seed);

	for (int i = 0; i < 7; ++i) {
		tableau[i] = new Tableau(i + 1, dealPile);
	}
}

void Solitaire::undo()
{
	//cannot undo if no moves have been made
	if (!canUndo()) {
		return;
	}

	//reload everything from the save state (deep copy not needed as we are throwing out undoState at the end)
	memcpy(tableau, undoState->tableau, sizeof(tableau));
	memcpy(foundations, undoState->foundations, sizeof(foundations));
	holding = undoState->holding;
	dealPile = undoState->dealPile;
	showingPile = undoState->showingPile;
	discardPile = undoState->discardPile;
	firstMoveTimestamp = undoState->firstMoveTimestamp;
	winSeconds = undoState->winSeconds;
	score = undoState->score;
	previousPenaltyTime = undoState->previousPenaltyTime;
	resets = undoState->resets;
	holdOrigin = undoState->holdOrigin;
	options = undoState->options;
	numberOfUndos = undoState->numberOfUndos + 1;

	//allows for infinite undos, but only if there is something to undo
	undoState = undoState == nullptr ? nullptr : undoState->undoState;
}


//save the game state so it can be undone later, and start the timer if needed
void Solitaire::preMove()
{
	undoState = new Solitaire(this);

	if (firstMoveTimestamp == 0) {
		printf("TODO: timestamp! Solitaire::preMove\n");
		//firstMoveTimestamp = System.currentTimeMillis();
	}
}

//adds (or subtracts) an amount from the score, ensuring the final
//score is not negative (unless playing in Vegas mode, where you can lose money)
void Solitaire::changeScore(int amount)
{
	//don't bother with the score if scoring is off
	if (options.scoring == ScoringMode::None) {
		return;
	}

	score += amount;

	//in standard mode, it cannot be negative (it can be in Vegas mode though)
	if (score < 0 && options.scoring == ScoringMode::Standard) {
		score = 0;
	}
}

//returns the score, and applies time penalties
int Solitaire::getScore()
{
	int time = getTime();

	//only standard mode has time penalties
	if (options.scoring == ScoringMode::Standard && options.timed) {
		//if it has been longer than 10 seconds since the last penalty
		//(loops in case it has been e.g. longer than 20 seconds)
		while (time - previousPenaltyTime >= 10) {
			changeScore(-2);					//apply penalty
			previousPenaltyTime += 10;			//adding 10 instead of setting to time ensures that this records the time where the previous penalty SHOULD
												//have been applied, even if it was applied later
		}
	}

	return score;
}

//if the game is in progress, return the seconds since the start, if it hasn't started, return zero, if it has been won,
//return the time the game took
int Solitaire::getTime()
{
	printf("TODO: timestamp! Solitaire::getTime\n");

	return 0;

	/*if (firstMoveTimestamp == 0) return 0;
	else if (winSeconds == 0) return (int) ((System.currentTimeMillis() - firstMoveTimestamp) / 1000);
	return winSeconds;*/
}


//check if the game has been won
bool Solitaire::isWon()
{
	//each foundation needs 13 cards (from ace to king) to win
	//so if any have less than 13, it is not a win
	for (int i = 0; i < 4; ++i) {
		if (foundations[i]->getHeight() != 13) {
			return false;
		}
	}
	return true;
}

bool Solitaire::canUndo()
{
	return undoState != nullptr;
}

void Solitaire::checkForWin()
{
	if (isWon() && winSeconds == 0) {
		//record time when win occured
		winSeconds = getTime();

		//time bonus is only applied in standard mode
		if (options.scoring == ScoringMode::Standard) {
			//add bonus points as described here: https://en.wikipedia.org/wiki/Klondike_(solitaire)
			//but with a new penalty for each undo
			if (winSeconds >= 30) {
				score += (20000 / winSeconds) * 35 / (numberOfUndos + 1);
			}
		}
	}
}


//pick up a pile of cards from a given pile ID
//numCards determines how many cards from the parent pile are grabbed (from the front)
void Solitaire::hold(int column, int numCards)
{
	preMove();

	//save where the cards came from in case the move is cancelled or illegal
	holdOrigin = column;

	if (column >= HAND_COLUMN_BASE) {
		//grab from the showing pile
		holding = new TableauPile(showingPile, 1);

	} else if (column >= FOUNDATION_COLUMN_BASE) {
		//grab from one of the foundations
		holding = new TableauPile(foundations[column - FOUNDATION_COLUMN_BASE], 1);

	} else {
		//otherwise it is a tableau
		holding = new TableauPile(tableau[column]->visiblePile, numCards);
	}
}

//forces cards to be released on a certain pile, even if under normal rules it wouldn't be allowed
//used to allow cards to return to their original positions if a move is cancelled or illegal
void Solitaire::forceRelease(int column)
{
	if (column >= HAND_COLUMN_BASE) {
		showingPile->forceAddPile(holding);

	} else if (column >= FOUNDATION_COLUMN_BASE) {
		foundations[column - FOUNDATION_COLUMN_BASE]->forceAddPile(holding);

	} else {
		tableau[column]->visiblePile->forceAddPile(holding);
	}
}

//releases the currently held cards onto a given pile
void Solitaire::release(int column)
{
	bool couldRelease = false;

	if (column >= HAND_COLUMN_BASE) {
		//you cannot put back into the hand
		couldRelease = false;

	} else if (column >= FOUNDATION_COLUMN_BASE) {
		couldRelease = foundations[column - FOUNDATION_COLUMN_BASE]->addPile(holding);

		//apply the scoring, only if it didn't come from the foundation (ie. it was already in the foundation and the user just clicked the card)
		if (couldRelease && (holdOrigin < FOUNDATION_COLUMN_BASE || holdOrigin >= HAND_COLUMN_BASE)) {
			if (options.scoring == ScoringMode::Standard) changeScore(10);
			else if (options.scoring == ScoringMode::Vegas) changeScore(5);
		}

	} else if (column != -1) {
		// ensure kings can only be moved to empty tableaus, not just empty piles
		if (holding->getBottomCard().rank == RANK_KING && tableau[column]->visiblePile->getHeight() == 0 && tableau[column]->hiddenPile->getHeight() != 0) {
			couldRelease = false;
		} else {
			couldRelease = tableau[column]->visiblePile->addPile(holding);
		}

		//apply scoring depending on where it comes from and the scoring mode
		if (couldRelease && holdOrigin == HAND_COLUMN_BASE && options.scoring == ScoringMode::Standard) {
			changeScore(5);
		} else if (couldRelease && holdOrigin == FOUNDATION_COLUMN_BASE) {
			if (options.scoring == ScoringMode::Standard) changeScore(-15);
			else if (options.scoring == ScoringMode::Vegas) changeScore(-5);
		}
	}

	if (!couldRelease) {
		//put the cards being held back where it came from if they were not placed on a valid pile
		forceRelease(holdOrigin);
	} else {
		//make a previously discarded cards visible if the showing pile is empty
		if (holdOrigin == HAND_COLUMN_BASE && showingPile->getHeight() == 0 && discardPile->getHeight() != 0) {
			showingPile->forceAddCard(discardPile->removeTopCard());
		}
	}

	//clear the holding pile
	holding = new TableauPile();

	//games can only be won on a card release, so check that here
	checkForWin();
}

//'recycles' all of the cards in the hand
//assumes that the showing pile is already cleared (ie. moved into the discard pile)
void Solitaire::resetHand()
{
	//move to the deal pile
	dealPile = discardPile;

	//clear the other ones
	showingPile = new DealPile();
	discardPile = new DealPile();

	resets++;

	//apply the points penalty in standard mode if needed
	if (options.scoring == ScoringMode::Standard) {
		if (options.draw3) {
			if (resets >= 4) changeScore(-20);
		} else {
			changeScore(-100);
		}
	}
}

//determines if you can reset the hand (on Vegas mode you can only do it a set number of times)
bool Solitaire::canFlipHand()
{
	return !(dealPile->getHeight() == 0 && options.scoring == ScoringMode::Vegas && resets == (options.draw3 ? 2 : 0));
}

//flips a card in the hand
void Solitaire::flipHand(int count)
{
	preMove();

	//ensure it is legal to do so
	if (!canFlipHand()) {
		return;
	}

	//we have now committed to turning the card

	//put everything that was showing in the discard pile
	while (showingPile->getHeight() != 0) {
		discardPile->forceAddCard(showingPile->removeBottomCard());
	}

	//reset/recycle the hand if needed (must be done after the above step)
	if (dealPile->getHeight() == 0) {
		resetHand();
		return;
	}

	//deal the cards
	for (int i = 0; i < count && dealPile->getHeight() != 0; ++i) {
		showingPile->forceAddCard(dealPile->removeBottomCard());
	}
}

//turn over a flipped over card in the tableau
void Solitaire::flipColumn(int column)
{
	preMove();

	//turn it over and add the ponts
	tableau[column]->flipOverCard();

	if (options.scoring == ScoringMode::Standard) {
		changeScore(5);
	}
}

extern "C" void __cxa_pure_virtual()
{

}