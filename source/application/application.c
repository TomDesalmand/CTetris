// Header files include //
#include "../../include/application/application.h"

// STD include //
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h> 
#include <sys/time.h>

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
    (*application)->gui = malloc(sizeof(struct GUI));
    if (!(*application)->gui) {
        return false;
    }
    (*application)->tetrimino = malloc(sizeof(struct Tetrimino));
    if (!(*application)->tetrimino) {
        return false;
    }
    (*application)->tetrimino->elementList = NULL;
    (*application)->tetrimino->color = 0;
    (*application)->elementList = NULL;
    (*application)->gui->mapWidth = 15;
    (*application)->gui->mapHeight = 25;
    (*application)->gui->level = 0;
    (*application)->gui->score = 0;
    return true;
}

bool handleInputs(struct Application** application) {
    int input = getch();
    if (input == QUIT) {
        return true;
    } if (input == ROTATE) {
        rotateTetrimino((*application)->gui, (*application)->elementList, (*application)->tetrimino);
    } if (input == LEFT) {
        moveTetrimino((*application)->gui, (*application)->elementList, (*application)->tetrimino, -1, 0);
    } if (input == RIGHT) {
        moveTetrimino((*application)->gui, (*application)->elementList, (*application)->tetrimino, 1, 0);
    } if (input == UP) {
        moveTetrimino((*application)->gui, (*application)->elementList, (*application)->tetrimino, 0, -1);
    } if (input == DOWN) {
        moveTetrimino((*application)->gui, (*application)->elementList, (*application)->tetrimino, 0, 1);
    } if (input == KEY_RESIZE) {
        getWindowSize((*application)->gui);
    }
    return false;
}

void displayFPS(int* frames, struct timeval* last) {
    static double last_fps = 0.0;
    struct timeval now;
    gettimeofday(&now, NULL);
    double elapsed = (double)(now.tv_sec - last->tv_sec) + (now.tv_usec - last->tv_usec) / 1000000.0;
    if (elapsed >= 1.f) {
        last_fps = (*frames) / elapsed;
        *frames = 0;
        *last = now;
    }
    mvprintw(0, 0, "FPS: %.2f", last_fps);
}

void run(struct Application** application) {
    createRandomTetrimino(&(*application)->tetrimino);
    getWindowSize((*application)->gui);

    struct timeval last;
    gettimeofday(&last, NULL);
    int frames = 0;

    while (!handleInputs(&(*application))) {
        frames++;
        checkPlaceTetrimino((*application)->gui, &(*application)->elementList, &(*application)->tetrimino);
        erase();
        displayMap((*application)->gui);
        displayElementList((*application)->gui, (*application)->tetrimino->elementList);
        displayElementList((*application)->gui, (*application)->elementList);
        displayFPS(&frames, &last);
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
    free((*application)->gui);
    free(*application);
    *application = NULL;
}