#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <SDL2/SDL.h>
#include "../EntityManager.h"
#include "../Constants.h"
#include "../Tuple2.hpp"
#include "../Game.h"

class TransformComponent: public Component {

    public: 
        /***********/
        /* MEMBERS */
        /***********/
        float velocitySize;
        int onGoingStep;
        char onGoingDirection;
        Tuple2<int> position; // the effective position in pixels (updated every frame)
        Tuple2<int> mapPosition; // the row and column indexes of the position of the character on the map (updated when the movement into a certain direction is accepted in CtrlComponent)
        Tuple2<float> velocity;
        int width;
        int height;
        int scale;

        /***********/
        /* METHODS */
        /***********/
        TransformComponent(int posX, int posY, int w, int h, int s, float vel) {
            position.x = posX;
            position.y = posY;
            mapPosition.x = position.x / STEP_SIZE;
            mapPosition.y = position.y / STEP_SIZE;
            velocity.x = 0.0;
            velocity.y = 0.0;
            width = w;
            height = h;
            scale = s;
            velocitySize = vel;
        }

        void SetAccessibilityMap() {
            Game::map.accessibleTiles.Set(mapPosition.y, mapPosition.x, '1');
        }

        void Initialize() override {
            this->onGoingStep = 0;
            this->onGoingDirection = '-';
        }

        void Update() override {
            position.x += velocity.x;
            position.y += velocity.y;
            onGoingStep = onGoingStep < 0 ? 0 : onGoingStep;
        }

        void Render() override {
        }

        void Print() const override {
            std::cout << "        velocitySize: " << velocitySize << std::endl;
            std::cout << "        width: " << width << std::endl;
            std::cout << "        height: " << height << std::endl;
            std::cout << "        scale: " << scale << std::endl;
            std::cout << "        position(Tuple2)x,y: " << position.x << "," << position.y << std::endl;
            std::cout << "        mapPosition(Tuple2)x,y: " << mapPosition.x << "," << mapPosition.y << std::endl;
        }

        ~TransformComponent() {
//            std::cout << "\t\t" << this->owner->name << ": call destructor for TransformComponent" << std::endl;
        }
};

#endif
