#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include "./Game.h"

class FontManager {
    public:
        static TTF_Font* LoadFont(const char* fileName, int fontSize); // load a font from file specifying the size
        static void Draw(SDL_Texture* texture, SDL_Rect position); // draw a font in a certain position providing a texture created form a surface (SDL_CreateTextureFromSurface)
};

#endif
