#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "./Entity.h"
#include "./Component.h"
#include <set>

struct layerTypeCompare { // multiset ordered by Entity logic order (by LayerType)
    bool operator() (const Entity* lhs, const Entity* rhs) const {
        return (*lhs < *rhs);
    }
};

class EntityManager {

    private:
        /***********/
        /* MEMBERS */
        /***********/
        std::multiset<Entity*, layerTypeCompare> entities; // entities ordered by LayerType

   public:
        /***********/
        /* METHODS */
        /***********/
        EntityManager(); // constructor
        ~EntityManager(); // destructor
        void DestroyAllEntities(); // destroy all entities
        void MakeAllEntitiesInactive(); // set all entities inactives
        void DestroyInactiveEntities(); // destroy all inactives entities
        void DestroyNOTEssentialEntities(); // destroy all NOT esseential entities
        void Update(); // update all entities and destoy those one that are become inactive
        void Render(); // render all entities in sequence by layerType
        bool HasNoEntities() const; // check if there is at least one entity
        void ListAllEntities() const; // print a list of all entities and their components 
        unsigned int GetEntityCount() const; // get the number of entities
        std::multiset<Entity*, layerTypeCompare> GetEntities() const; // return a copy of the entities vector
        std::multiset<Entity*, layerTypeCompare> GetEntitiesByLayer(LayerType layer) const; // return a sub-multiset with all the entities with a certain LayerType
        Entity* GetEntityByName(std::string entityName) const; // return the first occurrency of the the entity with name 'entityName'
        Entity& AddEntity(std::string entityName, LayerType layer, bool isEssential, bool isMainInMap); // add a new entity (return also a reference to the new one just created)
        void SetAccessibilityPlayerLayerMap();
        void SetAccessibilityOverTilemapLayer();
        void WriteTsavFile(std::string mapName);
        void ShowBounding();

        //template <typename T>
        //std::multiset<Entity*, layerTypeCompare> GetEntitiesByComponents() const {
            //std::multiset<Entity*, layerTypeCompare> selectedEntities;
            //for (auto& entity: entities) {
                //if (entity->HasComponent<T>) {
                    //selectedEntities.insert(entity);
                //}
            //}
            //return selectedEntities;
        //}
};

#endif
