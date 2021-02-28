#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../Constants.h"
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "../Animation.h"

class SpriteComponent: public Component {
    private:
        TransformComponent* transform;
        SDL_Texture* texture;
        SDL_Rect sourceRectangle;
        SDL_Rect destinationRectangle;
        std::map<std::string, Animation> animations;
        std::string currentAnimationName;
        int numFrames;
        bool isFixed;

    public:
        unsigned int animationIndex;
        bool isAnimated;
        bool activeAnimation;
        SDL_RendererFlip spriteFlip;
        unsigned int footAlternate;

        ~SpriteComponent() {
//            std::cout << "\t\t" << this->owner->name << ": call destructor for SpriteComponent" << std::endl;
        }

        SpriteComponent(std::string assetTextureId, bool isFixed, unsigned int animationIndex = 0) { // sprite with NO animation
            this->isAnimated = false;
            this->isFixed = isFixed;
            this->animationIndex = animationIndex;
            SetTexture(assetTextureId);
        }

        SpriteComponent(std::string assetTextureId, int numFrames, bool hasDirections, bool isFixed, unsigned int animationIndex = 0) { // sprite with animation
            this->isAnimated = true;
            this->numFrames = numFrames;
            this->isFixed = isFixed;
            this->animationIndex = animationIndex;

            if (hasDirections) {
                Animation downAnimation = Animation(0, numFrames);
                Animation upAnimation = Animation(1, numFrames);
                Animation leftAnimation = Animation(2, numFrames);
                Animation rightAnimation = Animation(3, numFrames);
                animations.emplace("DownAnimation", downAnimation);
                animations.emplace("RightAnimation", rightAnimation);
                animations.emplace("LeftAnimation", leftAnimation);
                animations.emplace("UpAnimation", upAnimation);
                SetCurrentAnimationByIndex(this->animationIndex);
            } else {
                Animation singleAnimation = Animation(0, numFrames);
                animations.emplace("SingleAnimation", singleAnimation);
                this->currentAnimationName = "SingleAnimation";
            }

            Play(this->currentAnimationName);

            SetTexture(assetTextureId);
        }

        void SetCurrentAnimationByIndex(unsigned int animationIndex) {
            switch(animationIndex) {
                case 0:
                    this->currentAnimationName = "DownAnimation";
                break;
                case 1:
                    this->currentAnimationName = "UpAnimation";
                break;
                case 2:
                    this->currentAnimationName = "LeftAnimation";
                break;
                case 3:
                    this->currentAnimationName = "RightAnimation";
                break;
            }
        }

        void Play(std::string animationName) {
            numFrames = animations[animationName].numFrames;
            animationIndex = animations[animationName].index;
            currentAnimationName = animationName;
        }

        void SetTexture(std::string assetTextureId) {
            texture = Game::assetManager.GetTexture(assetTextureId);
        }

        void Initialize() override {
            transform = owner->GetComponent<TransformComponent>();
            sourceRectangle.x = 0;
            sourceRectangle.y = 0;
            sourceRectangle.w = transform->width;
            sourceRectangle.h = transform->height;
            spriteFlip = SDL_FLIP_NONE;
            activeAnimation = false;
            footAlternate = 0;
        }

        void Update() override {
            // if the animation is active, update the frame for the animation, otherwise just pick up the first frame at y = 0
            if (isAnimated && activeAnimation) { // 32 = STEP_SIZE perchè gli sprites si fanno di 32 pixels, -1 perchè sennò per un istante si vede lo sprite a risposo e 16 perchè se la scala è 1 lo step_size è 32 e quindi per metà passo devo tenere lo stesso piede avanti
                sourceRectangle.y = ( STEP_SIZE * footAlternate) + sourceRectangle.h * static_cast<int>((STEP_SIZE - transform->onGoingStep - 1) / ((STEP_SIZE / 4) * transform->scale));
            } else {
                sourceRectangle.y = 0;
            }
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
            std::cout << "        numFrames: " << this->numFrames << std::endl;
        }
};

#endif
