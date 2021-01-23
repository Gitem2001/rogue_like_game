//
// Created by Rashid on 18.01.2021.
//

#ifndef ROGUE_LIKE_GAME_GAMEOBJECT_H
#define ROGUE_LIKE_GAME_GAMEOBJECT_H
enum  res_col{ CanMove, CantMove, CanAttack, AidHP, Damage, Destroy, Nothing };
class Wall;
class Knight;
class Zombie;
class Dragon;
class Princess;
class AidKit;
class Projectile;
class Floor;
class Gameobject {
public:
    char GetSym();

    virtual res_col Collide(Wall*) = 0;

    virtual res_col Collide(Knight*) = 0;

    virtual res_col Collide(Zombie*) = 0;

    virtual res_col Collide(Dragon*) = 0;

    virtual res_col Collide(Princess*) = 0;

    virtual res_col Collide(AidKit*) = 0;

    virtual res_col Collide(Projectile*) = 0;

    virtual res_col Collide(Floor*) = 0;
protected:
    int x;
    int y;
    char sym_char;

};


#endif //ROGUE_LIKE_GAME_GAMEOBJECT_H
