//
// Created by Rashid on 18.01.2021.
//

#ifndef ROGUE_LIKE_GAME_KNIGHT_H
#define ROGUE_LIKE_GAME_KNIGHT_H
#include <string>
#include "character.h"
#include "Map.h"
class Knight: public Character {
public:
    Knight() = default;
    Knight(int x, int y, std::string sym, std::string hp, std::string damage, std::string vision);
    void Move(char a, Map map_);
    

private:
    
};



#endif //ROGUE_LIKE_GAME_KNIGHT_H
