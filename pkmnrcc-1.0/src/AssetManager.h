#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <string>
#include <SDL2/SDL_ttf.h>
#include "./TextureManager.h"
#include "./FontManager.h"
//#include "./EntityManager.h"

class AssetManager {

    private:
        /***********/
        /* MEMBERS */
        /***********/
        //EntityManager& manager; // a reference to the entityManager
        std::map<std::string, SDL_Texture*> textures; // associate an ID for each Texture
        std::map<std::string, TTF_Font*> fonts; // associate an ID for each Font

    public:
        /***********/
        /* METHODS */
        /***********/
        //AssetManager(EntityManager& manager);
        AssetManager();
        ~AssetManager(); // call ClearData
        void ClearData();
        void AddTexture(std::string textureId, const char* filePath); // add a texture to the map
        void AddFont(std::string fontId, const char* filePath, int fontSize); // add a font to the map
        SDL_Texture* GetTexture(std::string textureId); // get a pointer to the texture with textureId
        TTF_Font* GetFont(std::string fontId); // get a pointer to the font with fontId
};

#endif
