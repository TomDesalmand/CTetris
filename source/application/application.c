// Header files include //
#include "../../include/application/application.h"

// STD include //
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h> 

void initApplication(void) {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, true);
    nodelay(stdscr, true);
}

void initColor(void) {
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

bool initApplicationStructures(struct Application** application) {
    (*application)->elementList = NULL;
    (*application)->tetrimino = malloc(sizeof(struct Tetrimino));
    if (!(*application)->tetrimino) {
        return false;
    }
    (*application)->tetrimino->elementList = NULL;
    (*application)->tetrimino->color = 0;
    return true;
}

void run(struct Application** application) {
    createLightningTetrimino(&(*application)->tetrimino, 2);
    while (true) {
        int input = getch();
        if (input == QUIT) {
            break;
        } if (input == ROTATE) {
            rotateTetrimino((*application)->tetrimino);
        } if (input == LEFT) {
            moveTetrimino((*application)->tetrimino, -1, 0);
        } if (input == RIGHT) {
            moveTetrimino((*application)->tetrimino, 1, 0);
        } if (input == UP) {
            moveTetrimino((*application)->tetrimino, 0, -1);
        } if (input == DOWN) {
            moveTetrimino((*application)->tetrimino, 0, 1);
        }
        erase();
        displayMap();
        displayElementList((*application)->tetrimino->elementList);
        wnoutrefresh(stdscr);
        doupdate();
    }
}

void endApplication(void) {
    if (isendwin()) {
        return;
    }
    nodelay(stdscr, false);
    keypad(stdscr, false);
    nocbreak();
    echo();
    curs_set(1);
    clear();
    refresh();
    endwin();
}

void freeApplicationStructures(struct Application** application) {
    freeElementList(&(*application)->elementList);
    freeTetrimino(&(*application)->tetrimino);
    free(*application);
    *application = NULL;
}