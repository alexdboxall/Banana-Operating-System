
#include <stdio.h>
#include <string.h>
#include <time.h>
extern "C" {
    #include <unistd.h>
    #include <dirent.h>
}

#include "gui.hpp"


GUI::GUI() : NTopLevel("Solitaire", 1000, 700, WIN_FLAGS_DEFAULT_0 | WIN_FLAGS_0_HIDDEN | WIN_FLAGS_0_PRETTY | WIN_FLAGS_0_NO_RESIZE)
{
	game = nullptr;

	// TODO: ...

	game = new Solitaire(GameOptions());
}   

void GUI::drawBackOfCard(Context* g, int x, int y)
{
	Context_fill_rect(g, x, y, CARD_WIDTH, CARD_HEIGHT, 0xFFFFFF);
	Context_draw_rect(g, x, y, CARD_WIDTH - 1, CARD_HEIGHT - 1, 0x000000);
	Context_fill_rect(g, x + CARD_BORDER, y + CARD_BORDER, CARD_WIDTH - 2 * CARD_BORDER, CARD_HEIGHT - 2 * CARD_BORDER, 0x0040C0);

	//g2.setPaint(cardBackPaint);
	//g2.fillRect(x + CARD_BORDER * 2, y + CARD_BORDER * 2, CARD_WIDTH - 4 * CARD_BORDER, CARD_HEIGHT - 4 * CARD_BORDER);
}

void GUI::drawCard(Context* g, int x, int y, Card card)
{
	Context_fill_rect(g, x, y, CARD_WIDTH, CARD_HEIGHT, 0xFFFFFF);
	Context_draw_rect(g,x, y, CARD_WIDTH - 1, CARD_HEIGHT - 1, 0x000000);

	char rank[8];
	if (card.rank == RANK_ACE) strcpy(rank, "A");
	else if (card.rank == RANK_JACK) strcpy(rank, "J");
	else if (card.rank == RANK_QUEEN) strcpy(rank, "Q");
	else if (card.rank == RANK_KING) strcpy(rank, "K");
	else sprintf(rank, "%d", card.rank);

	Context_draw_text(g, rank, x + 5, y + 5, card.isBlack() ? 0x000000 : 0xFF0000);
}

void GUI::paintHand(Context* g)
{
	int dealCards = game->dealPile->getHeight();

	if (dealCards == 0) {
		if (game->canFlipHand()) {

			/*g.setColor(new Color(0x00FF00));
			g.fillOval(DRAW_X_POS + CARD_WIDTH / 8, DRAW_Y_POS + (CARD_HEIGHT - CARD_WIDTH) / 2 + CARD_WIDTH / 8, CARD_WIDTH * 6 / 8, CARD_WIDTH * 6 / 8);
			g.setColor(new Color(0x008000));
			g.fillOval(DRAW_X_POS + CARD_WIDTH / 6, DRAW_Y_POS + (CARD_HEIGHT - CARD_WIDTH) / 2 + CARD_WIDTH / 6, CARD_WIDTH * 4 / 6, CARD_WIDTH * 4 / 6);
			*/
		} else {
			/*Graphics2D g2 = (Graphics2D) g;
			g2.setColor(new Color(0xFF0000));
			g2.setStroke(new BasicStroke(5));
			g2.drawLine(DRAW_X_POS + CARD_WIDTH / 8, DRAW_Y_POS + (CARD_HEIGHT - CARD_WIDTH) / 2 + CARD_WIDTH / 8, DRAW_X_POS + CARD_WIDTH * 7 / 8, DRAW_Y_POS + (CARD_HEIGHT - CARD_WIDTH) / 2 + CARD_WIDTH * 7 / 8);
			g2.drawLine(DRAW_X_POS + CARD_WIDTH / 8, DRAW_Y_POS + (CARD_HEIGHT - CARD_WIDTH) / 2 + CARD_WIDTH * 7 / 8, DRAW_X_POS + CARD_WIDTH * 7 / 8, DRAW_Y_POS + (CARD_HEIGHT - CARD_WIDTH) / 2 + CARD_WIDTH / 8);
			g2.setStroke(new BasicStroke(1));*/
		}

	} else {
		for (int i = 0; i < dealCards / 8 + 1; ++i) {
			drawBackOfCard(g, DRAW_X_POS + 2 * i, DRAW_Y_POS + i);
		}
	}

	int shown = game->showingPile->getHeight() + game->discardPile->getHeight();

	if (shown != 0) {
		int xpos = DRAW_X_POS + TABLEAU_DISTANCE;
		int ypos = DRAW_Y_POS;
		int i = 0;


		for (int j = game->discardPile->numCards - 1; j > -1; --j) {
			Card card = game->discardPile->cards[j];
			drawCard(g, xpos, ypos, card);

			if (i % 8 == 7) {
				xpos += 2;
				ypos += 1;
			}
			++i;
		}

		for (int j = game->showingPile->numCards - 1; j > -1; --j) {
			Card card = game->showingPile->cards[j];
			drawCard(g, xpos, ypos, card);
			xpos += 28;
		}
	}
}

void GUI::paintTableau(Context* g)
{
	for (int t = 0; t < 7; ++t) {
		int ypos = TABLEAU_Y_POS;
		for (int i = 0; i < game->tableau[t]->hiddenPile->numCards; ++i) {
			drawBackOfCard(g, TABLEAU_X_POS + t * TABLEAU_DISTANCE, ypos);
			ypos += TABLEAU_Y_DISTANCE;
		}

		for (int i = game->tableau[t]->visiblePile->numCards - 1; i > -1; --i) {
			Card card = game->tableau[t]->visiblePile->cards[i];
			drawCard(g, TABLEAU_X_POS + t * TABLEAU_DISTANCE, ypos, card);
			ypos += TABLEAU_Y_DISTANCE;
		}
	}
}

void GUI::paintFoundations(Context* g)
{
	for (int i = 0; i < 4; ++i) {
		Context_draw_rect(g, FOUNDATION_X_POS + i * TABLEAU_DISTANCE, FOUNDATION_Y_POS, CARD_WIDTH, CARD_HEIGHT, 0x000000);

		if (game->foundations[i]->getHeight() != 0) {
			drawCard(g, FOUNDATION_X_POS + i * TABLEAU_DISTANCE, FOUNDATION_Y_POS, game->foundations[i]->getTopCard());
		}
	}

}

void GUI::paintHolding(Context* g)
{
	if (game->holding->getHeight() == 0) {
		return;
	}

	int ypos = recentMouseY + recentCardY;

	for (int i = game->holding->numCards - 1; i > -1; --i) {
		Card card = game->holding->cards[i];
		drawCard(g, recentMouseX + recentCardX, ypos, card);
		ypos += 15;
	}
}

void GUI::paintStatusBar(Context* g)
{
    Context_fill_rect(g, 0, WINDOW_HEIGHT - 27, WINDOW_WIDTH, 27, 0xFFFFFF);

	char timeString[256];
	sprintf(timeString, "Time: %d", game->getTime());

}

void GUI::rerender()
{
    Context* g = getContext();

    Context_fill_rect(g, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0x008000);

    paintHand(g);
    paintTableau(g);
    paintFoundations(g);
    paintHolding(g);
    paintStatusBar(g);

    if (game->isWon()) {
        Context_draw_text(g, "YOU WINNED!", WINDOW_WIDTH / 2 - 131, WINDOW_HEIGHT / 2, 0x000000);
    }
}

void GUI::recomputeDistances(int w, int h)
{
	WINDOW_WIDTH = w;
	WINDOW_HEIGHT = h;
	TABLEAU_DISTANCE = WINDOW_WIDTH * 138 / 1000;
	if (TABLEAU_DISTANCE <= CARD_WIDTH) {
		TABLEAU_DISTANCE = CARD_WIDTH + 1;
	}
	DRAW_X_POS = (WINDOW_WIDTH - 6 * TABLEAU_DISTANCE - CARD_WIDTH) / 2;
	TABLEAU_X_POS = DRAW_X_POS;
	FOUNDATION_X_POS = TABLEAU_X_POS + 3 * TABLEAU_DISTANCE;
}

void GUI::start(GameOptions opt)
{
	opt.setInitialScore(game->score);
	game = new Solitaire(opt);
	opt.useSeed = false;
	repaint();
}

void GUI::startFromSeed(int seed)
{
	GameOptions opt = game->options;
	opt.useSeed = true;
	opt.initialSeed = seed;
	opt.setInitialScore(game->score);

	if (opt.cumulative && opt.scoring == ScoringMode::Vegas) {
		opt.initialScore = game->score;
	}

	start(opt);
}

CardClickInfo GUI::detectMousePosition(int x, int y)
{
	int tableau = -1;
	int cards = 0;
	int cardX = 0;
	int cardY = 0;

	if (y >= FOUNDATION_Y_POS && y <= FOUNDATION_Y_POS + CARD_HEIGHT) {
		if (x >= FOUNDATION_X_POS && ((x - FOUNDATION_X_POS) % TABLEAU_DISTANCE) < CARD_WIDTH) {
			cards = 1;
			tableau = FOUNDATION_COLUMN_BASE + ((x - FOUNDATION_X_POS) / TABLEAU_DISTANCE);
			cardX = FOUNDATION_X_POS + ((x - FOUNDATION_X_POS) / TABLEAU_DISTANCE) * TABLEAU_DISTANCE;
			cardY = FOUNDATION_Y_POS;
		}
	}

	int draw3Shift = game->options.draw3 ? DEAL_3_SHIFT_DIST * (game->showingPile->getHeight() - 1) : 0;
	if (y >= DRAW_Y_POS && y <= DRAW_Y_POS + CARD_HEIGHT + game->dealPile->getHeight() / 8) {
		if (x >= DRAW_X_POS && x <= DRAW_X_POS + CARD_WIDTH + game->dealPile->getHeight() / 4) {
			cards = 1;
			tableau = DRAW_PILE_BASE;
			cardX = DRAW_X_POS;
			cardY = DRAW_Y_POS;
		}
		if (x >= DRAW_X_POS + TABLEAU_DISTANCE + draw3Shift && x <= DRAW_X_POS + TABLEAU_DISTANCE + CARD_WIDTH + draw3Shift + game->discardPile->getHeight() / 4) {
			cards = 1;
			tableau = HAND_COLUMN_BASE;
			cardX = DRAW_X_POS + TABLEAU_DISTANCE + draw3Shift;
			cardY = DRAW_Y_POS;
		}
	}

	if (y >= TABLEAU_Y_POS) {
		if (x >= TABLEAU_X_POS && ((x - TABLEAU_X_POS) % TABLEAU_DISTANCE) < CARD_WIDTH) {
			tableau = ((x - TABLEAU_X_POS) / TABLEAU_DISTANCE);
			if (tableau < 7) {
				int hidden = game->tableau[tableau]->hiddenPile->getHeight();

				int cardsIn = (y - TABLEAU_Y_POS) / TABLEAU_Y_DISTANCE;

				if (cardsIn - hidden >= 0) {
					cards = game->tableau[tableau]->visiblePile->getHeight() + hidden - cardsIn;
					if (cards < 1) {
						cards = 1;
						cardsIn = game->tableau[tableau]->visiblePile->getHeight() + hidden;
					}
					cardX = TABLEAU_X_POS + ((x - TABLEAU_X_POS) / TABLEAU_DISTANCE) * TABLEAU_DISTANCE;
					cardY = TABLEAU_Y_POS + cardsIn * TABLEAU_Y_DISTANCE;

				} else {
					tableau = -1;
				}
			} else {
				tableau = -1;
			}
		}
	}

	return CardClickInfo(tableau, cards, cardX, cardY);
}

void GUI::mouseDown(NiEvent evnt)
{
	if (game->isWon()) {
		return;
	}

	recentMouseX = evnt.mouseX - x;
	recentMouseY = evnt.mouseY - y;

	CardClickInfo clickInfo = detectMousePosition(recentMouseX, recentMouseY);

	if (clickInfo.tableau == DRAW_PILE_BASE) {
		game->flipHand(game->options.draw3 ? 3 : 1);
		repaint();

	} else if (clickInfo.tableau != -1 && game->holding->getHeight() == 0) {

		if (clickInfo.tableau < 7) {
			Tableau* tab = game->tableau[clickInfo.tableau];
			if (tab->visiblePile->getHeight() == 0 && tab->hiddenPile->getHeight() != 0) {
				game->flipColumn(clickInfo.tableau);
				repaint();
				return;
			}
		}

		game->hold(clickInfo.tableau, clickInfo.cards);
		recentCardX = clickInfo.cardX - recentMouseX;
		recentCardY = clickInfo.cardY - recentMouseY;
		repaint();
	}
}

int mouseDeltaX = 0;
int mouseDeltaY = 0;

int count = 0;
void GUI::mouseDragged(NiEvent evnt)
{
	if (game->holding->getHeight() == 0) {
		return;
	}

	int xChange = recentMouseX - (evnt.mouseX - x);
	if (xChange < 0) xChange = -xChange;
	int yChange = recentMouseY - (evnt.mouseY - y);
	if (yChange < 0) yChange = -yChange;

	mouseDeltaX += xChange;
	mouseDeltaY += yChange;

	recentMouseX = evnt.mouseX - x;
	recentMouseY = evnt.mouseY - y;

	if (++count > 8) {
		repaint();
		count = 0;
	}
}

void GUI::mouseUp(NiEvent evnt)
{
	mouseDeltaX = 0;
	mouseDeltaY = 0;

	CardClickInfo clickInfo = detectMousePosition(recentMouseX, recentMouseY);

	if (game->holding->getHeight() != 0) {
		game->release(clickInfo.tableau);
		repaint();
	}
}

int paintGUIThunk(NTopLevel* object)
{
    ((GUI*) object)->rerender();
    return 0;
}

extern "C" int main() {
    createSystemBrushes();

	time_t t;
	srand((unsigned) time(&t));

    GUI* gui = new GUI();

    NLoadedBitmap* bmp = new NLoadedBitmap("C:/Banana/Icons/solitaire.tga");
    gui->paintHandlerHook = paintGUIThunk;
    gui->setIcon(bmp);
    gui->initialise();

    while (1) {
		NiEvent evnt = gui->process();

		switch (evnt.type) {
		case EVENT_TYPE_MOUSE_DOWN:
			gui->mouseDown(evnt);
			gui->defaultEventHandler(evnt);
			break;
		case EVENT_TYPE_MOUSE_UP:
			gui->mouseUp(evnt);
			gui->defaultEventHandler(evnt);
			break;
		case EVENT_TYPE_MOUSE_DRAG:
			gui->mouseDragged(evnt);
			gui->defaultEventHandler(evnt);
			break;
		default:
			gui->defaultEventHandler(evnt);
			break;
		}
    }
    
    return 0;
}

