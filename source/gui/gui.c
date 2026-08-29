// Header files include //
#include "../../include/application/application.h"

#define PIXEL_SIZE 2
#define OFFSET 1

// Do not ask me to actually detail/macro any of the hardcoded
// values in this function because I would actually crashout :D.
void displayMap(struct GUI* gui) {
    int mapDisplayWidth = gui->mapWidth * PIXEL_SIZE;
    int startY = gui->windowHeight / 2 - gui->mapHeight / 2;
    int startX = gui->windowWidth / 2 - mapDisplayWidth / 2;

    mvhline(startY - OFFSET, startX, 0, mapDisplayWidth + PIXEL_SIZE); //TOP
    mvhline(startY + gui->mapHeight, startX, 0, mapDisplayWidth + PIXEL_SIZE); //BOTTOM
    mvvline(startY, startX - OFFSET, 0, gui->mapHeight); //LEFT
    mvvline(startY, startX + mapDisplayWidth + PIXEL_SIZE, 0, gui->mapHeight); //RIGHT
    mvaddch(startY - OFFSET, startX - OFFSET, ACS_ULCORNER); // TOP LEFT
    mvaddch(startY - OFFSET, startX + mapDisplayWidth + PIXEL_SIZE, ACS_URCORNER); // TOP RIGHT
    mvaddch(startY + gui->mapHeight, startX - OFFSET, ACS_LLCORNER); // BOTTOM LEFT
    mvaddch(startY + gui->mapHeight, startX + mapDisplayWidth + PIXEL_SIZE, ACS_LRCORNER); // BOTTOM RIGHT
}

void displayHudInfo(struct GUI* gui) {
    int mapDisplayWidth = gui->mapWidth * 2;
    int startY = gui->windowHeight / 2 - gui->mapHeight / 2;
    int startX = gui->windowWidth / 2 + mapDisplayWidth / 2;
    mvaddstr(startY, startX + 5, "Level:");
    mvprintw(startY, startX + 12, "%d", gui->level);
    mvaddstr(startY + 2, startX + 5, "Score:");
    mvprintw(startY + 2, startX + 12, "%d", gui->score);
    mvaddstr(startY + 4, startX + 5, "Next Tetromino:");
}

void getWindowSize(struct GUI *gui) {
    getmaxyx(stdscr, gui->windowHeight, gui->windowWidth);
}
