#pragma once

#define FOUNDATION_COLUMN_BASE	7
#define HAND_COLUMN_BASE		11
#define DRAW_PILE_BASE		12

enum class ScoringMode
{
	Standard,
	Vegas,
	None
};

class GameOptions
{
public:
	ScoringMode scoring;
	bool timed;
	bool draw3;
	bool cumulative;

	int initialScore;
	int initialSeed;
	bool useSeed;

	GameOptions()
	{
		scoring = ScoringMode::Standard;
		timed = true;
		draw3 = true;
		cumulative = true;

		initialScore = 0;
		initialSeed = 0;
		useSeed = false;
	}

	void setInitialScore(int currentScore)
	{
		if (scoring == ScoringMode::Vegas) {
			initialScore = cumulative ? currentScore - 52 : -52;
		} else {
			initialScore = 0;
		}
	}
};

#include "TableauPile.hpp"
#include "Tableau.hpp"
#include "Card.hpp"
#include "DealPile.hpp"
#include "FoundationPile.hpp"

class Solitaire
{
public:
	GameOptions options;
	Tableau* tableau[7];
	TableauPile* holding;
	DealPile* dealPile;
	DealPile* showingPile;
	DealPile* discardPile;
	FoundationPile* foundations[4];

	long long int firstMoveTimestamp = 0;
	int winSeconds = 0;
	int score = 0;
	int previousPenaltyTime = 0;
	int resets = 0;
	int holdOrigin;
	int numberOfUndos = 0;
	int seed = 0;

	Solitaire* undoState;

	Solitaire(Solitaire* other);
	Solitaire(GameOptions opt);

	void undo();
	void preMove();
	void changeScore(int amount);
	int getScore();
	int getTime();
	bool isWon();
	bool canUndo();
	void checkForWin();
	void hold(int column, int numCards);
	void forceRelease(int column);
	void release(int column);
	void resetHand();
	bool canFlipHand();
	void flipHand(int count);
	void flipColumn(int column);
};