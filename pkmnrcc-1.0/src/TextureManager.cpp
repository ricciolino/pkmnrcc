#include "./TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName) { // first load the IMG specified by the path 'fileName' into the surface and then make the texture from the surface
    SDL_Surface* surface = IMG_Load(fileName);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Game::renderer, texture, &sourceRectangle, &destinationRectangle, 0.0, nullptr, flip); // specify how much portion of the source IMG to use and the destination position into the screen

}
