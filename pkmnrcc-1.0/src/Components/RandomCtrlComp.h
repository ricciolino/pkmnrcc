#ifndef RANDOMCTRLCOMP_H
#define RANDOMCTRLCOMP_H 

#include <SDL2/SDL.h>
#include "../Game.h"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoundingComponent.h"
#include "../Collision.h"

class RandomCtrlComp: public Component { 
    private:
        unsigned int rndMovement;
        unsigned int rndFrequency;
        const int maxRndFrequency;
        const int minRndFrequency;
        unsigned int ticksLastMovement;
        
    public:
        TransformComponent *transform;
        SpriteComponent *sprite;
        BoundingComponent *bounding;

        RandomCtrlComp(const int _maxRndFrequency, const int _minRndFrequency): maxRndFrequency(_maxRndFrequency), minRndFrequency(_minRndFrequency), transform(nullptr), sprite(nullptr) {
            srand(time(nullptr));
            rndMovement = 0; // hold the position at the beginning
            rndFrequency = (maxRndFrequency - minRndFrequency) / 2;
            ticksLastMovement = SDL_GetTicks();
        }

        ~RandomCtrlComp() {
            transform = nullptr;
            sprite = nullptr;
            bounding = nullptr;
//            std::cout << "\t\t" << this->owner->name << ": call destructor for RandomCtrlComp" << std::endl;
        }

        void Initialize() override {
            transform = owner->GetComponent<TransformComponent>();
            sprite = owner->GetComponent<SpriteComponent>();
            bounding = owner->GetComponent<BoundingComponent>();
        }

        void Update() override {
            if (SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastMovement + rndFrequency * FRAME_TARGET_TIME)) {
                ticksLastMovement = SDL_GetTicks();
                rndMovement = rand() % 4 + 1; // generate number between 1 and 4 (included)
                rndFrequency = rand() % (maxRndFrequency - minRndFrequency) + minRndFrequency;
            } else {
                rndMovement = 0;
            }
            
            if( rndMovement == 1 && transform->position.y > bounding->yUp * STEP_SIZE ) {
                if (transform->onGoingStep == 0) {
                    if (!Collision::IsThereACollision(Game::map.accessibleTiles, transform->mapPosition.y - 1, transform->mapPosition.x)) {
                        SetTileAccessible(true); // make accessible the tile from which the character is leaving
                        transform->mapPosition.y--; // update the mapPosition
                        SetTileAccessible(false); // make inaccessible the current tile where it is the character (tile @ transform->mapPosition.y, transform->mapPosition.x) 
                        transform->onGoingStep = STEP_SIZE;
                        transform->velocity.y = -transform->velocitySize;
                        transform->onGoingDirection = 'y';
                        sprite->activeAnimation = true;
                    } else {
                        transform->velocity.y = 0;
                        sprite->activeAnimation = false;
                    }
                    transform->velocity.x = 0;
                    sprite->Play("UpAnimation");
                    sprite->footAlternate = !sprite->footAlternate;
                } 
            }                                                                           // check if the RIGHT movement is scheduled
            else if( rndMovement == 2 && transform->position.x < bounding->xRight * STEP_SIZE ) {
                if (transform->onGoingStep == 0) {
                    if (!Collision::IsThereACollision(Game::map.accessibleTiles, transform->mapPosition.y, transform->mapPosition.x + 1)) {
                        SetTileAccessible(true); // make accessible the tile from which the character is leaving
                        transform->mapPosition.x++; // update the mapPosition
                        SetTileAccessible(false); // make inaccessible the current tile where it is the character (tile @ transform->mapPosition.y, transform->mapPosition.x) 
                        transform->onGoingStep = STEP_SIZE;
                        transform->velocity.x = transform->velocitySize;
                        transform->onGoingDirection = 'x';
                        sprite->activeAnimation = true;
                    } else {
                        transform->velocity.x = 0;
                        sprite->activeAnimation = false;
                    }
                    transform->velocity.y = 0;
                    sprite->Play("RightAnimation");
                    sprite->footAlternate = !sprite->footAlternate;
                }
            }                                                                           // check if the DOWN movement is scheduled
            else if( rndMovement == 3 && transform->position.y < bounding->yDown * STEP_SIZE ) {
                if (transform->onGoingStep == 0) {
                    if (!Collision::IsThereACollision(Game::map.accessibleTiles, transform->mapPosition.y + 1, transform->mapPosition.x)) {
                        SetTileAccessible(true); // make accessible the tile from which the character is leaving
                        transform->mapPosition.y++; // update the mapPosition
                        SetTileAccessible(false); // make inaccessible the current tile where it is the character (tile @ transform->mapPosition.y, transform->mapPosition.x) 
                        transform->onGoingStep = STEP_SIZE;
                        transform->velocity.y = transform->velocitySize;
                        transform->onGoingDirection = 'y';
                        sprite->activeAnimation = true;
                    } else {
                        transform->velocity.y = 0;
                        sprite->activeAnimation = false;
                    }
                    transform->velocity.x = 0;
                    sprite->Play("DownAnimation");
                    sprite->footAlternate = !sprite->footAlternate;
                }
            }                                                                           // check if the LEFT movement is scheduled 
            else if( rndMovement == 4 && transform->position.x > bounding->xLeft * STEP_SIZE ) {
                if (transform->onGoingStep == 0) {
                    if (!Collision::IsThereACollision(Game::map.accessibleTiles, transform->mapPosition.y, transform->mapPosition.x - 1)) {
                        SetTileAccessible(true); // make accessible the tile from which the character is leaving (tile @ transform->mapPosition.y, transform->mapPosition.x)
                        transform->mapPosition.x--; // update the mapPosition
                        SetTileAccessible(false); // make inaccessible the current tile where it is the character (tile @ transform->mapPosition.y, transform->mapPosition.x)
                        transform->onGoingStep = STEP_SIZE;
                        transform->velocity.x = -transform->velocitySize;
                        transform->onGoingDirection = 'x';
                        sprite->activeAnimation = true;
                    } else {
                        transform->velocity.x = 0;
                        sprite->activeAnimation = false;
                    }
                    transform->velocity.y = 0;
                    sprite->Play("LeftAnimation");
                    sprite->footAlternate = !sprite->footAlternate;
                }
            } else {                                      // if either, NO arrow keys or more than one arrow key, are pressed, then stop moving and animation
                if (transform->onGoingStep == 0) {
                    transform->velocity.y = 0;
                    transform->velocity.x = 0;
                    sprite->activeAnimation = false;
                    transform->onGoingDirection = '-';
                }
            }

            // if the movement is ON GOING, decrease the onGoingStep until is reached the TARGET STEP SIZE
            if (transform->onGoingStep > 0) {
                if (transform->onGoingDirection == 'x') {
                    transform->onGoingStep -= transform->velocity.x >= 0 ? transform->velocity.x : -transform->velocity.x; // decrease the onGoingStep along x direction
                    transform->velocity.x > 0 ? sprite->Play("RightAnimation") : sprite->Play("LeftAnimation"); // play the appropriate animation for the x direction
                }
                if (transform->onGoingDirection == 'y') {
                    transform->onGoingStep -= transform->velocity.y >= 0 ? transform->velocity.y : -transform->velocity.y; // decrease the onGoingStep along y direction
                    transform->velocity.y > 0 ? sprite->Play("DownAnimation") : sprite->Play("UpAnimation"); // play the appropriate animation for the y direction
                }
            }
        }

        void SetTileAccessible(bool isAccessible) { // based on the current tile defined from transform->mapPosition
            if (isAccessible) {
                Game::map.accessibleTiles.Set(transform->mapPosition.y, transform->mapPosition.x, '0'); // tile accessible
            } else {
                Game::map.accessibleTiles.Set(transform->mapPosition.y, transform->mapPosition.x, '1'); // tile inaccessible
            }
        }

        void Render() override {
        }

        void Print() const override {
            std::cout << "        maxRndFrequency: " << this->maxRndFrequency << std::endl;
            std::cout << "        minRndFrequency: " << this->minRndFrequency << std::endl;
        }
};

#endif
