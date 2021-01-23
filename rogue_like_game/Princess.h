//
// Created by Rashid on 18.01.2021.
//

#ifndef ROGUE_LIKE_GAME_PRINCESS_H
#define ROGUE_LIKE_GAME_PRINCESS_H
#include <string>
#include "character.h"

class Princess: public Character {
public:
    Princess() = default;
    Princess(int x, int y, std::string sym, std::string hp, std::string damage);
	res_col Collide(Zombie*) override;
	res_col Collide(Princess*) override;
	res_col Collide(Knight*) override;

	res_col Collide(Floor*) override;

	res_col Collide(AidKit*) override;

	res_col Collide(Dragon*) override;

	res_col Collide(Wall*) override;

	res_col Collide(Projectile*) override;
};


#endif //ROGUE_LIKE_GAME_PRINCESS_H
