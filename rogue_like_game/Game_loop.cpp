//
// Created by Rashid on 18.01.2021.
//
#include <curses.h>
#include "Game_loop.h"
#include "Knight.h"
#include "Princess.h"
#include "Zombie.h"
void Game_loop::Start_game() {  // Процедура начала игры
    this->Pers = Knight(1,1);
    game_characters.push_back(&Pers);
    Princess Princ(8,10);
    game_characters.push_back(&Princ);
    Zombie  Z1(5,5);
    game_characters.push_back(&Z1);
    Map current_map = Map();
    initscr();
    refresh();
    curs_set(0);
    clear();
    noecho();
    current_map.Paint(game_characters);
    Cont_game(current_map);
}
void Game_loop::Cont_game(Map map_) {
    char buf = getch(); // ожидаем символа от пользователя
    this->Pers.Move(buf,map_);
    map_.Paint(game_characters);
    Cont_game(map_);
    if (this->Pers.GetHp() == 0) {
        exit(0);
    }
}
