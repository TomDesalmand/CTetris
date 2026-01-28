#include "../../include/application/application.h"

void displayMap()
{
    // ! HORIZONTAL BORDER MAP :
    mvhline(1, 5, 0, (WIDTH + 2)); //TOP
    mvhline(HEIGHT, 5, 0, (WIDTH + 2)); //BOTTOM
    // ! VERTICAL BORDER MAP :
    mvvline(1, 5, 0, HEIGHT); //LEFT
    mvvline(1, WIDTH + 6, 0, HEIGHT); //RIGHT
    // ! MAP JUNSTION BOX :
    mvaddch(1, 5, ACS_ULCORNER);
    mvaddch(1, WIDTH + 6, ACS_URCORNER);
    mvaddch(HEIGHT, 5, ACS_LLCORNER);
    mvaddch(HEIGHT, WIDTH + 6, ACS_LRCORNER);
}