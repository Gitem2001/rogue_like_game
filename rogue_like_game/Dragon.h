//
// Created by Rashid on 18.01.2021.
//

#ifndef ROGUE_LIKE_GAME_DRAGON_H
#define ROGUE_LIKE_GAME_DRAGON_H
#include <string>
#include "character.h"
#include "Projectile.h"

class Dragon: public Character {
public:
    Dragon(int x, int y, std::string sym, std::string hp, std::string damage);
    Projectile Attack(int x,int y);
	res_col Collide(Zombie*) override;
	res_col Collide(Dragon*) override;
	res_col Collide(Knight*) override;
	
	res_col Collide(Princess*) override;
	
	res_col Collide(AidKit*) override;
	
	res_col Collide(Floor*) override;
	
	res_col Collide(Wall*) override;
	
	res_col Collide(Projectile*) override;
	res_col Collide(Gameobject* buf);
};	


#endif //ROGUE_LIKE_GAME_DRAGON_H
