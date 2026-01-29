#pragma once

struct GUI {
    int windowWidth;
    int windowHeight;
    int score;
    int level;
};

void getWindowSize(struct GUI* gui);
void displayMap(struct GUI* gui);