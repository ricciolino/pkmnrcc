#include <iostream>
#include "./Entity.h"

Entity::Entity(EntityManager& manager, std::string name, LayerType layer, bool isEssential, bool isMainInMap): manager(manager), name(name), layer(layer), isEssential(isEssential), isMainInMap(isMainInMap) {
    this->isActive = true;
}

Entity::~Entity() {
    //std::cout << "Entity: " << this->name << " - layerNumber " << this->layer << ": destructor" << std::endl;
    //this->ListAllComponents();
    for (auto& mapComponent: mapComponents){
		if(mapComponent.second != nullptr){
			delete mapComponent.second;
            mapComponent.second = nullptr;
		}
	}
    mapComponents.clear(); 
}

void Entity::Update() {
    for (auto& mapComponent: mapComponents) {
        mapComponent.second->Update();    
    }
}

void Entity::Render() {
    for (auto& mapComponent: mapComponents) {
        mapComponent.second->Render();    
    }
}

void Entity::MakeItInactive() {
    this->isActive = false;
}

bool Entity::IsActive() const {
    return this->isActive;
}

bool Entity::IsEssential() const {
    return this->isEssential;
}

bool Entity::IsMainInMap() const {
    return this->isMainInMap;
}

void Entity::ListAllComponents() const {
    for (auto& mapComponent: mapComponents) {
        std::string componentName = mapComponent.first->name();
        componentName = componentName.substr(2);
        std::cout << "    component<" << componentName << ">" << std::endl;
        mapComponent.second->Print();
    }
}
