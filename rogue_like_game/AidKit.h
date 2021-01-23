#pragma once
#include "Gameobject.h"
#include <string>
class AidKit:public Gameobject{
public:
	AidKit(int x, int y, std::string sym);
	res_col Collide(Zombie*) override;
	res_col Collide(AidKit*) override;
	res_col Collide(Knight*) override;

	res_col Collide(Dragon*) override;

	res_col Collide(Princess*) override;

	res_col Collide(Floor*) override;

	res_col Collide(Wall*) override;

	res_col Collide(Projectile*) override;
};


