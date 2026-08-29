// Header files include //
#include "../../include/application/application.h"

// STD include //
#include <stdbool.h>
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
    init_pair(8, COLOR_WHITE, COLOR_WHITE);
}

bool initApplicationStructures(struct Application** application) {
    static struct LevelScore scores[] = {
        {1, 1, 1.f},
        {2, 100, 0.75f},
        {3, 2000, 0.50f},
        {4, 3000, 0.25f},
        {5, 4000, 0.20f},
        {6, 5000, 0.15f},
        {7, 3000, 0.125f},
        {8, 1000, 0.10f},
        {9, 2000, 0.075f},
        {10, 3000, 0.05f}
    };

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
    (*application)->gui->mapWidth = 10;
    (*application)->gui->mapHeight = 30;
    (*application)->gui->level = 1;
    (*application)->gui->score = 0;
    (*application)->gui->speed = scores[0].speed;
    (*application)->gui->levelScore = scores;
    return true;
}

void updateLevel(struct GUI** gui) {
    if ((*gui)->level == 10) {
        return;
    }
    if ((*gui)->score >= (*gui)->levelScore[(*gui)->level].score) {
        (*gui)->level++;
        (*gui)->speed = (*gui)->levelScore[(*gui)->level - 1].speed;
    }
}


bool handleInputs(struct Application** application) {
    int input = getch();
    if (input == QUIT) {
        return true;
    } if (input == ROTATE) {
        rotateTetrimino((*application)->gui, (*application)->elementList, (*application)->tetrimino);
    } if (input == KEY_LEFT) {
        moveTetrimino((*application)->gui, (*application)->elementList, (*application)->tetrimino, -1, 0);
    } if (input == KEY_RIGHT) {
        moveTetrimino((*application)->gui, (*application)->elementList, (*application)->tetrimino, 1, 0);
    } if (input == KEY_UP) {
        moveTetrimino((*application)->gui, (*application)->elementList, (*application)->tetrimino, 0, -1);
    } if (input == KEY_DOWN) {
        moveTetrimino((*application)->gui, (*application)->elementList, (*application)->tetrimino, 0, 1);
    } if (input == KEY_RESIZE) {
        getWindowSize((*application)->gui);
    }
    return false;
}

void display(struct Application** application, int* frames, struct timeval* last, struct timeval* lastDrop) {
    static double last_fps = 0.0;
    struct timeval now;
    gettimeofday(&now, NULL);
    double elapsed = (double)(now.tv_sec - last->tv_sec) + (now.tv_usec - last->tv_usec) / 1000000.0;
    double dropElapsed = (double)(now.tv_sec - lastDrop->tv_sec) + (now.tv_usec - lastDrop->tv_usec) / 1000000.0;

    // FPS calculation
    if (elapsed >= 1.f) {
        last_fps = (*frames) / elapsed;
        *frames = 0;
        *last = now;
    }

    // Tetrimino drop
    if (dropElapsed >= (*application)->gui->speed) {
        moveTetrimino((*application)->gui, (*application)->elementList, (*application)->tetrimino, 0, 1);
        *lastDrop = now;  // Reset drop timer after tetrimino moves
    }

    // Rendering
    if (elapsed >= 0.016) {
        erase();
        updateLevel(&(*application)->gui);
        displayMap((*application)->gui);
        displayHudInfo((*application)->gui);
        displayElementList((*application)->gui, (*application)->tetrimino->elementList);
        displayElementList((*application)->gui, (*application)->elementList);
        displayNextElementList((*application)->gui, (*application)->nextTetrimino->elementList);
        mvprintw(0, 0, "TPS: %.2f", last_fps);
    }
}

void run(struct Application** application) {
    createRandomTetrimino(&(*application)->tetrimino);
    createRandomTetrimino(&(*application)->nextTetrimino);
    getWindowSize((*application)->gui);

    struct timeval lastFrame, lastDrop;
    gettimeofday(&lastFrame, NULL);
    gettimeofday(&lastDrop, NULL);
    int frames = 0;
    while (!handleInputs(&(*application))) {
        frames++;
        display(&(*application), &frames, &lastFrame, &lastDrop);  // Pass lastDrop
        wnoutrefresh(stdscr);
        doupdate();
        if (checkPlaceTetrimino((*application)->gui, &(*application)->elementList, &(*application)->tetrimino, &(*application)->nextTetrimino)) {
            flashAndDeleteRows(&(*application)->gui, &(*application)->elementList);
        }
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
    freeTetrimino(&(*application)->nextTetrimino);
    free((*application)->gui);
    free(*application);
    *application = NULL;
}
