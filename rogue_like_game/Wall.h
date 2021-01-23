//
// Created by Rashid on 18.01.2021.
//

#ifndef ROGUE_LIKE_GAME_WALL_H
#define ROGUE_LIKE_GAME_WALL_H
#include <string>
#include "Gameobject.h"
class Wall: public Gameobject {
public:
    Wall(int x, int y, std::string sym);

	res_col Collide(Zombie*) override;
	res_col Collide(Wall*) override;

 	res_col Collide(Knight*) override;

	res_col Collide(Princess*) override;

	res_col Collide(AidKit*) override;

	res_col Collide(Dragon*) override;

	res_col Collide(Projectile*) override;

	res_col Collide(Floor*) override;
};


#endif //ROGUE_LIKE_GAME_WALL_H
