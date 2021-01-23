//
// Created by Rashid on 20.01.2021.
//

#ifndef ROGUE_LIKE_GAME_PROJECTILE_H
#define ROGUE_LIKE_GAME_PROJECTILE_H

#include "Gameobject.h"
class Projectile: protected  Gameobject{
    void Fly(int x_goal,int y_goal);
	res_col Collide(Zombie*) override;
	res_col Collide(Projectile*) override;
	res_col Collide(Knight*) override;

	res_col Collide(Princess*) override;

	res_col Collide(AidKit*) override;

	res_col Collide(Dragon*) override;

	res_col Collide(Wall*) override;

	res_col Collide(Floor*) override;
	res_col Collide(Gameobject* buf);

public:
    Projectile(int x,int y);
};
#endif //ROGUE_LIKE_GAME_PROJECTILE_H
