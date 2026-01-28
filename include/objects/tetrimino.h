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

void createTetriminoFromFile(struct Tetrimino** tetrimino, const char* asset_path, int color);
void createBarTetrimino(struct Tetrimino** tetrimino, int color);
void createSquareTetrimino(struct Tetrimino** tetrimino, int color);
void createLightningTetrimino(struct Tetrimino** tetrimino, int color);
void moveTetrimino(struct Tetrimino* tetrimino, int x, int y);
void rotateTetrimino(struct Tetrimino* tetrimino);
void freeTetrimino(struct Tetrimino** tetrimino);


