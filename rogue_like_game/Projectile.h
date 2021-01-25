//
// Created by Rashid on 20.01.2021.
//

#ifndef ROGUE_LIKE_GAME_PROJECTILE_H
#define ROGUE_LIKE_GAME_PROJECTILE_H

#include "Gameobject.h"
#include <utility>
class Projectile: public  Gameobject{
public:
	void Fly();
	Projectile() = default;
	res_col Collide(Zombie*) override;
	res_col Collide(Projectile*) override;
	res_col Collide(Knight*) override;

	res_col Collide(Princess*) override;

	res_col Collide(AidKit*) override;

	res_col Collide(Dragon*) override;

	res_col Collide(Wall*) override;

	res_col Collide(Floor*) override;
	res_col Collide(Gameobject* buf);
	std::pair<int, int> direction;
	int damage;
	int x;
	int y;
    Projectile(int x,int y,std::pair<int,int> dir);
};
#endif //ROGUE_LIKE_GAME_PROJECTILE_H
