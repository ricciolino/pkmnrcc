#include <fstream>
#include "./Constants.h"
#include "./Game.h"
#include "./Map.h"
#include "./EntityManager.h"
#include "./Constants.h"

Map::Map() {
    this->scale = MAP_SCALE_SIZE;
    this->tileSize = MAP_TILE_SIZE;
    this->mapImg = nullptr;
}

void Map::ClearMap() {
    if (mapImg != nullptr) {
        SDL_DestroyTexture(mapImg);
    }
    name = "";
    sourceRectangle = {0,0,0,0};
    destinationRectangle = {0,0,0,0};
    accessibleTiles.Clear();
}

Map::~Map() {
    ClearMap();
}

void Map::LoadMap(std::string mapName, std::string filePath, int mapSizeX, int mapSizeY) {
    this->name = mapName;

    // LOAD THE ACCESSIBLE-TILES FILE
    std::ifstream mapFile;
    mapFile.open(filePath + ".map");
    this->accessibleTiles.Init(mapSizeY, mapSizeX); // mapSizeY -> (N rows) & mapSizeX -> (M columns)
    this->accessibleTiles.LoadFromFile(mapFile);
    mapFile.close();

    // LOAD THE MAP IMAGE
    std::string imgPath{ filePath + std::string(".png") };
    SDL_Surface* surface = IMG_Load(imgPath.c_str());
    this->mapImg = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
    this->sourceRectangle.x = 0;
    this->sourceRectangle.y = 0;
    this->sourceRectangle.w = mapSizeX * tileSize * scale;
    this->sourceRectangle.h = mapSizeY * tileSize * scale;
    this->destinationRectangle = this->sourceRectangle; // initially the .x and .y of destRect will be 0 as the sourceRect but when the mainPlayer will be setted they will change accordingly
}
