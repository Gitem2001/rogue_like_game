//
// Created by Rashid on 18.01.2021.
//

#ifndef ROGUE_LIKE_GAME_ZOMBIE_H
#define ROGUE_LIKE_GAME_ZOMBIE_H
#include <string>
#include "character.h"

class Zombie : public Character {
public:
    Zombie(int x, int y, std::string sym, std::string hp, std::string damage);
};


#endif //ROGUE_LIKE_GAME_ZOMBIE_H
