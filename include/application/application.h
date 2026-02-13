#pragma once

// Header files include //
#include "../objects/element.h"
#include "../objects/tetrimino.h"
#include "../gui/gui.h"

// NCURSE include //
#include <ncurses.h>

// STD include //
#include <stdbool.h>

// Movement keys //
#define ROTATE 32 // spacebar //
// GUI keys //
#define QUIT 113 // q //

struct Application {
    struct GUI* gui;
    struct Element* elementList;
    struct Tetrimino* tetrimino;
    int level;
};

// Application
void initApplication(void);
bool initApplicationStructures(struct Application** application);
void initColor(void);
bool handleInputs(struct Application** application);
void run(struct Application** application);
void endApplication(void);
void freeApplicationStructures(struct Application** application);