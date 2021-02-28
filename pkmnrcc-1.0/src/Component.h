#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>

class Entity;

class Component {
    
    public:
        /***********/
        /* MEMBERS */
        /***********/
        Entity* owner;

        /***********/
        /* METHODS */
        /***********/
        virtual void Initialize() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
        virtual void Print() const = 0;
        virtual ~Component() = default; 
};

#endif
