//
// Created by Rashid on 18.01.2021.
//

#ifndef ROGUE_LIKE_GAME_DRAGON_H
#define ROGUE_LIKE_GAME_DRAGON_H
#include <string>
#include "character.h"
#include "Projectile.h"

class Dragon: public Character {
public:
    Dragon(int x, int y, std::string sym, std::string hp, std::string damage);
    Projectile Attack(int x,int y);
};


#endif //ROGUE_LIKE_GAME_DRAGON_H
