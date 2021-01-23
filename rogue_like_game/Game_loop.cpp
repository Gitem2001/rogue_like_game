//
// Created by Rashid on 18.01.2021.
//
#include <curses.h>
#include <fstream>
#include <map>
#include "Game_loop.h"
#include "Knight.h"
#include "Princess.h"
#include "Zombie.h"
#include "Dragon.h"
void Game_loop::Start_game() {  // Процедура начала игры
    std::ifstream fin("config.txt");
    std::string buf;
    std::map<std::string, std::string> constants;
    while (fin >> buf) {
       auto index =buf.find('=');
       constants.emplace(buf.substr(0, index), buf.substr(index+1));
    }
    this->Pers = Knight(1, 1, constants["KNIGHT_CHAR"], constants["KNIGHT_HP"], constants["KNIGHT_DAMAGE"], constants["KNIGHT_VISION"]);
    game_characters.push_back(&Pers);
    Princess Princ(8, 10, constants["PRINCESS_CHAR"], constants["PRINCESS_HP"], constants["PRINCESS_DAMAGE"]);
    game_characters.push_back(&Princ);
    Zombie  Z1(5, 5, constants["ZOMBIE_CHAR"], constants["ZOMBIE_HP"], constants["ZOMBIE_DAMAGE"]);
    game_characters.push_back(&Z1);
    Dragon D1(7, 7, constants["DRAGON_CHAR"], constants["DRAGON_HP"], constants["DRAGON_DAMAGE"]);
    game_characters.push_back(&D1);
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
