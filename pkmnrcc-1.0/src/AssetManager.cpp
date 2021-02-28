#include "./AssetManager.h"
#include <iostream>

//AssetManager::AssetManager(EntityManager& manager): manager(manager) {}
AssetManager::AssetManager(){}

AssetManager::~AssetManager() {
    this->ClearData();
}

void AssetManager::ClearData() {
    for (auto const& [textureId, texture]: textures) {
        SDL_DestroyTexture(texture);
        //std::cout << "Destroyed texture " <<textureId << std::endl;
    }
    for (auto const& [fontId, font]: fonts) {
        TTF_CloseFont(font);
        //std::cout << "Closed font " << fontId << std::endl;
    }
    textures.clear();
    fonts.clear();
}
void AssetManager::AddTexture(std::string textureId, const char* filePath) {
    textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}
void AssetManager::AddFont(std::string fontId, const char* filePath, int fontSize) {
    fonts.emplace(fontId, FontManager::LoadFont(filePath, fontSize));
}
SDL_Texture* AssetManager::GetTexture(std::string textureId) {
    return textures[textureId];
}
TTF_Font* AssetManager::GetFont(std::string fontId) {
    return fonts[fontId];
}
