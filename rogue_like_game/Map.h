//
// Created by Rashid on 18.01.2021.
//

#ifndef ROGUE_LIKE_GAME_MAP_H
#define ROGUE_LIKE_GAME_MAP_H

#include <vector>
#include "character.h"
#include "Knight.h"
#include "Princess.h"
#include <memory>
class Map {
public:
    Map();
    void Paint();
    char Get_Sym(int x,int y);
    void Paint_Win();
    int Paint_Lose();
    void Win_Or_Lose();
    std::shared_ptr <Knight> Pers;
    std::shared_ptr <Princess> Princ;
    std::vector<std::vector<std::shared_ptr<Gameobject>>> map_;
};


#endif //ROGUE_LIKE_GAME_MAP_H
