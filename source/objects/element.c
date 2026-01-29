// Header files include //
#include "../../include/objects/element.h"

// STD include //
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>


struct Element* createElement(int x, int y, int color) {
    struct Element* new = malloc(sizeof(struct Element));
    if (!new) {
        return NULL;
    }
    new->x = x;
    new->y = y;
    new->color = color;
    new->next = NULL;
    return new;
}

void displayElementList(struct GUI* gui, struct Element* elementList) {
    struct Element* tmp = elementList;
    while (tmp != NULL) {
        attron(COLOR_PAIR(tmp->color));
        mvaddstr(gui->windowHeight / 2 - gui->mapHeight / 2 + tmp->y, gui->windowWidth / 2 - 1 + tmp->x, "■");
        attroff(COLOR_PAIR(tmp->color));
        tmp = tmp->next;
    }
}

void appendElement(struct Element** elementList, struct Element** newElement) {
    struct Element* tmp = (*elementList);
    // If the game element list is empty then we change the pointer 
    // to point to the new element to initialize it.
    if ((*elementList) == NULL) {
        (*elementList) = (*newElement);
        (*newElement) = NULL;
    } else {
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        // Append the element at the end.
        tmp->next = (*newElement);
        (*newElement) = NULL;
    }
}

void appendTetrominoElements(struct Element** elementList, struct Element** tetrominoElementList) {
    // If the game element list is empty then we change the pointer 
    // to point to the tetrimino element list to initialize it.
    if ((*elementList) == NULL) {
        (*elementList) = (*tetrominoElementList);
        (*tetrominoElementList) = NULL;
        return;
    } else {
        struct Element* tmp = (*elementList);
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        // Append the tetromino element list at the end and remove it from the tetromino.
        tmp->next = (*tetrominoElementList);
        (*tetrominoElementList) = NULL;
    }
}

void freeElementList(struct Element** elementList) {
    struct Element* tmp = NULL;
    // Iterate to free all the elements of the chained list.
    while (*elementList != NULL) {
        tmp = (*elementList);
        (*elementList) = (*elementList)->next;
        free(tmp);
    }
}

bool checkElementExist(struct Element* elementList, int x, int y) {
    struct Element* tmp = elementList;
    // Iterate through each element of the chained list to check if one
    // exists at the specified coordinates.
    while (tmp != NULL) {
        if (tmp->x == x && tmp->y == y) {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

void deleteRow(struct Element** elementList, int y) {
    struct Element* previous = NULL;
    struct Element* tmp = NULL;
    struct Element* current = (*elementList);
    while (current != NULL) {
        // Delete the row we want to delete.
        if (current->y == y) {
            // We change the head of the chain list if we need to delete it,
            // else, we delete the current node and update pointers.
            if (previous == NULL) {
                tmp = current;
                (*elementList) = (*elementList)->next;
                current = (*elementList);
            } else {
                tmp = current;
                current = current->next;
                previous->next = current;
            }
            free(tmp);
        } else {
            previous = current;
            current = current->next;
        }
    }
}

void moveRowsDown(struct Element** elementList, int y) {
    struct Element* tmp = (*elementList);
    while (tmp != NULL) {
        // Move rows above the deleted row down by 1 (increase y)
        if (tmp->y < y) {
            tmp->y++;
        }
        tmp = tmp->next;
    }
}

void checkRow(struct GUI* gui, struct Element** elementList) {
    int leftBound = 1 - (gui->mapWidth / 2);
    int rightBound = 1 + (gui->mapWidth / 2);
    for (int y = gui->mapHeight - 1; y >= 0; y--) {
        bool shouldDeleteRow = true;
        for (int x = leftBound; x <= rightBound; x++) {
            if (!checkElementExist((*elementList), x, y)) {
                shouldDeleteRow = false;
                break;
            }
        }
        if (shouldDeleteRow) {
            deleteRow(&(*elementList), y);
            moveRowsDown(&(*elementList), y);
            // Re-check the same y after shifting above rows down
            y++;
        }
    }
}