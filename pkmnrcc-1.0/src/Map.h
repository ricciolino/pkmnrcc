#ifndef MAP_H
#define MAP_H

#include <string>
#include <SDL2/SDL_image.h>
#include "./Matrix.hpp"

class Map {
    private:
        int scale; // the scale size of the tiles
        int tileSize; // the size of a tile
    public:
        std::string name;
        SDL_Texture* mapImg;
        SDL_Rect sourceRectangle;
        SDL_Rect destinationRectangle;
        Matrix<char> accessibleTiles;

        Map();
        ~Map();
       
       void LoadMap(std::string mapName, std::string filePath, int mapSizeX, int mapSizeY); // load a map on the basis of a texture and a file map (e.g. myMap.map)
       void ClearMap();
};

#endif
