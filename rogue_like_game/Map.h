//
// Created by Rashid on 18.01.2021.
//

#ifndef ROGUE_LIKE_GAME_MAP_H
#define ROGUE_LIKE_GAME_MAP_H

#include <vector>
#include "character.h"
class Map {
public:
    Map();
    void Paint(std::vector<Character*> characters);
    char Get_Sym(int x,int y);
private:
    std::vector<std::vector<char>> map_;
};


#endif //ROGUE_LIKE_GAME_MAP_H
