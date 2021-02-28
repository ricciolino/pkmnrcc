#ifndef STATICSPRITECOMPONENT_H
#define STATICSPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../Constants.h"
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "../Animation.h"

class StaticSpriteComponent: public Component {
    private:
        StaticTransformComponent* transform;
        SDL_Texture* texture;
        SDL_Rect sourceRectangle;
        SDL_Rect destinationRectangle;
        bool isFixed;

    public:
        unsigned int animationIndex;
        bool isAnimated;
        SDL_RendererFlip spriteFlip;

        ~StaticSpriteComponent() {
        }

        StaticSpriteComponent(std::string assetTextureId, bool isFixed, unsigned int animationIndex = 0) { // sprite with NO animation
            this->isAnimated = false;
            this->isFixed = isFixed;
            this->animationIndex = animationIndex;
            SetTexture(assetTextureId);
        }

        void SetTexture(std::string assetTextureId) {
            texture = Game::assetManager.GetTexture(assetTextureId);
        }

        void Initialize() override {
            transform = owner->GetComponent<StaticTransformComponent>();
            sourceRectangle.x = 0;
            sourceRectangle.y = 0;
            sourceRectangle.w = transform->width;
            sourceRectangle.h = transform->height;
            spriteFlip = SDL_FLIP_NONE;
        }

        void Update() override {
            sourceRectangle.x = animationIndex * transform->width;
            destinationRectangle.x = static_cast<int>(transform->position.x) - (isFixed ? 0 : Game::camera.x);
            destinationRectangle.y = static_cast<int>(transform->position.y) - (isFixed ? 0 : Game::camera.y);
            destinationRectangle.w = transform->width * transform->scale;
            destinationRectangle.h = transform->height * transform->scale;
        }

        void Render() override {
            TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
        }

        void Print() const override {
            std::cout << "        isAnimated: " << this->isAnimated << std::endl;
            std::cout << "        isFixed: " << this->isFixed << std::endl;
        }
};

#endif
