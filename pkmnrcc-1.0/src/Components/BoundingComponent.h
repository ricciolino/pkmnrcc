#ifndef BOUNDINGCOMPONENT_H
#define BOUNDINGCOMPONENT_H

#include <iostream>
#include "../AssetManager.h"

class BoundingComponent: public Component {
    public:
        unsigned int xLeft;
        unsigned int xRight;
        unsigned int yUp;
        unsigned int yDown;
        unsigned int x;
        unsigned int y;
        unsigned int w;
        unsigned int h;
        bool showBounding;
        SDL_Rect rectBound;
        SDL_Rect rectLabel;
        SDL_Texture* label;
        std::string text;
        SDL_Color color;
        std::string fontFamily;
        TransformComponent* tc;

        BoundingComponent(const unsigned int _xLeft, const unsigned int _xRight, const unsigned int _yUp, const unsigned int _yDown, const SDL_Color& _color, const std::string _fontFamily) : showBounding(false), color(_color), fontFamily(_fontFamily), label(nullptr) {
            this->xLeft = _xLeft;
            this->xRight = _xRight;
            this->yUp = _yUp;
            this->yDown = _yDown;
            this->x = this->xLeft * STEP_SIZE;
            this->y = this->yUp * STEP_SIZE;
            this->w = this->xRight * STEP_SIZE - this->x + STEP_SIZE;
            this->h = this->yDown * STEP_SIZE - this->y + STEP_SIZE;
        }

        ~BoundingComponent(){
            if (label != nullptr) SDL_DestroyTexture(label);
            tc = nullptr;
        }

        void Initialize() override {
            rectBound = {0, 0, static_cast<int>(w), static_cast<int>(h)};
            tc = owner->GetComponent<TransformComponent>();
            text = owner->name;
            SetLabelText(text,fontFamily);
        }

        void SetLabelText(std::string text, std::string fontFamily) {
            SDL_Surface* surface = TTF_RenderText_Blended(Game::assetManager.GetFont(fontFamily), text.c_str(), color);
            label = SDL_CreateTextureFromSurface(Game::renderer, surface);
            SDL_FreeSurface(surface);
            SDL_QueryTexture(label, nullptr, nullptr, &rectLabel.w, &rectLabel.h);
        }

        void Update() override {}

        void Render() override {
            if (showBounding == true) {
                SDL_SetRenderDrawColor(Game::renderer, color.r, color.g, color.b, color.a);
                rectBound.x = static_cast<int>(x - Game::camera.x);
                rectBound.y = static_cast<int>(y - Game::camera.y);
                SDL_RenderDrawRect(Game::renderer, &rectBound);
                rectLabel.x = static_cast<int>(tc->position.x + STEP_SIZE/6 - Game::camera.x);
                rectLabel.y = static_cast<int>(tc->position.y - STEP_SIZE/4 - Game::camera.y);
                FontManager::Draw(label,rectLabel);
            }
        }

        void Print() const override {
            std::cout << "        bound xLeft: " << this->xLeft << std::endl;
            std::cout << "        bound xRight: " << this->xRight << std::endl;
            std::cout << "        bound yUp: " << this->yUp << std::endl;
            std::cout << "        bound yDown: " << this->yDown << std::endl;
        }
};

#endif
