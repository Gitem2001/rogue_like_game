//
// Created by Rashid on 18.01.2021.
//

#ifndef ROGUE_LIKE_GAME_DRAGON_H
#define ROGUE_LIKE_GAME_DRAGON_H

#include "character.h"
#include "Projectile.h"

class Dragon: Character {
    Dragon(int x,int y);
    Projectile Attack(int x,int y);
};


#endif //ROGUE_LIKE_GAME_DRAGON_H
