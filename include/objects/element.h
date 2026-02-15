#pragma once

// Header files include //
#include "../../include/gui/gui.h"

// STD include //
#include <stdbool.h>

// This header defines a struct that will allow to access all the elements in the game.
struct Element {
    int x;
    int y;
    int color;
    struct Element* next;
};

struct Element* createElement(int x, int y, int color);
void displayElementList(struct GUI* gui, struct Element* elementList);
void displayNextElementList(struct GUI* gui, struct Element* elementList);
void appendElement(struct Element** elementList, struct Element** newElement);
void appendTetrominoElements(struct Element** elementList, struct Element** tetrominoElementList);
void freeElementList(struct Element** elementList);
bool checkElementExist(struct Element* elementList, int x, int y);
void deleteRow(struct Element** elementList, int y);
void moveRowsDown(struct Element** elementList, int y);
void flashAndDeleteRows(struct GUI* gui, struct Element** elementList);
int getElementListMaxWidth(struct Element* elementList);
int getElementListMaxHeight(struct Element* elementList);