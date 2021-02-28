#include <iostream>
#include <fstream>
#include "./Components/TransformComponent.h"
#include "./Components/StaticTransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/RandomCtrlComp.h"
#include "./EntityManager.h"
#include "./Paths.h"

EntityManager::EntityManager() {
}

EntityManager::~EntityManager() {
    //std::cout << "EntityManager: destructor" << std::endl;
    //MakeAllEntitiesInactive();
    //DestroyInactiveEntities();
    this->DestroyAllEntities();
}
void EntityManager::DestroyAllEntities() {
    for (auto entity: entities) {
        if (entity != nullptr) {
            //std::cout << "Count: " << GetEntityCount() << " - EntityManager: DestroyAllEntities : destroied " << entity->name << std::endl;
            delete entity;
            entity = nullptr;
        }
    }
    entities.clear();
    //std::cout << " - Count: " << GetEntityCount() << std::endl;
}

void EntityManager::MakeAllEntitiesInactive() {
    for (auto& entity: entities) {
        entity->MakeItInactive();
    }
}

void EntityManager::DestroyInactiveEntities() {
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        if (!(*it)->IsActive()) {
            //std::cout << "Count: " << GetEntityCount() << " - EntityManager: DestroyInactiveEntities: destroied " << (*it)->name;
            delete (*it);
            entities.erase(it);
            //std::cout << " - Count: " << GetEntityCount() << std::endl;
        }
    }
}

void EntityManager::DestroyNOTEssentialEntities() {
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        if (!(*it)->IsEssential()) {
            //std::cout << "Count: " << GetEntityCount() << " - EntityManager: DestroyNOTEssentialEntities: destroied " << (*it)->name;
            delete (*it);
            entities.erase(it);
            //std::cout << " - Count: " << GetEntityCount() << std::endl;
        }
    }
}

void EntityManager::Update() { 
    for (auto& entity: entities) {
        entity->Update();
    }
    //DestroyInactiveEntities();
}

void EntityManager::Render() { // entities are already ordered by LayerType
    for (auto& entity: entities) {
        entity->Render();
    }
}

bool EntityManager::HasNoEntities() const {
    return entities.size() == 0;
}

unsigned int EntityManager::GetEntityCount() const {
    return entities.size();
}

std::multiset<Entity*, layerTypeCompare> EntityManager::GetEntities() const {
    return entities;
}

Entity* EntityManager::GetEntityByName(std::string entityName) const {
    for (auto* entity: entities) {
        if (entity->name.compare(entityName) == 0) {
            return entity;
        }
    }
    return nullptr;
}

std::multiset<Entity*, layerTypeCompare> EntityManager::GetEntitiesByLayer(LayerType layer) const {
    std::multiset<Entity*, layerTypeCompare> selectedEntities;
    for (auto& entity: entities) {
        if (entity->layer == layer) {
            selectedEntities.insert(entity);
        }
    }
    return selectedEntities;
}

void EntityManager::ListAllEntities() const {
    unsigned int i = 0;
    for (auto& entity: entities) {
        std::cout << "Entity[" << i << "]: " << entity->name << " - layerType:" << entity->layer << " - isEssential:" << entity->IsEssential() << " - isMainInMap:" << entity->IsMainInMap() << std::endl;
        entity->ListAllComponents();
        i++;
    }
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer, bool isEssential, bool isMainInMap) {
    Entity* entity = new Entity(*this, entityName, layer, isEssential, isMainInMap);
    entities.insert(entity);
    return *entity;
}

void EntityManager::SetAccessibilityPlayerLayerMap() {
    std::multiset<Entity*, layerTypeCompare> playerLayerEntities = this->GetEntitiesByLayer(PLAYER_LAYER);
    for (auto& entity: playerLayerEntities) {
        TransformComponent* transform = entity->GetComponent<TransformComponent>();
        if (transform) {
            transform->SetAccessibilityMap();
        }
    }
}

void EntityManager::SetAccessibilityOverTilemapLayer() {
    std::multiset<Entity*, layerTypeCompare> overTileMapLayerEntities = this->GetEntitiesByLayer(OVER_TILEMAP_LAYER);
    for (auto& entity: overTileMapLayerEntities) {
        if (entity->IsMainInMap()) {
            StaticTransformComponent* sTransform = entity->GetComponent<StaticTransformComponent>();
            if (sTransform) {
                sTransform->SetAccessibilityMap();
            }
        }
    }
}

void EntityManager::WriteTsavFile(std::string mapName) {
    fs::create_directories(tsav_dir);
    std::ofstream ofs;
    ofs.open(tsav_dir.string()+mapName+".tsav",std::ios::out);
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        if ((*it)->HasComponent<RandomCtrlComp>()) {
            TransformComponent* tc = (*it)->GetComponent<TransformComponent>();
            unsigned int rest_x = static_cast<unsigned int>(tc->position.x) % STEP_SIZE;
            if (rest_x != 0) {
                if (tc->onGoingDirection == 'x') {
                    tc->velocity.x > 0 ?
                        (tc->onGoingStep > STEP_SIZE/2 ? tc->position.x -= rest_x : tc->position.x += STEP_SIZE - rest_x) :
                        (tc->onGoingStep > STEP_SIZE/2 ? tc->position.x += STEP_SIZE - rest_x : tc->position.x -= rest_x);
                }
            }
            unsigned int rest_y = static_cast<unsigned int>(tc->position.y) % STEP_SIZE;
            if (rest_y != 0) {
                if (tc->onGoingDirection == 'y') {
                    tc->velocity.y > 0 ?
                        (tc->onGoingStep > STEP_SIZE/2 ? tc->position.y -= rest_y : tc->position.y += STEP_SIZE - rest_y) :
                        (tc->onGoingStep > STEP_SIZE/2 ? tc->position.y += STEP_SIZE - rest_y : tc->position.y -= rest_y);
                }
            }
            SpriteComponent* sc = (*it)->GetComponent<SpriteComponent>();
            ofs << (*it)->name << "PosX=" << tc->position.x / STEP_SIZE << ", "
                << (*it)->name << "PosY=" << tc->position.y / STEP_SIZE << ", "
                << (*it)->name << "IndexAnim=" << sc->animationIndex << std::endl;
        }
    }
    ofs.close();
}

void EntityManager::ShowBounding() {
    for (auto entity: entities) {
        BoundingComponent* bc = entity->GetComponent<BoundingComponent>();
        if (bc != nullptr)
            bc->showBounding = ! bc->showBounding;
    }
}
