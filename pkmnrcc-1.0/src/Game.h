#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <lua5.3/sol.hpp>
#include "./Entity.h"
#include "./Component.h"
#include "./EntityManager.h"
#include "./AssetManager.h"
#include "./Map.h"

class AssetManager;

struct TextLine {
    SDL_Rect rectLabel;
    SDL_Texture* label;
    TextLine(SDL_Rect& _rectLabel, SDL_Texture* _label) : rectLabel(_rectLabel), label(_label) {}
};

class Game {

    private:
        /***********/
        /* MEMBERS */
        /***********/
        bool isRunning; // when become false stop the game
        SDL_Window* window; // the game window
        std::vector<TextLine*> text; // print lines of text
        SDL_Rect choiceBox; // the box surrounding the choice 
        SDL_Rect choiceBox2; // the box surrounding the choice (to make more large the pixel size)
        SDL_Rect choiceBox3; // the box surrounding the choice (to make more large the pixel size) 
        SDL_Rect choiceBox4; // the box surrounding the choice (to make more large the pixel size) 
        bool dangerOfRepetition; // avoid repentinely repetition of the same key (set to 0 in SDLK_UP event)

        /***********/
        /* METHODS */
        /***********/
        TextLine* MakeTextLine(const std::string& text, const int x, const int y, const SDL_Color& color, const std::string& font); // Make a line of text to add to 'text' vector
        void RenderChoiceBox();
        void ClearText(); // clean text vector
    
    public:
        /***********/
        /* MEMBERS */
        /***********/
        static SDL_Renderer* renderer; // the renderer for the window
        static EntityManager manager; // manage all the entities and their components
        static AssetManager assetManager; // Loads all textures, fonts and sounds, cleared each LoadLocation
        static SDL_Event event; // to poll event
        static const Uint8* keyBoardStatus; // to view the status of the keyboard on the ProcessingInput method 
        static SDL_Rect camera; // the visual seen into the window
        static Modalities mode; // handle the modalities to render
        static Map map; // game map, cleared each LoadLocation
        static std::string previousMap; // keep track of the map to where is going away and write the tsav files
        static Map up; // game map, cleared each LoadLocation
        static int xOffUp;
        static Map left; // game map, cleared each LoadLocation
        static int yOffLeft;
        static Map down; // game map, cleared each LoadLocation
        static int xOffDown;
        static Map right; // game map, cleared each LoadLocation
        static int yOffRight;
        static std::string changeMap;
        int ticksLastFrame; // ms elapsed from the SDL_Init, updated each frame
        int flagTicks; // flag used to make effects (e.g. fading on text) 
        Entity* mainPlayer; // don't clear this Entity in Game destructor, it's cleared into the EntityManager destructor

        /***********/
        /* METHODS */
        /***********/
        Game(); // constructor
        ~Game(); // destructor
        void Initialize(int width, int height); // initialize all SDL stuffs, and load the starting location
        void ProcessInput(); // process events input
        void Update(); // adjust the time-step and update all entities
        void Render(); // render all entities 
        void Destroy(); // destroy the window, the renderer and quit from SDL
        bool IsRunning() const; // check if the game is running
        void LoadScript(std::string scriptName); // load location from LUA script
        void DrawMaps() const; // Handles the draws of the maps
        void HandleCameraMovement(Component* comp); // move the camera if the mainPlayer moves
};



#endif
