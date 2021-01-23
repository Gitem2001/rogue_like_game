//
// Created by Rashid on 18.01.2021.
//

#include "character.h"

float Character::GetDamage() {
    return this->damage;
}
float Character::GetHp() {
    return this->hp;
}
std::pair<int, int> Character::GetPos() {
    return {this->x,this->y};
}
char Character::GetSym() {
    return this->sym_char;
}
int Character::GetVision() {
    return this->vision;
}
