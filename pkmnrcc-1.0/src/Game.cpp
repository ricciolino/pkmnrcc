#include <iostream>
#include <fstream>
#include "./Constants.h"
#include "./Paths.h"
#include "./Game.h"
#include "./TextureManager.h"
#include "./Components/TransformComponent.h"
#include "./Components/StaticTransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/StaticSpriteComponent.h"
#include "./Components/KeybCtrlCompMapMovement.h"
#include "./Components/RandomCtrlComp.h"
#include "./Components/BoundingComponent.h"

#ifdef __linux__
//    char* home = getenv("HOME"); // USERPROFILE in Windows (mac ??)
//    fs::path pkmn_dir = std::string(home) + "/.pkmnrcc";
    fs::path pkmn_dir = "../HOME/.pkmnrcc"; // this simulate the user HOME directory (remove this line and uncomment the previous 2 lines on packaging)
    fs::path sav_dir = pkmn_dir.string() + "/sav/";
    fs::path tsav_dir = pkmn_dir.string() + "/tsav/";
#elif _WIN32
//    char* home = getenv("USERPROFILE");
//    fs::path pkmn_dir = std::string(home) + "\\.pkmnrcc";
    fs::path pkmn_dir = "..\\HOME\\.pkmnrcc";
    fs::path sav_dir = pkmn_dir.string() + "\\sav\\";
    fs::path tsav_dir = pkmn_dir.string() + "\\tsav\\";
#endif

/*********************************/
/* STATIC MEMBERS INITIALIZATION */
/*********************************/
EntityManager Game::manager;
AssetManager Game::assetManager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
const Uint8* Game::keyBoardStatus = nullptr; 
Modalities Game::mode = START;
std::string Game::previousMap = "";
Map Game::map;
Map Game::up;
int Game::xOffUp;
Map Game::left;
int Game::yOffLeft;
Map Game::down;
int Game::xOffDown;
Map Game::right;
int Game::yOffRight;
std::string Game::changeMap = "";
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

Game::Game(): ticksLastFrame(0), mainPlayer(nullptr) {
    this->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
    this->dangerOfRepetition = false;
}

Game::~Game() {
    // do NOT call delete on Entity* player (it's freed inside the EntityManager)
    //std::cout << "Game destructor" << std::endl;
    if (mainPlayer != nullptr) { mainPlayer = nullptr; }
    this->ClearText(); // clear all text lines of private member 'text'
    // destroy the window, the renderer and quit from SDL
    assetManager.ClearData(); // remove and destroy fonts before to call TTF_Quit
    this->Destroy();
    this->keyBoardStatus = nullptr;
}

bool Game::IsRunning() const {
    return this->isRunning;
}

void Game::Initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    if (IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG != IMG_INIT_PNG) {
        std::cerr << "Error initializing SDL IMG" << std::endl;
        return;
    }
    if (TTF_Init() != 0) {
        std::cerr << "Error initializing SDL TTF" << std::endl;
        return;
    }
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    LoadScript("essential");

    this->text.push_back(this->MakeTextLine("New game", 0, -30, WHITE_COLOR, "charriot-36pt")); // the number passed will be the corrispectively offset to move around the text
    this->text.push_back(this->MakeTextLine("Load Game", 0, 30, WHITE_COLOR, "charriot-36pt")); // x and y coordinates start from center (on the basis of the line width and height)
    for (auto line: text) {
        if(this->choiceBox.w < line->rectLabel.w) {
            this->choiceBox.w = line->rectLabel.w+10;
            this->choiceBox.h = line->rectLabel.h;
            this->choiceBox.x = line->rectLabel.x-7;
            this->choiceBox.y = line->rectLabel.y;
        }
    }
   
    isRunning = true;
    return;
}

void Game::LoadScript(std::string scriptName) {
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
    luaL_requiref(lua, "io", luaopen_io, 1);
    luaL_requiref(lua, "string", luaopen_string, 1);

    lua.script_file("../assets/scripts/" + scriptName + ".lua");

    sol::table scriptData = lua[scriptName];

    ///////////////////////////////////////////////////////////////////////////
    // LOAD LIST OF ASSETS FROM LUA CONFIG FILE
    ///////////////////////////////////////////////////////////////////////////
    sol::table scriptAssets = scriptData["assets"];

    unsigned int assetIndex = 0;
    while (true) {
        sol::optional<sol::table> existsAssetIndexNode = scriptAssets[assetIndex];
        if (existsAssetIndexNode == sol::nullopt) {
            break;
        } else {
            sol::table asset = scriptAssets[assetIndex];
            std::string assetType = asset["type"];
            if (assetType.compare("texture") == 0) {
                std::string assetId = asset["id"];
                std::string assetFile = asset["file"];
                assetManager.AddTexture(assetId, assetFile.c_str());
            }
            if (assetType.compare("font") == 0) {
                std::string assetId = asset["id"];
                std::string assetFile = asset["file"];
                int fontSize = asset["fontSize"];
                assetManager.AddFont(assetId, assetFile.c_str(), fontSize);
            }
        }
        assetIndex++;
    }

    Game::changeMap = ""; // initialized to "" and in Update() method check if it is != to "" --> means change map activated
    ///////////////////////////////////////////////////////////////////////////
    // LOAD MAP AND TILE INFORMATION FROM LUA CONFIG FILE
    ///////////////////////////////////////////////////////////////////////////
    sol::optional<sol::table> existMap = scriptData["map"];
    if (existMap != sol::nullopt) {
        sol::table locationMap = scriptData["map"];
        map.LoadMap(
            locationMap["name"],
            locationMap["file"],
            static_cast<int>(locationMap["mapSizeX"]),
            static_cast<int>(locationMap["mapSizeY"])
        );
    } else {
        Game::map.ClearMap();
    }

    sol::optional<sol::table> existMapUp = scriptData["mapUp"];
    xOffUp = 0;
    if (existMapUp != sol::nullopt) {
        sol::table locationMapUp = scriptData["mapUp"];
        up.LoadMap(
            locationMapUp["name"],
            locationMapUp["file"],
            static_cast<int>(locationMapUp["mapSizeX"]),
            static_cast<int>(locationMapUp["mapSizeY"])
        );
        xOffUp = static_cast<int>(locationMapUp["xOff"]);
    } else {
        Game::up.ClearMap();
    }
    sol::optional<sol::table> existMapRight = scriptData["mapRight"];
    yOffRight = 0;
    if (existMapRight != sol::nullopt) {
        sol::table locationMapRight = scriptData["mapRight"];
        right.LoadMap(
            locationMapRight["name"],
            locationMapRight["file"],
            static_cast<int>(locationMapRight["mapSizeX"]),
            static_cast<int>(locationMapRight["mapSizeY"])
        );
        yOffRight = static_cast<int>(locationMapRight["yOff"]);
    } else {
        Game::right.ClearMap();
    }
    sol::optional<sol::table> existMapLeft = scriptData["mapLeft"];
    yOffLeft = 0;
    if (existMapLeft != sol::nullopt) {
        sol::table locationMapLeft = scriptData["mapLeft"];
        left.LoadMap(
            locationMapLeft["name"],
            locationMapLeft["file"],
            static_cast<int>(locationMapLeft["mapSizeX"]),
            static_cast<int>(locationMapLeft["mapSizeY"])
        );
        yOffLeft = static_cast<int>(locationMapLeft["yOff"]);
    } else {
        Game::left.ClearMap();
    }
    sol::optional<sol::table> existMapDown = scriptData["mapDown"];
    xOffDown = 0;
    if (existMapDown != sol::nullopt) {
        sol::table locationMapDown = scriptData["mapDown"];
        down.LoadMap(
            locationMapDown["name"],
            locationMapDown["file"],
            static_cast<int>(locationMapDown["mapSizeX"]),
            static_cast<int>(locationMapDown["mapSizeY"])
        );
        xOffDown = static_cast<int>(locationMapDown["xOff"]);
    } else {
        Game::down.ClearMap();
    }

    ///////////////////////////////////////////////////////////////////////////
    // LOAD ENTITIES AND COMPONENTS FROM LUA CONFIG FILE
    ///////////////////////////////////////////////////////////////////////////
    sol::table levelEntities = scriptData["entities"];
    unsigned int entityIndex = 0;
    while (true) {
        sol::optional<sol::table> existsEntityIndexNode = levelEntities[entityIndex];
        if (existsEntityIndexNode == sol::nullopt) {
            break;
        }
        else {
            sol::table entity = levelEntities[entityIndex];
            std::string entityName = entity["name"];
            LayerType entityLayerType = static_cast<LayerType>(static_cast<int>(entity["layer"]));
            bool isEssential = static_cast<bool>(entity["isEssential"]);
            bool isMainInMap = static_cast<bool>(entity["isMainInMap"]);

            // Add new entity
            auto& newEntity(manager.AddEntity(entityName, entityLayerType, isEssential, isMainInMap));

            // Add Transform Component
            sol::optional<sol::table> existsTransformComponent = entity["components"]["transform"];
            if (existsTransformComponent != sol::nullopt) {
                if (!newEntity.HasComponent<TransformComponent>()) {
                    newEntity.AddComponent<TransformComponent>(
                        static_cast<int>(entity["components"]["transform"]["position"]["x"]),
                        static_cast<int>(entity["components"]["transform"]["position"]["y"]),
                        static_cast<int>(entity["components"]["transform"]["width"]),
                        static_cast<int>(entity["components"]["transform"]["height"]),
                        static_cast<int>(entity["components"]["transform"]["scale"]),
                        static_cast<float>(entity["components"]["transform"]["velocitySize"])
                    );
                }
            }

            // Add StaticTransform Component
            sol::optional<sol::table> existsStaticTransformComponent = entity["components"]["staticTransform"];
            if (existsStaticTransformComponent != sol::nullopt) {
                if (!newEntity.HasComponent<StaticTransformComponent>()) {
                    newEntity.AddComponent<StaticTransformComponent>(
                        static_cast<int>(entity["components"]["staticTransform"]["position"]["x"]),
                        static_cast<int>(entity["components"]["staticTransform"]["position"]["y"]),
                        static_cast<int>(entity["components"]["staticTransform"]["width"]),
                        static_cast<int>(entity["components"]["staticTransform"]["height"]),
                        static_cast<int>(entity["components"]["staticTransform"]["scale"])
                    );
                }
            }

            // Add sprite component
            sol::optional<sol::table> existsSpriteComponent = entity["components"]["sprite"];
            if (existsSpriteComponent != sol::nullopt) {
                std::string textureId = entity["components"]["sprite"]["textureAssetId"];
                bool isAnimated = entity["components"]["sprite"]["animated"];
                if (!newEntity.HasComponent<SpriteComponent>()) {
                    if (isAnimated) {
                        newEntity.AddComponent<SpriteComponent>(
                            textureId,
                            static_cast<int>(entity["components"]["sprite"]["frameCount"]),
                            static_cast<bool>(entity["components"]["sprite"]["hasDirections"]),
                            static_cast<bool>(entity["components"]["sprite"]["fixed"]),
                            static_cast<unsigned int>(entity["components"]["sprite"]["animationIndex"])
                        );
                    } else {
                        newEntity.AddComponent<SpriteComponent>(
                            textureId,
                            static_cast<bool>(entity["components"]["sprite"]["fixed"]),
                            static_cast<unsigned int>(entity["components"]["sprite"]["animationIndex"])
                        );
                    }
                }
            }

            // Add staticSprite component
            sol::optional<sol::table> existsStaticSpriteComponent = entity["components"]["staticSprite"];
            if (existsStaticSpriteComponent != sol::nullopt) {
                std::string textureId = entity["components"]["staticSprite"]["textureAssetId"];
                if (!newEntity.HasComponent<StaticSpriteComponent>()) {
                    newEntity.AddComponent<StaticSpriteComponent>(
                        textureId,
                        static_cast<bool>(entity["components"]["staticSprite"]["fixed"]),
                        static_cast<unsigned int>(entity["components"]["staticSprite"]["animationIndex"])
                    );
                }
            }

            // Add random bound component
            sol::optional<sol::table> existsBoundComponent = entity["components"]["bound"];
            if (existsBoundComponent != sol::nullopt) {
                if (!newEntity.HasComponent<BoundingComponent>()) {
                    newEntity.AddComponent<BoundingComponent>(
                        entity["components"]["bound"]["xLeft"],
                        entity["components"]["bound"]["xRight"],
                        entity["components"]["bound"]["yUp"],
                        entity["components"]["bound"]["yDown"],
                        SDL_Color{
                            static_cast<Uint8>(entity["components"]["bound"]["color"]["r"]),
                            static_cast<Uint8>(entity["components"]["bound"]["color"]["g"]),
                            static_cast<Uint8>(entity["components"]["bound"]["color"]["b"]),
                            static_cast<Uint8>(entity["components"]["bound"]["color"]["a"])
                        },
                        entity["components"]["bound"]["fontFamily"]
                    );
                }
            }

            // Add input control component
            sol::optional<sol::table> existsInputComponent = entity["components"]["input"];
            if (existsInputComponent != sol::nullopt) {
                if (!newEntity.HasComponent<KeybCtrlCompMapMovement>()) {
                    newEntity.AddComponent<KeybCtrlCompMapMovement>();
                }
            }

            // Add random control component
            sol::optional<sol::table> existsRandInputComponent = entity["components"]["randInput"];
            if (existsRandInputComponent != sol::nullopt) {
                if (!newEntity.HasComponent<RandomCtrlComp>()) {
                    newEntity.AddComponent<RandomCtrlComp>(entity["components"]["randInput"]["maxRndFrequency"],entity["components"]["randInput"]["minRndFrequency"]);
                }
            }
        }
        entityIndex++;
    }

    ///////////////////////////////////////////////////////////////////////////
    // SET MAIN PLAYER AND SET THE INITIAL POSITION OF THE MAPS
    ///////////////////////////////////////////////////////////////////////////
    if(scriptName=="player") {
        mainPlayer = manager.GetEntityByName("player");
        this->previousMap = this->map.name; // at the beginning (only essential script loaded) the previousMap it's the same as map
    } else if(scriptName!="essential"){
        TransformComponent* mainPlayerTransform = mainPlayer->GetComponent<TransformComponent>();
        map.destinationRectangle.x = -mainPlayerTransform->position.x + WINDOW_WIDTH / 2;
        map.destinationRectangle.y = -mainPlayerTransform->position.y + WINDOW_HEIGHT / 2;
        up.destinationRectangle.x = xOffUp + (-mainPlayerTransform->position.x + WINDOW_WIDTH / 2);
        up.destinationRectangle.y = -up.sourceRectangle.h + (-mainPlayerTransform->position.y + WINDOW_HEIGHT / 2);
        right.destinationRectangle.x = map.sourceRectangle.w + (-mainPlayerTransform->position.x + WINDOW_WIDTH / 2);
        right.destinationRectangle.y = yOffRight + (-mainPlayerTransform->position.y + WINDOW_HEIGHT / 2);
        left.destinationRectangle.x = -left.sourceRectangle.w + (-mainPlayerTransform->position.x + WINDOW_WIDTH / 2);
        left.destinationRectangle.y = yOffLeft + (-mainPlayerTransform->position.y + WINDOW_HEIGHT / 2);
        down.destinationRectangle.x = xOffDown + (-mainPlayerTransform->position.x + WINDOW_WIDTH / 2);
        down.destinationRectangle.y = map.sourceRectangle.h + (-mainPlayerTransform->position.y + WINDOW_HEIGHT / 2);
        manager.SetAccessibilityPlayerLayerMap();
        manager.SetAccessibilityOverTilemapLayer();
    }
}

void Game::ProcessInput() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT: { // es. premo ALT+F4
            isRunning = false;
            fs::remove_all(tsav_dir);
            fs::create_directories(tsav_dir);
            break;
        }
        case SDL_KEYDOWN: {
            keyBoardStatus = SDL_GetKeyboardState(nullptr); // take a snapshot of the keyboard 
            if (!dangerOfRepetition) {
                if (this->mode == NORMAL && (keyBoardStatus[SDL_SCANCODE_Q] || keyBoardStatus[SDL_SCANCODE_ESCAPE])) {
                    this->text.push_back(this->MakeTextLine("Do you want to quit the game?", 0, -40, RED_COLOR, "charriot-36pt")); // the number passed will be the corrispectively offset to move around the text
                    this->text.push_back(this->MakeTextLine("Yes", 0, 0, BLUE_COLOR, "charriot-25pt")); // the number passed will be the corrispectively offset to move around the text
                    this->text.push_back(this->MakeTextLine("No", 0, 30, YELLOW_COLOR, "charriot-25pt")); // x and y coordinates start from center (on the basis of the line width and height)
                    this->choiceBox.w = text.at(1)->rectLabel.w+10;
                    this->choiceBox.h = text.at(1)->rectLabel.h;
                    this->choiceBox.x = text.at(1)->rectLabel.x-7;
                    this->choiceBox.y = text.at(1)->rectLabel.y;
                    this->mode = QUIT;
                } else if (this->mode == NORMAL && keyBoardStatus[SDL_SCANCODE_A]) {
                    Game::manager.ListAllEntities();
                    std::cout << "----------------------------------------------" << std::endl;
                } else if (this->mode == NORMAL && keyBoardStatus[SDL_SCANCODE_S]) {
                    map.accessibleTiles.Print(true);
                } else if (this->mode == NORMAL && keyBoardStatus[SDL_SCANCODE_D]) {
                    std::cout << "manager.GetEntityCount() = " << manager.GetEntityCount()<< std::endl;
                } else if (this->mode == NORMAL && keyBoardStatus[SDL_SCANCODE_F]) {
                    manager.ShowBounding();
                } else if (this->mode == NORMAL && keyBoardStatus[SDL_SCANCODE_W]) {
                    this->text.push_back(this->MakeTextLine("Do you want to save the game?", 0, -40, WHITE_COLOR, "charriot-36pt")); // the number passed will be the corrispectively offset to move around the text
                    this->text.push_back(this->MakeTextLine("Yes", 0, 0, WHITE_COLOR, "charriot-25pt")); // the number passed will be the corrispectively offset to move around the text
                    this->text.push_back(this->MakeTextLine("No", 0, 30, WHITE_COLOR, "charriot-25pt")); // x and y coordinates start from center (on the basis of the line width and height)
                    this->choiceBox.w = text.at(1)->rectLabel.w+10;
                    this->choiceBox.h = text.at(1)->rectLabel.h;
                    this->choiceBox.x = text.at(1)->rectLabel.x-7;
                    this->choiceBox.y = text.at(1)->rectLabel.y;
                    this->mode = SAVE;
                } else if ((this->mode == SAVE || this->mode == QUIT) && (keyBoardStatus[SDL_SCANCODE_X] || keyBoardStatus[SDL_SCANCODE_ESCAPE])) {
                    this->mode = NORMAL;
                    this->ClearText();
                } else if (this->mode == QUIT && (keyBoardStatus[SDL_SCANCODE_Z] || keyBoardStatus[SDL_SCANCODE_RETURN])) {
                    if(this->choiceBox.y < 450) { // Si, esco dal gioco
                        isRunning = false;
                        fs::remove_all(tsav_dir);
                        fs::create_directories(tsav_dir);
                        this->mode = QUIT;
                    } else {
                        this->mode = NORMAL;
                    } 
                    this->ClearText();
                } else if (this->mode == SAVE && (keyBoardStatus[SDL_SCANCODE_Z] || keyBoardStatus[SDL_SCANCODE_RETURN])) {
                    if(this->choiceBox.y < 450) { // Si, salvo il gioco
                        manager.WriteTsavFile(map.name);
                        for(auto& p: fs::directory_iterator(sav_dir.string())) {
                            if (p.path().extension() == ".tsav") {
                                fs::remove(p.path());
                            }
                        }
                        fs::path from_path = tsav_dir.string() + map.name + ".tsav";
                        fs::path to_path = sav_dir.string() + map.name + ".tsav";
                        fs::copy_file(from_path,to_path);
                        std::ofstream ofs;
                        ofs.open(sav_dir.string()+"game.sav",std::ios::out);
                        ofs << map.name << std::endl;
                        ofs << "playerPosX=" << this->mainPlayer->GetComponent<TransformComponent>()->mapPosition.x;
                        ofs << ", playerPosY=" << this->mainPlayer->GetComponent<TransformComponent>()->mapPosition.y;
                        ofs << ", playerIndexAnim=" << this->mainPlayer->GetComponent<SpriteComponent>()->animationIndex << std::endl;
                        ofs.close();
                    }
                    this->mode = NORMAL;
                    this->ClearText();
                } else if (this->mode == START && (keyBoardStatus[SDL_SCANCODE_Z] || keyBoardStatus[SDL_SCANCODE_RETURN])) {
                    if(this->choiceBox.y > 450) { // Load game
                        std::ifstream ifs(sav_dir.string()+"game.sav");
                        std::string isSaved;
                        ifs >> isSaved;
                        ifs.close();
                        if (isSaved != "") {
                            fs::path from_path = sav_dir.string() + isSaved + ".tsav";
                            fs::path to_path = tsav_dir.string() + isSaved + ".tsav";
                            fs::copy_file(from_path,to_path);
                            LoadScript("player");
                            LoadScript(isSaved);
                            this->mode = NORMAL;
                            this->ClearText();
                        } else { // There is no saved game
                            if (this->text.size() < 3) {
                                this->text.push_back(this->MakeTextLine("There is no saved game", 0, 60, FUXIA_COLOR, "charriot-14pt"));
                            }
                            this->flagTicks = SDL_GetTicks();
                        } 
                    } else { // New game
                        fs::remove_all(sav_dir);
                        fs::create_directories(sav_dir);
                        LoadScript("player");
                        LoadScript("mappa1");
                        this->mode = NORMAL;
                        this->ClearText();
                    }
                } else if (this->mode == START && keyBoardStatus[SDL_SCANCODE_UP] && this->choiceBox.y > 450) {
                    if (this->text.size() == 3) { this->text.erase(this->text.end() - 1); }
                    this->choiceBox.y -= 60;
                } else if (this->mode == START && keyBoardStatus[SDL_SCANCODE_DOWN] && this->choiceBox.y < 450) {
                    this->choiceBox.y += 60;
                } else if ((this->mode == SAVE || this->mode == QUIT) && keyBoardStatus[SDL_SCANCODE_UP] && this->choiceBox.y > 450) {
                    this->choiceBox.y -= 30;
                } else if ((this->mode == SAVE || this->mode == QUIT) && keyBoardStatus[SDL_SCANCODE_DOWN] && this->choiceBox.y < 450) {
                    this->choiceBox.y += 30;
                }
            }
            this->dangerOfRepetition = true;
            break;
        }
        case SDL_KEYUP: {
            this->dangerOfRepetition = false;
            break;
        }
        default: {
            break;
        }
    }
}

void Game::Update() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));
    ticksLastFrame = SDL_GetTicks(); // Sets the new ticks for the current frame to be used in the next pass

    if (this->mode == NORMAL) {
        manager.Update(); // update all entities

        // note: when in KeybCtrlCompMapMovement change map, Game::changeMap get the corresponding name to the changed map (e.g. Game::changeMap == left --> then Game::changeMap = "smeraldopoli")
        // also note that: until the step is completed (onGoingStep > 0) in both cases in which either the map is changed or not the Game::changeMap variable will be temporaly set to one of left,down,up,right
        // whereas the real mapName something else like e.g. : mapLeft
        if(Game::changeMap != "" && Game::changeMap != "up" && Game::changeMap != "down" && Game::changeMap != "left" && Game::changeMap != "right") { // so need to exclude this cases above
            manager.WriteTsavFile(Game::previousMap);
            manager.DestroyNOTEssentialEntities();
            LoadScript(Game::changeMap);
            Game::changeMap = "";
        }

        if (mainPlayer) { // check if the game has started, and so if the mainPlayer pointer has been initialized
            TransformComponent* mainPlayerTransform = mainPlayer->GetComponent<TransformComponent>();
            HandleCameraMovement(mainPlayerTransform); // if the mainPlayer has moved, move also the camera
        }
    }
}

void Game::RenderChoiceBox() {
    this->choiceBox2.w = this->choiceBox.w + 2;
    this->choiceBox3.w = this->choiceBox.w + 4;
    this->choiceBox4.w = this->choiceBox.w + 6;
    this->choiceBox2.h = this->choiceBox.h + 2;
    this->choiceBox3.h = this->choiceBox.h + 4;
    this->choiceBox4.h = this->choiceBox.h + 6;
    this->choiceBox2.y = this->choiceBox.y - 1;
    this->choiceBox3.y = this->choiceBox.y - 2;
    this->choiceBox4.y = this->choiceBox.y - 3;
    this->choiceBox2.x = this->choiceBox.x - 1;
    this->choiceBox3.x = this->choiceBox.x - 2;
    this->choiceBox4.x = this->choiceBox.x - 3;
    SDL_RenderDrawRect(this->renderer,&this->choiceBox);
    SDL_RenderDrawRect(this->renderer,&this->choiceBox2);
    SDL_RenderDrawRect(this->renderer,&this->choiceBox3);
    SDL_RenderDrawRect(this->renderer,&this->choiceBox4);
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    switch(mode) {
        case START:
            for (auto [i,line] = std::tuple{1,this->text.begin()}; line != this->text.end(); ++line, i++) {
                if (i < 3) {
                    FontManager::Draw((*line)->label,(*line)->rectLabel);
                } else { // means the user has clicked Load Game but there is no Saved Game
                    Uint16 a = 50 + (255 * (SDL_GetTicks() - flagTicks)) / 1000; // 1000 means 1 sec
                    if (a > 255) a = 255;
                    SDL_SetTextureBlendMode( (*line)->label, SDL_BLENDMODE_BLEND );
                    SDL_SetTextureAlphaMod( (*line)->label, a );
                    SDL_RenderCopy(renderer, (*line)->label, NULL, &(*line)->rectLabel);
                }
            }
            SDL_SetRenderDrawColor(this->renderer,GREEN_COLOR.r,GREEN_COLOR.g,GREEN_COLOR.b,GREEN_COLOR.a);
            this->RenderChoiceBox();
        break;
        case NORMAL:
            if (manager.HasNoEntities()) { return; }
            this->DrawMaps();
            manager.Render();
        break;
        case QUIT:
            for(auto line: this->text) { FontManager::Draw(line->label,line->rectLabel); }
            SDL_SetRenderDrawColor(this->renderer,FUXIA_COLOR.r,FUXIA_COLOR.g,FUXIA_COLOR.b,FUXIA_COLOR.a);
            this->RenderChoiceBox();
        break;
        case SAVE:
            for(auto line: this->text) { FontManager::Draw(line->label,line->rectLabel); }
            SDL_SetRenderDrawColor(this->renderer,RED_COLOR.r,RED_COLOR.g,RED_COLOR.b,RED_COLOR.a);
            this->RenderChoiceBox();
        break;
    }

    SDL_RenderPresent(renderer);
}

void Game::DrawMaps() const {
    TextureManager::Draw(this->map.mapImg, this->map.sourceRectangle, this->map.destinationRectangle, SDL_FLIP_NONE);
    if (up.mapImg != nullptr) {
        TextureManager::Draw(this->up.mapImg, this->up.sourceRectangle, this->up.destinationRectangle, SDL_FLIP_NONE);
    }
    if (left.mapImg != nullptr) {
        TextureManager::Draw(this->left.mapImg, this->left.sourceRectangle, this->left.destinationRectangle, SDL_FLIP_NONE);
    }
    if (right.mapImg != nullptr) {
        TextureManager::Draw(this->right.mapImg, this->right.sourceRectangle, this->right.destinationRectangle, SDL_FLIP_NONE);
    }
    if (down.mapImg != nullptr) {
        TextureManager::Draw(this->down.mapImg, this->down.sourceRectangle, this->down.destinationRectangle, SDL_FLIP_NONE);
    }
}

TextLine* Game::MakeTextLine(const std::string& text, const int x, const int y, const SDL_Color& color, const std::string& font) {
    SDL_Surface* surface = TTF_RenderText_Blended(Game::assetManager.GetFont(font), text.c_str(), color);
    SDL_Texture* label = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect rectLabel;
    SDL_QueryTexture(label, nullptr, nullptr, &rectLabel.w, &rectLabel.h);
    rectLabel.x = (WINDOW_WIDTH - rectLabel.w) / 2 + x;
    rectLabel.y = (WINDOW_HEIGHT - rectLabel.h) / 2 + y;
    TextLine* line = new TextLine(rectLabel,label);
    return line;
}
void Game::ClearText() {
    for (auto line: this->text) {
        if (line->label != nullptr)
            //std::cout << "Destroyed texture line, ptr label = " << line->label << std::endl;
            SDL_DestroyTexture(line->label);
    }
    this->text.clear();
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Game::HandleCameraMovement(Component* comp) {
    TransformComponent* mainPlayerTransform = static_cast<TransformComponent*>(comp);
    camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);
}

