//
// Created by Rashid on 18.01.2021.
//

#ifndef ROGUE_LIKE_GAME_GAME_LOOP_H
#define ROGUE_LIKE_GAME_GAME_LOOP_H
#include "Knight.h"
class Game_loop {
public:
    Game_loop() = default;
    void Start_game();
    void Cont_game(Map map_);
private:
    std::vector<Character*> game_characters;
    Knight Pers;
};


#endif //ROGUE_LIKE_GAME_GAME_LOOP_H
