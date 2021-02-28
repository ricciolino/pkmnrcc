#ifndef KEYBCTRLCOMPMAPMOVEMENT_H
#define KEYBCTRLCOMPMAPMOVEMENT_H

#include <SDL2/SDL.h>
#include "../Game.h"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Collision.h"

class KeybCtrlCompMapMovement: public Component { // only the main player will have this component !! 
    public:
        TransformComponent *transform;
        SpriteComponent *sprite;
        const Uint8* keyBoardStatus;

        KeybCtrlCompMapMovement(): transform(nullptr), sprite(nullptr), keyBoardStatus(nullptr) {}

        ~KeybCtrlCompMapMovement() {
            transform = nullptr;
            sprite = nullptr;
            keyBoardStatus = nullptr;
//            std::cout << "\t\t" << this->owner->name << ": call destructor for KeybCtrlCompMapMovement" << std::endl;
        }

        void Initialize() override {
            transform = owner->GetComponent<TransformComponent>();
            sprite = owner->GetComponent<SpriteComponent>();
        }

        void Update() override {

            // Get the status of the keyboard (pressed keys)
            keyBoardStatus = SDL_GetKeyboardState(nullptr);

            // accept arrow keys as input only if
            // there is ONLY ONE ARROW key pressed
            // and there is NOT AN ON GOING movement yet
                                                                                        // check if the UP arrow key is pressed
            if( !keyBoardStatus[SDL_SCANCODE_DOWN] && !keyBoardStatus[SDL_SCANCODE_RIGHT] && !keyBoardStatus[SDL_SCANCODE_LEFT] && keyBoardStatus[SDL_SCANCODE_UP]) {
                if (transform->onGoingStep == 0 && Game::changeMap == "") {
                    if (!Collision::IsThereACollision(Game::map.accessibleTiles, transform->mapPosition.y - 1, transform->mapPosition.x)) {
                        if(transform->mapPosition.y - 1 != -1) {
                            SetTileAccessible(true); // make accessible the tile from which the character is leaving
                            transform->mapPosition.y--; // update the mapPosition
                            SetTileAccessible(false); // make inaccessible the current tile where it is the character (tile @ transform->mapPosition.y, transform->mapPosition.x) 
                        } else { // the case in which the character changes map
                            Game::changeMap = "up";
                        }
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
            }                                                                           // check if the RIGHT arrow key is pressed
            else if( !keyBoardStatus[SDL_SCANCODE_DOWN] && keyBoardStatus[SDL_SCANCODE_RIGHT] && !keyBoardStatus[SDL_SCANCODE_LEFT] && !keyBoardStatus[SDL_SCANCODE_UP]) {
                if (transform->onGoingStep == 0 && Game::changeMap == "") {
                    if (!Collision::IsThereACollision(Game::map.accessibleTiles, transform->mapPosition.y, transform->mapPosition.x + 1)) {
                        if(transform->mapPosition.x + 1 != Game::map.accessibleTiles.GetM()) {
                            SetTileAccessible(true); // make accessible the tile from which the character is leaving
                            transform->mapPosition.x++; // update the mapPosition
                            SetTileAccessible(false); // make inaccessible the current tile where it is the character (tile @ transform->mapPosition.y, transform->mapPosition.x) 
                        } else { // the case in which the character changes map
                            Game::changeMap = "right";
                        }
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
            }                                                                           // check if the DOWN arrow key is pressed
            else if( keyBoardStatus[SDL_SCANCODE_DOWN] && !keyBoardStatus[SDL_SCANCODE_RIGHT] && !keyBoardStatus[SDL_SCANCODE_LEFT] && !keyBoardStatus[SDL_SCANCODE_UP]) {
                if (transform->onGoingStep == 0 && Game::changeMap == "") {
                    if (!Collision::IsThereACollision(Game::map.accessibleTiles, transform->mapPosition.y + 1, transform->mapPosition.x)) {
                        if(transform->mapPosition.y + 1 != Game::map.accessibleTiles.GetN()) {
                            SetTileAccessible(true); // make accessible the tile from which the character is leaving
                            transform->mapPosition.y++; // update the mapPosition
                            SetTileAccessible(false); // make inaccessible the current tile where it is the character (tile @ transform->mapPosition.y, transform->mapPosition.x) 
                        } else { // the case in which the character changes map
                            Game::changeMap = "down";
                        }
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
            }                                                                           // check if the LEFT arrow key is pressed
            else if( !keyBoardStatus[SDL_SCANCODE_DOWN] && !keyBoardStatus[SDL_SCANCODE_RIGHT] && keyBoardStatus[SDL_SCANCODE_LEFT] && !keyBoardStatus[SDL_SCANCODE_UP]) {
                if (transform->onGoingStep == 0 && Game::changeMap == "") {
                    if (!Collision::IsThereACollision(Game::map.accessibleTiles, transform->mapPosition.y, transform->mapPosition.x - 1)) {
                        if(transform->mapPosition.x - 1 != -1) {
                            SetTileAccessible(true); // make accessible the tile from which the character is leaving (tile @ transform->mapPosition.y, transform->mapPosition.x)
                            transform->mapPosition.x--; // update the mapPosition
                            SetTileAccessible(false); // make inaccessible the current tile where it is the character (tile @ transform->mapPosition.y, transform->mapPosition.x)
                        } else { // the case in which the character changes map
                            Game::changeMap = "left";
                        }
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
               if (transform->onGoingStep == 0 && Game::changeMap == "") { 
                    if (transform->onGoingStep == 0) {
                        transform->velocity.y = 0;
                        transform->velocity.x = 0;
                        sprite->activeAnimation = false;
                        transform->onGoingDirection = '-';
                    }
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
                Game::map.destinationRectangle.x -= transform->velocity.x;
                Game::map.destinationRectangle.y -= transform->velocity.y;
                Game::up.destinationRectangle.x -= transform->velocity.x;
                Game::up.destinationRectangle.y -= transform->velocity.y;
                Game::down.destinationRectangle.x -= transform->velocity.x;
                Game::down.destinationRectangle.y -= transform->velocity.y;
                Game::right.destinationRectangle.x -= transform->velocity.x;
                Game::right.destinationRectangle.y -= transform->velocity.y;
                Game::left.destinationRectangle.x -= transform->velocity.x;
                Game::left.destinationRectangle.y -= transform->velocity.y;
            } else {
                if(Game::changeMap == "up") {
                    Game::previousMap = Game::map.name;
                    Game::changeMap = Game::up.name;
                    transform->position.y = Game::up.sourceRectangle.h + 1 - STEP_SIZE;
                    transform->mapPosition.y = (transform->position.y - 1) / STEP_SIZE;
                    transform->position.x = transform->position.x - Game::xOffUp;
                    transform->mapPosition.x = transform->position.x / STEP_SIZE;
                }
                if(Game::changeMap == "down") {
                    Game::previousMap = Game::map.name;
                    Game::changeMap = Game::down.name;
                    transform->position.y = -1;
                    transform->mapPosition.y = (transform->position.y + 1) / STEP_SIZE;
                    transform->position.x = transform->position.x - Game::xOffDown;
                    transform->mapPosition.x = transform->position.x / STEP_SIZE;
                }
                if(Game::changeMap == "right") {
                    Game::previousMap = Game::map.name;
                    Game::changeMap = Game::right.name;
                    transform->position.x = -1;
                    transform->mapPosition.x = (transform->position.x + 1) / STEP_SIZE;
                    transform->position.y = transform->position.y - Game::yOffRight;
                    transform->mapPosition.y = transform->position.y / STEP_SIZE;
                }
                if(Game::changeMap == "left") {
                    Game::previousMap = Game::map.name;
                    Game::changeMap = Game::left.name;
                    transform->position.x = Game::left.sourceRectangle.w + 1 - STEP_SIZE;
                    transform->mapPosition.x = (transform->position.x - 1) / STEP_SIZE;
                    transform->position.y = transform->position.y - Game::yOffLeft;
                    transform->mapPosition.y = transform->position.y / STEP_SIZE;
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
        }
};

#endif
