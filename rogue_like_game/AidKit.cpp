#include "AidKit.h"
AidKit::AidKit(int x, int y, std::string sym) {
    this->x = x;
    this->y = y;
    this->sym_char = sym[0];
}
res_col AidKit::Collide(Zombie*) {
    return Destroy;
}
res_col AidKit::Collide(AidKit*) {
    return Nothing;
}
res_col AidKit::Collide(Dragon*) {
    return Destroy;
}
res_col AidKit::Collide(Princess*) {
    return Destroy;
}
res_col AidKit::Collide(Knight*) {
    return AidHP;
}
res_col AidKit::Collide(Floor*) {
    return Nothing;
}
res_col AidKit::Collide(Wall*) {
    return Nothing;
}
res_col AidKit::Collide(Projectile*) {
    return Destroy;
}