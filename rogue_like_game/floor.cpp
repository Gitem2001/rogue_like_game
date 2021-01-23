#include "floor.h"

Floor::Floor(int x, int y, std::string sym) {
    this->x = x;
    this->y = y;
    this->sym_char = sym[0];
}
res_col Floor::Collide(Zombie*) {
    return CanMove;
}
res_col Floor::Collide(AidKit*) {
    return Nothing;
}
res_col Floor::Collide(Floor*) {
    return Nothing;
}
res_col Floor::Collide(Princess*) {
    return CantMove;
}
res_col Floor::Collide(Knight*) {
    return CanMove;
}
res_col Floor::Collide(Dragon*) {
    return CanMove;
}
res_col Floor::Collide(Wall*) {
    return Nothing;
}
res_col Floor::Collide(Projectile*) {
    return CanMove;
}