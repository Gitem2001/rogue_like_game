//
// Created by Rashid on 18.01.2021.
//
#include <curses.h>
#include "Game_loop.h"
#include "Map.h"

void Game_loop::Start_game() {  // Процедура начала игры
    Map current_map = Map();
    initscr();
    resize_term(40,112);
    refresh();
    curs_set(0);
    clear();
    noecho();
    current_map.Paint();
    Cont_game(current_map);
}
void Game_loop::Cont_game(Map map_) {

    char buf = getch(); // ожидаем символа от пользователя
    std::pair<int,int> buf2 = (*map_.Pers).try_move(buf);
    res_col flag = (*map_.Pers).Collide(&(*map_.map_[buf2.first][buf2.second]));
    switch (flag) {
    case CanMove:
        map_.map_[(*map_.Pers).GetPos().first][(*map_.Pers).GetPos().second].swap(map_.map_[buf2.first][buf2.second]);
        (*map_.Pers).move(buf2.first, buf2.second);
        break;
    case AidHP:
        map_.destroy_obj(buf2.first, buf2.second);
        map_.map_[(*map_.Pers).GetPos().first][(*map_.Pers).GetPos().second].swap(map_.map_[buf2.first][buf2.second]);
        (*map_.Pers).move(buf2.first, buf2.second);
        (*map_.Pers).Regeneration(); 
        break;
    case CanAttack:
        (*map_.map_[buf2.first][buf2.second]).Hit((*map_.Pers).GetDamage());
        if ((*map_.map_[buf2.first][buf2.second]).GetHp() <= 0) {
            map_.destroy_obj(buf2.first, buf2.second);
            map_.map_[(*map_.Pers).GetPos().first][(*map_.Pers).GetPos().second].swap(map_.map_[buf2.first][buf2.second]);
            (*map_.Pers).move(buf2.first, buf2.second);
        }
        break;
    } 
    map_.Win_Or_Lose();
    map_.Paint();
    Cont_game(map_);
}
