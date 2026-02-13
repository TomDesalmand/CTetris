// Header files include //
#include "../../include/application/application.h"

void displayMap(struct GUI* gui) {
    int mapDisplayWidth = gui->mapWidth * 2;
    int startY = gui->windowHeight / 2 - gui->mapHeight / 2;
    int startX = gui->windowWidth / 2 - mapDisplayWidth / 2;

    // ! HORIZONTAL BORDER MAP :
    mvhline(startY - 1, startX, 0, mapDisplayWidth + 2); //TOP
    mvhline(startY + gui->mapHeight, startX, 0, mapDisplayWidth + 2); //BOTTOM
    // ! VERTICAL BORDER MAP :
    mvvline(startY, startX - 1, 0, gui->mapHeight); //LEFT
    mvvline(startY, startX + mapDisplayWidth + 2, 0, gui->mapHeight); //RIGHT
    // ! MAP JUNCTION BOX :
    mvaddch(startY - 1, startX - 1, ACS_ULCORNER); // TOP LEFT
    mvaddch(startY - 1, startX + mapDisplayWidth + 2, ACS_URCORNER); // TOP RIGHT
    mvaddch(startY + gui->mapHeight, startX - 1, ACS_LLCORNER); // BOTTOM LEFT
    mvaddch(startY + gui->mapHeight, startX + mapDisplayWidth + 2, ACS_LRCORNER); // BOTTOM RIGHT
}

void getWindowSize(struct GUI *gui) {
    getmaxyx(stdscr, gui->windowHeight, gui->windowWidth);
}