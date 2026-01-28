#pragma once

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
void displayElementList(struct Element* elementList);
void appendElement(struct Element** elementList, struct Element** newElement);
void appendTetrominoElements(struct Element** elementList, struct Element** tetrominoElementList);
void freeElementList(struct Element** elementList);
bool checkElementExist(struct Element* elementList, int x, int y);
void deleteRow(struct Element** elementList, int y);