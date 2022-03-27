
#pragma once

#include "solitaire.hpp"
#include <udraw/banana.hpp>

#define CARD_WIDTH 105
#define CARD_HEIGHT 150
#define CARD_BORDER 6
#define DRAW_Y_POS 50
#define TABLEAU_Y_POS 230
#define FOUNDATION_Y_POS DRAW_Y_POS
#define TABLEAU_Y_DISTANCE 22
#define DEAL_3_SHIFT_DIST 35


class CardClickInfo
{
public:
    int tableau;
    int cards;
    int cardX;
    int cardY;

    CardClickInfo(int _t, int _c, int _x, int _y)
    {
        tableau = _t;
        cards = _c;
        cardX = _x;
        cardY = _y;
    }
};

class GUI : public NTopLevel
{
public:

    int WINDOW_WIDTH = 1000;
    int WINDOW_HEIGHT = 700;
    int DRAW_X_POS = 25;
    int TABLEAU_X_POS = 25;
    int TABLEAU_DISTANCE = 137;
    int FOUNDATION_X_POS = 25 + 3 * 137;

    int recentMouseX;
    int recentMouseY;
    int recentCardX;
    int recentCardY;

    GameOptions options;

    Solitaire* game = nullptr;

    GUI();

    void drawBackOfCard(Context* g, int x, int y);
    void drawCard(Context* g, int x, int y, Card card);
    void paintHand(Context* g);
    void paintTableau(Context* g);
    void paintFoundations(Context* g);
    void paintHolding(Context* g);
    void paintStatusBar(Context* g);
    void rerender();
    void recomputeDistances(int w, int h);
    void start(GameOptions opt);
    void startFromSeed(int seed);
    CardClickInfo detectMousePosition(int x, int y);
    void mouseDown(NiEvent evnt);
    void mouseDragged(NiEvent evnt);
    void mouseUp(NiEvent evnt);
};