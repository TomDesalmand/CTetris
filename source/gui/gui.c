// Header files include //
#include "../../include/application/application.h"

void displayMap(struct GUI* gui) {
    // ! HORIZONTAL BORDER MAP :
    mvhline(gui->windowHeight / 2 - gui->mapHeight / 2 - 1, gui->windowWidth / 2 - gui->mapWidth / 2, 0, gui->mapWidth); //TOP
    mvhline(gui->windowHeight / 2 + gui->mapHeight / 2 + 1, gui->windowWidth / 2 - gui->mapWidth / 2, 0, gui->mapWidth); //BOTTOM
    // ! VERTICAL BORDER MAP :
    mvvline(gui->windowHeight / 2 - gui->mapHeight / 2, gui->windowWidth / 2 - gui->mapWidth / 2 - 1 , 0, gui->mapHeight); //LEFT
    mvvline(gui->windowHeight / 2 - gui->mapHeight / 2, gui->windowWidth / 2 + gui->mapWidth / 2 + 1, 0, gui->mapHeight); //RIGHT
    // ! MAP JUNSTION BOX :
    mvaddch(gui->windowHeight / 2 - gui->mapHeight / 2 - 1, gui->windowWidth / 2 - gui->mapWidth / 2 - 1, ACS_ULCORNER); // TOP LEFT
    mvaddch(gui->windowHeight / 2 - gui->mapHeight / 2 - 1, gui->windowWidth / 2 + gui->mapWidth / 2 + 1, ACS_URCORNER); // TOP RIGHT
    mvaddch(gui->windowHeight / 2 + gui->mapHeight / 2 + 1, gui->windowWidth / 2 - gui->mapWidth / 2 - 1, ACS_LLCORNER); // BOTTOM LEFT
    mvaddch(gui->windowHeight / 2 + gui->mapHeight / 2 + 1, gui->windowWidth / 2 + gui->mapWidth / 2 + 1, ACS_LRCORNER); // BOTTOM RIGHT
}

void getWindowSize(struct GUI *gui) {
    getmaxyx(stdscr, gui->windowHeight, gui->windowWidth);
}