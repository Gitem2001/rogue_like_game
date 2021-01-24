//
// Created by Rashid on 18.01.2021.
//

#include "character.h"

float Character::GetDamage() {
    return this->damage;
}
std::pair<int, int> Character::GetPos() {
    return {this->x,this->y};
}

int Character::GetVision() {
    return this->vision;
}
