#include "./Collision.h"
#include "./Game.h"

bool Collision::IsThereACollision(Matrix<char>& accessibleTiles, int y, int x) {
    if (y == -1 || y == accessibleTiles.GetN() || x == -1 || x == accessibleTiles.GetM()) {
        return false;
    }
    char ch = accessibleTiles.Get(y,x); 
    bool accessible = atoi(&ch);
    return accessible;
}
