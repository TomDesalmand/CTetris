#pragma once

// Structure that holds the speed of the game based
// on the current score of the player.
struct LevelScore {
    int level;
    int score;
    double speed;
};

struct GUI {
    struct LevelScore* levelScore;
    int windowWidth;
    int windowHeight;
    int mapWidth;
    int mapHeight;
    int score;
    int level;
    double speed;
};

void getWindowSize(struct GUI* gui);
void displayMap(struct GUI* gui);
void displayHudInfo(struct GUI* gui);
