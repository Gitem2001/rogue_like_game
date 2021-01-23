//
// Created by Rashid on 20.01.2021.
//

#ifndef ROGUE_LIKE_GAME_PROJECTILE_H
#define ROGUE_LIKE_GAME_PROJECTILE_H

#include "Gameobject.h"
class Projectile: protected  Gameobject{
    void Fly(int x_goal,int y_goal);

public:
    Projectile(int x,int y);
};
#endif //ROGUE_LIKE_GAME_PROJECTILE_H
