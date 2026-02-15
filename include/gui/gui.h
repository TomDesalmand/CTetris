#pragma once

struct GUI {
    int windowWidth;
    int windowHeight;
    int mapWidth;
    int mapHeight;
    int score;
    int level;
};

void getWindowSize(struct GUI* gui);
void displayMap(struct GUI* gui);
void displayNextTetriminoBox(struct GUI* gui);