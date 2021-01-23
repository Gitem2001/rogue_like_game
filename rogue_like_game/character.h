//
// Created by Rashid on 18.01.2021.
//

#ifndef ROGUE_LIKE_GAME_CHARACTER_H
#define ROGUE_LIKE_GAME_CHARACTER_H


#include <utility>
#include "Gameobject.h"

class Character : public Gameobject {
protected:
    float hp;
    float damage;
    float max_hp;
    int vision;
public:
    float GetHp();
    float GetDamage();
    char GetSym();
    int  GetVision();
    std::pair<int, int> GetPos();
};

#endif //ROGUE_LIKE_GAME_CHARACTER_H
