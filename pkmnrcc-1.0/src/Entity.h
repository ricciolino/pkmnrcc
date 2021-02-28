#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <map>
#include "./Constants.h"
#include "./Component.h"

class EntityManager;
class Component;

class Entity {

    private:
        /***********/
        /* MEMBERS */
        /***********/
        EntityManager& manager; // a reference to its manager (to be able to get the others Components)
        bool isActive;
        bool isEssential;
        bool isMainInMap;
        std::map<const std::type_info*, Component*> mapComponents; // map which contains all the components (each one must be unique)

    public:
        /***********/
        /* MEMBERS */
        /***********/
        std::string name; // the name of the entity
        LayerType layer; // level of Layer to renderer in sequence

        /***********/
        /* METHODS */
        /***********/
        Entity(EntityManager& manager, std::string name, LayerType layer, bool isEssential = false, bool isMainInMap = false);
        ~Entity();
        void Update(); // call Update for all Components
        void Render(); // call Render for all Components 
        void MakeItInactive(); // make the entity inactive (then on the next Update of the manager will be erased form the list of Entities that the manager has)
        bool IsActive() const; // check if the entity is active
        bool IsEssential() const;
        bool IsMainInMap() const;
        void ListAllComponents() const; // prints a list of all the Components

        // use this method to add a component but check before if it already exists with the method below HasComponent
        template <typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args) {
            T* newComponent = new T(std::forward<TArgs>(args)...);
            newComponent->owner = this;
            mapComponents.emplace(std::make_pair(&typeid(*newComponent), newComponent)); // insert a new component (or change one already existing)
            newComponent->Initialize(); // call Initialize for the new component (Components override Initialize method)
            return *newComponent;
        }

        // check if an entity has a certain component
        template <typename T>
        bool HasComponent() const {
            return mapComponents.count(&typeid(T));
        }

        // return a certain component if it exist (nullptr otherwise)
        template <typename T>
        T* GetComponent() {
            if (this->HasComponent<T>())
                return static_cast<T*>(mapComponents[&typeid(T)]);
            else
                return nullptr;
        }

        /*************/
        /* OPERATORS */       
        /*************/
        bool operator< (const Entity& _entity) const { // needed for multiset ordering in EntityManager
            if (this->layer == _entity.layer)
                return this->name < _entity.name;
            return this->layer < _entity.layer;
        }
};

#endif
