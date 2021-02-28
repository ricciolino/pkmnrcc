#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>
#include "Matrix.hpp"

class Collision {
    public:
        static bool IsThereACollision(Matrix<char>& accessibleTiles, int y, int x);
};

#endif
