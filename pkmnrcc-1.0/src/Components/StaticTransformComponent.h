#ifndef STATICTRANSFORMCOMPONENT_H
#define STATICTRANSFORMCOMPONENT_H

#include <SDL2/SDL.h>
#include "../EntityManager.h"
#include "../Constants.h"
#include "../Tuple2.hpp"
#include "../Game.h"

class StaticTransformComponent: public Component {

    public: 
        /***********/
        /* MEMBERS */
        /***********/
        Tuple2<int> position; // the effective position in pixels (updated every frame)
        Tuple2<int> mapPosition; // the row and column indexes of the position of the character on the map (updated when the movement into a certain direction is accepted in CtrlComponent)
        int width;
        int height;
        int scale;

        /***********/
        /* METHODS */
        /***********/
       StaticTransformComponent(int posX, int posY, int w, int h, int s) {
            position.x = posX;
            position.y = posY;
            mapPosition.x = position.x / static_cast<int>(STEP_SIZE);
            mapPosition.y = position.y / static_cast<int>(STEP_SIZE);
            width = w;
            height = h;
            scale = s;
        }

        void SetAccessibilityMap() {
            size_t w = this->mapPosition.x + this->width * this->scale / STEP_SIZE;
            size_t h = this->mapPosition.y + this->height * this->scale / STEP_SIZE;
            for (size_t x = this->mapPosition.x; x < w ; x++) {
                for (size_t y = this->mapPosition.y; y < h ; y++) {
                    Game::map.accessibleTiles.Set(y, x, '1');
                }
            }
        }

        void Initialize() override {
        }

        void Update() override {
        }

        void Render() override {
        }

        void Print() const override {
            std::cout << "        width: " << width << std::endl;
            std::cout << "        height: " << height << std::endl;
            std::cout << "        scale: " << scale << std::endl;
            std::cout << "        position(Tuple2)x,y: " << position.x << "," << position.y << std::endl;
            std::cout << "        mapPosition(Tuple2)x,y: " << mapPosition.x << "," << mapPosition.y << std::endl;
        }

        ~StaticTransformComponent() {
        }
};

#endif
