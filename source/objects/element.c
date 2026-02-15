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
    int mapDisplayWidth = gui->mapWidth * 2;
    int startY = gui->windowHeight / 2 - gui->mapHeight / 2;
    int startX = gui->windowWidth / 2 - mapDisplayWidth / 2;
    int leftBound = 1 - (gui->mapWidth / 2);

    struct Element* tmp = elementList;
    while (tmp != NULL) {
        int screenX = startX + (tmp->x - leftBound) * 2;
        int screenY = startY + tmp->y;
        chtype block = ' ' | COLOR_PAIR(tmp->color) | A_REVERSE;
        mvaddch(screenY, screenX, block);
        mvaddch(screenY, screenX + 1, block);
        tmp = tmp->next;
    }
}

void displayNextElementList(struct GUI* gui, struct Element* elementList) {
    int mapDisplayWidth = gui->mapWidth * 2;
    int startY = gui->windowHeight / 2 - gui->mapHeight / 2;
    int startX = gui->windowWidth / 2 + mapDisplayWidth / 2;
    
    struct Element* tmp = elementList;
    while (tmp != NULL) {
        int screenX = startX + (tmp->x) * 2 + 10;
        int screenY = startY + tmp->y + 2;
        chtype block = ' ' | COLOR_PAIR(tmp->color) | A_REVERSE;
        mvaddch(screenY - getElementListMaxHeight(elementList) / 2, screenX - getElementListMaxWidth(elementList) / 2, block);
        mvaddch(screenY - getElementListMaxHeight(elementList) / 2, screenX - getElementListMaxWidth(elementList) / 2 + 1, block);
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

int getElementListMaxWidth(struct Element* elementList) {
    if (elementList == NULL) {
        return 0;
    }
    int minX = elementList->x;
    int maxX = elementList->x;
    struct Element* tmp = elementList->next;
    while (tmp != NULL) {
        if (tmp->x < minX) {
            minX = tmp->x;
        }
        if (tmp->x > maxX) {
            maxX = tmp->x;
        }
        tmp = tmp->next;
    }
    return maxX - minX + 1;
}

int getElementListMaxHeight(struct Element* elementList) {
    if (elementList == NULL) {
        return 0;
    }
    int minY = elementList->y;
    int maxY = elementList->y;
    struct Element* tmp = elementList->next;
    while (tmp != NULL) {
        if (tmp->y < minY) {
            minY = tmp->y;
        }
        if (tmp->y > maxY) {
            maxY = tmp->y;
        }
        tmp = tmp->next;
    }
    return maxY - minY + 1;
}

static void drawRowElements(struct GUI* gui, struct Element* elementList, int* rows, int rowCount, int colorOverride) {
    int mapDisplayWidth = gui->mapWidth * 2;
    int startY = gui->windowHeight / 2 - gui->mapHeight / 2;
    int startX = gui->windowWidth / 2 - mapDisplayWidth / 2;
    int leftBound = 1 - (gui->mapWidth / 2);

    struct Element* tmp = elementList;
    while (tmp != NULL) {
        for (int i = 0; i < rowCount; i++) {
            if (tmp->y == rows[i]) {
                int screenX = startX + (tmp->x - leftBound) * 2;
                int screenY = startY + tmp->y;
                chtype block = colorOverride
                    ? (' ' | COLOR_PAIR(colorOverride))
                    : (' ' | COLOR_PAIR(tmp->color) | A_REVERSE);
                mvaddch(screenY, screenX, block);
                mvaddch(screenY, screenX + 1, block);
                break;
            }
        }
        tmp = tmp->next;
    }
}

static void flashRows(struct GUI* gui, struct Element* elementList, int* rows, int rowCount) {
    for (int flash = 0; flash < 3; flash++) {
        drawRowElements(gui, elementList, rows, rowCount, 8);
        refresh();
        napms(150);
        drawRowElements(gui, elementList, rows, rowCount, 0);
        refresh();
        napms(150);
    }
}

void flashAndDeleteRows(struct GUI* gui, struct Element** elementList) {
    int leftBound = 1 - (gui->mapWidth / 2);
    int rightBound = 1 + (gui->mapWidth / 2);
    int completeRows[gui->mapHeight];
    int completeRowCount = 0;
    for (int y = gui->mapHeight - 1; y >= 0; y--) {
        bool isComplete = true;
        for (int x = leftBound; x <= rightBound; x++) {
            if (!checkElementExist((*elementList), x, y)) {
                isComplete = false;
                break;
            }
        }
        if (isComplete) {
            completeRows[completeRowCount++] = y;
        }
    }

    if (completeRowCount == 0) {
        return;
    }

    // Flash the complete rows before deleting them
    flashRows(gui, *elementList, completeRows, completeRowCount);
    for (int i = 0; i < completeRowCount; i++) {
        deleteRow(elementList, completeRows[i]);
        moveRowsDown(elementList, completeRows[i]);
        // Rows above the deleted one shifted down, adjust remaining entries
        for (int j = i + 1; j < completeRowCount; j++) {
            completeRows[j]++;
        }
    }
}