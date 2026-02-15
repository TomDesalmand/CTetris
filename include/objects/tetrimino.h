#pragma once

// Header files
#include "element.h"

// Defines the Tetrimino and its associated Elements.
struct Tetrimino {
    int width;
    int height;
    int color;
    struct Element* elementList;
};

typedef struct {
    const char* asset;
    int color_pair;
} PieceDef;

static const PieceDef PIECES[] = {
    { "assets/hero.tetrimino",         6 },
    { "assets/smashboy.tetrimino",     1 },
    { "assets/cleveland.tetrimino",    2 },
    { "assets/rhode_island.tetrimino", 3 },
    { "assets/blue_ricky.tetrimino",   4 },
    { "assets/orange_ricky.tetrimino", 7 },
    { "assets/teewee.tetrimino",       5 },
};

bool checkPlaceTetrimino(struct GUI* gui, struct Element** elementList, struct Tetrimino** tetrimino, struct Tetrimino** nexTetrimino);
void createTetriminoFromFile(struct Tetrimino** tetrimino, const char* asset_path, int color);
void createRandomTetrimino(struct Tetrimino** tetrimino);
void moveTetrimino(struct GUI* gui, struct Element* elementList, struct Tetrimino *tetrimino, int x, int y);
void rotateTetrimino(struct GUI* gui, struct Element* elementList, struct Tetrimino* tetrimino);
void freeTetrimino(struct Tetrimino** tetrimino);
