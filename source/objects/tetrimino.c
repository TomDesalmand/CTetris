// Header files include //
#include "../../include/objects/tetrimino.h"

// STD include //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            if (buffer[charaterPosition] == '*') {
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

void createHeroTetrimino(struct Tetrimino** tetrimino, int color) {
    createTetriminoFromFile(&(*tetrimino), "assets/hero.tetrimino", color);
}

void createSmashBoyTetrimino(struct Tetrimino** tetrimino, int color) {
    createTetriminoFromFile(&(*tetrimino), "assets/smashboy.tetrimino", color);
}

void createClevelandTetrimino(struct Tetrimino** tetrimino, int color) {
    createTetriminoFromFile(&(*tetrimino), "assets/cleveland.tetrimino", color);
}

void createRhodeIslandTetrimino(struct Tetrimino** tetrimino, int color) {
    createTetriminoFromFile(&(*tetrimino), "assets/rhode_island.tetrimino", color);
}

void createBlueRickytetrimino(struct Tetrimino** tetrimino, int color) {
    createTetriminoFromFile(&(*tetrimino), "assets/blue_rickytetrimino.tetrimino", color);
}

void createOrangeRickytetrimino(struct Tetrimino** tetrimino, int color) {
    createTetriminoFromFile(&(*tetrimino), "assets/orange_rickytetrimino.tetrimino", color);
}

void createTeeweeTetrimino(struct Tetrimino** tetrimino, int color) {
    createTetriminoFromFile(&(*tetrimino), "assets/teewee.tetrimino", color);
}

void rotateTetrimino(struct Tetrimino* tetrimino) {
    if (!tetrimino || !tetrimino->elementList) {
        return;
    }
    // Get the top left coordinates of the tetrimino.
    int min_x = tetrimino->elementList->x;
    int min_y = tetrimino->elementList->y;
    struct Element* tmp = tetrimino->elementList;
    while (tmp != NULL) {
        if (tmp->x < min_x) {
            min_x = tmp->x;
        }
        if (tmp->y < min_y) { 
            min_y = tmp->y;
        }
        tmp = tmp->next;
    }
    int old_size_x = tetrimino->width;
    int old_size_y = tetrimino->height;
    tmp = tetrimino->elementList;
    while (tmp != NULL) {
        // Convert to local coordinates (relative to top-left corner)
        int local_x = tmp->x - min_x;
        int local_y = tmp->y - min_y;
        // 90 degree clockwise rotation: (x, y) -> (y, width-1-x)
        int new_local_x = local_y;
        int new_local_y = old_size_x - 1 - local_x;
        // Convert back to absolute coordinates
        tmp->x = min_x + new_local_x;
        tmp->y = min_y + new_local_y;
        tmp = tmp->next;
    }
    // Exchange both sizes to correspond to the new size of each.
    tetrimino->width = old_size_y;
    tetrimino->height = old_size_x;
}

void moveTetrimino(struct Tetrimino *tetrimino, int x, int y) {
    if (!tetrimino) {
        return;
    }
    struct Element* tmp = tetrimino->elementList;
    while (tmp != NULL) {
        tmp->x += x;
        tmp->y += y;
        tmp = tmp->next;
    }
}

void freeTetrimino(struct Tetrimino** tetrimino) {
    if (!(*tetrimino)) {
        return;
    }
    freeElementList(&(*tetrimino)->elementList);
    free(*tetrimino);
    (*tetrimino) = NULL;
}