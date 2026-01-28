#pragma once

// Header files include //
#include "../objects/element.h"
#include "../objects/tetrimino.h"

// NCURSE include //
#include <ncurses.h>

// STD include //
#include <stdbool.h>

// Movement keys //
#define UP 119 // w //
#define DOWN 115 // s //
#define LEFT 97 // a //
#define RIGHT 100 // d //
#define ROTATE 32 // spacebar //
// GUI keys //
#define QUIT 113 // q //

// GUI sizes //
#define HEIGHT 25
#define WIDTH 15

struct Application {
    struct Element* elementList;
    struct Tetrimino* tetrimino;
};

// Application
void initApplication(void);
bool initApplicationStructures(struct Application** application);
void initColor(void);
void run(struct Application** application);
void endApplication(void);
void freeApplicationStructures(struct Application** application);

// GUI
void displayMap();