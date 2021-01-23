//
// Created by Rashid on 18.01.2021.
//

#ifndef ROGUE_LIKE_GAME_PRINCESS_H
#define ROGUE_LIKE_GAME_PRINCESS_H
#include <string>
#include "character.h"

class Princess: public Character {
public:
    Princess(int x, int y, std::string sym, std::string hp, std::string damage);
};


#endif //ROGUE_LIKE_GAME_PRINCESS_H
