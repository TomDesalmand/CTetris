// Header files include //
#include "../../include/objects/tetrimino.h"

// STD include //
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void createTetriminoFromFile(struct Tetrimino** tetrimino, const char* asset_path, int color) {
    FILE *file; 
    char buffer[256]; 
    int row = 0;
    int max_cols = 0;
    if (!asset_path || (file = fopen(asset_path, "r")) == NULL) {
        return;
    }
    if ((*tetrimino) == NULL) {
        (*tetrimino) = malloc(sizeof(struct Tetrimino));
        if (!(*tetrimino)) {
            fclose(file);
            return;
        }
        (*tetrimino)->width = 0;
        (*tetrimino)->height = 0;
    } else {
        freeElementList(&(*tetrimino)->elementList);
        (*tetrimino)->width = 0;
        (*tetrimino)->height = 0;
    }
    (*tetrimino)->color = color; 
    (*tetrimino)->elementList = NULL;
    while (fgets(buffer, sizeof buffer, file)) {
        size_t n = strcspn(buffer, "\r\n");
        buffer[n] = '\0';
        size_t line_len = strlen(buffer);
        if ((int)line_len > max_cols) {
            max_cols = (int)line_len;
        }
        for (size_t charaterPosition = 0; buffer[charaterPosition]; ++charaterPosition) {
            if (buffer[charaterPosition] == '+') {
                struct Element *element = createElement((int)charaterPosition, row, color);
                if (!element) {
                    freeTetrimino(&(*tetrimino));
                    fclose(file);
                    return;
                }
                appendElement(&(*tetrimino)->elementList, &element);
            }
        }
        ++row;
    }
    (*tetrimino)->width = max_cols;
    (*tetrimino)->height = row;
    fclose(file);
}

static void getBounds(const struct GUI* gui, int* leftBound, int* rightBound) {
    *leftBound = 1 - (gui->mapWidth / 2);
    *rightBound = 1 + (gui->mapWidth / 2);
}

static void getMinimumXY(const struct Tetrimino* tetrimino, int* min_x, int* min_y) {
    struct Element* tmp = tetrimino->elementList;
    *min_x = tmp->x;
    *min_y = tmp->y;
    while (tmp != NULL) {
        if (tmp->x < *min_x) *min_x = tmp->x;
        if (tmp->y < *min_y) *min_y = tmp->y;
        tmp = tmp->next;
    }
}

static int canTranslate(const struct GUI* gui, const struct Element* elementList, const struct Tetrimino* tetrimino, int dx, int dy) {
    int leftBound, rightBound;
    getBounds(gui, &leftBound, &rightBound);
    struct Element* tmp = tetrimino->elementList;
    while (tmp != NULL) {
        int nx = tmp->x + dx;
        int ny = tmp->y + dy;
        if (nx < leftBound || nx > rightBound || ny < 0 || ny >= gui->mapHeight) {
            return 0;
        }
        // Prevent moving into existing elements on the board
        if (checkElementExist((struct Element*)elementList, nx, ny)) {
            return 0;
        }
        tmp = tmp->next;
    }
    return 1;
}

static void applyTranslate(struct Tetrimino* tetrimino, int dx, int dy) {
    struct Element* tmp = tetrimino->elementList;
    while (tmp != NULL) {
        tmp->x += dx;
        tmp->y += dy;
        tmp = tmp->next;
    }
}

static int computeRotationCheck(const struct GUI* gui, const struct Element* elementList, const struct Tetrimino* tetrimino, int min_x, int min_y, int old_w, int* out_dy) {
    int rotated_min_y = INT_MAX;
    struct Element* tmp = tetrimino->elementList;
    while (tmp != NULL) {
        int local_x = tmp->x - min_x;
        int local_y = tmp->y - min_y;
        int new_local_y = old_w - 1 - local_x;
        int ry = min_y + new_local_y;
        if (ry < rotated_min_y) rotated_min_y = ry;
        tmp = tmp->next;
    }
    int dy = min_y - rotated_min_y;
    int leftBound, rightBound;
    getBounds(gui, &leftBound, &rightBound);
    tmp = tetrimino->elementList;
    while (tmp != NULL) {
        int local_x = tmp->x - min_x;
        int local_y = tmp->y - min_y;
        int rx = min_x + local_y;
        int ry = min_y + old_w - 1 - local_x + dy;
        if (rx < leftBound || rx > rightBound || ry < 0 || ry >= gui->mapHeight) {
            return 0;
        }
        // Prevent rotating into existing elements on the board
        if (checkElementExist((struct Element*)elementList, rx, ry)) {
            return 0;
        }
        tmp = tmp->next;
    }
    *out_dy = dy;
    return 1;
}

static void applyRotation(struct Tetrimino* tetrimino, int min_x, int min_y, int old_w, int dy) {
    struct Element* tmp = tetrimino->elementList;
    while (tmp != NULL) {
        int local_x = tmp->x - min_x;
        int local_y = tmp->y - min_y;
        int new_local_x = local_y;
        int new_local_y = old_w - 1 - local_x;
        tmp->x = min_x + new_local_x;
        tmp->y = min_y + new_local_y + dy;
        tmp = tmp->next;
    }
}

void rotateTetrimino(struct GUI* gui, struct Element* elementList, struct Tetrimino* tetrimino) {
    if (!tetrimino || !gui) {
        return;
    }
    int min_x, min_y;
    getMinimumXY(tetrimino, &min_x, &min_y);
    int old_w = tetrimino->width;
    int old_h = tetrimino->height;
    int dy = 0;
    if (!computeRotationCheck(gui, elementList, tetrimino, min_x, min_y, old_w, &dy)) {
        return;
    }
    applyRotation(tetrimino, min_x, min_y, old_w, dy);
    tetrimino->width = old_h;
    tetrimino->height = old_w;
}

void moveTetrimino(struct GUI* gui, struct Element* elementList, struct Tetrimino *tetrimino, int x, int y) {
    if (!tetrimino || !gui) {
        return;
    }
    if (!canTranslate(gui, elementList, tetrimino, x, y)) {
        return;
    }
    applyTranslate(tetrimino, x, y);
}

void freeTetrimino(struct Tetrimino** tetrimino) {
    if (!(*tetrimino)) {
        return;
    }
    freeElementList(&(*tetrimino)->elementList);
    free(*tetrimino);
    (*tetrimino) = NULL;
}

void checkPlaceTetrimino(struct GUI* gui, struct Element** elementList, struct Tetrimino** tetrimino) {
    struct Element* tmp = (*tetrimino)->elementList;
    while (tmp != NULL) {
        if (tmp->y + 1 == gui->mapHeight || checkElementExist((*elementList), tmp->x, tmp->y + 1)) {
            appendTetrominoElements(&(*elementList), &(*tetrimino)->elementList);
            checkRow(&(*gui), &(*elementList));
            createRandomTetrimino(&(*tetrimino));
            return;
        }
        tmp = tmp->next;
    }
}

void createRandomTetrimino(struct Tetrimino** tetrimino) {
    size_t count = sizeof(PIECES) / sizeof(PIECES[0]);
    uint32_t index = arc4random_uniform((uint32_t)count);
    const PieceDef def = PIECES[index];
    createTetriminoFromFile(&(*tetrimino), def.asset, def.color_pair);
}
