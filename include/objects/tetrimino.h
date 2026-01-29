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
void createHeroTetrimino(struct Tetrimino** tetrimino, int color);
void createSmashBoyTetrimino(struct Tetrimino** tetrimino, int color);
void createClevelandTetrimino(struct Tetrimino** tetrimino, int color);
void createRhodeIslandTetrimino(struct Tetrimino** tetrimino, int color);
void createBlueRickytetrimino(struct Tetrimino** tetrimino, int color);
void createOrangeRickytetrimino(struct Tetrimino** tetrimino, int color);
void createTeeweeTetrimino(struct Tetrimino** tetrimino, int color);
void moveTetrimino(struct Tetrimino* tetrimino, int x, int y);
void rotateTetrimino(struct Tetrimino* tetrimino);
void freeTetrimino(struct Tetrimino** tetrimino);


