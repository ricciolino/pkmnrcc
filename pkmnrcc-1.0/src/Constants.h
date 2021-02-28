#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>

const unsigned int WINDOW_WIDTH = 896;
const unsigned int WINDOW_HEIGHT = 896;

const unsigned int FPS = 250; // When this value change, please also change the velocitySize in the assets scripts !
const unsigned int FRAME_TARGET_TIME = 1000 / FPS; // time-step = 4 ms

enum Modalities {
    START = 0,
    NORMAL = 1,
    QUIT = 2,
    SAVE = 3
};

enum LayerType {
    OVER_TILEMAP_LAYER = 0,
    PLAYER_LAYER = 1,
};
const unsigned int NUM_LAYERS = 2;

const unsigned int MAP_TILE_SIZE = 32;
const unsigned int MAP_SCALE_SIZE = 2;

const unsigned int STEP_SIZE = 64;

const SDL_Color RED_COLOR = {255, 0, 0, 255};
const SDL_Color GREEN_COLOR = {0, 255, 0, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255, 255};
const SDL_Color WHITE_COLOR = {255, 255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0, 255};
const SDL_Color YELLOW_COLOR = {255, 255, 0, 255};
const SDL_Color FUXIA_COLOR = {255, 0, 255, 255};
const SDL_Color CYAN_COLOR = {0, 255, 255, 255};

#endif
