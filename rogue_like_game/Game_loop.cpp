//
// Created by Rashid on 18.01.2021.
//
#include <curses.h>
#include "Game_loop.h"
#include "Map.h"
#include <stdlib.h>
#include <ctime>
void Game_loop::Start_game() {  // Процедура начала игры
    Map current_map = Map();
    initscr();
    resize_term(40,112);
    keypad(stdscr, TRUE);
    nodelay(stdscr, true);
    refresh();
    curs_set(0);
    clear();
    noecho();
    current_map.Paint();
    Cont_game(current_map);
}
std::pair<int, int> dir() {
    int rand_dir = 1+ rand()  % 4; // 1 - UP 2- DOWN 3- LEFT 4-RIGHT
    int dx, dy;
    switch (rand_dir) {
    case 1:
        dx = -1;
        dy = 0;
        break;
    case 2:
        dx = 1;
        dy = 0;
        break;
    case 3:
        dx = 0;
        dy = -1;
        break;
    case 4:
        dx = 0;
        dy = 1;
        break;
    }
    return std::pair<int, int>(dx, dy);
}
void Game_loop::Cont_game(Map map_) {
    long long last_knight_action = clock();
    long long t = clock();
    long long t_dragon = clock();
    long long one_action = 200;
    while (true) {
        if ((clock() - t) >= (one_action) * 1.5) {
            for (int i = 0; i < map_.zombies.size(); i++) {
                if (map_.zombies[i] != nullptr) {
                    std::pair<int, int> delta = dir();
                    std::pair<int, int> buf2((*map_.zombies[i]).GetPos().first + delta.first, (*map_.zombies[i]).GetPos().second + delta.second);
                    res_col flag = (*map_.zombies[i]).Collide(&(*map_.map_[buf2.first][buf2.second]));
                    switch (flag) {
                    case CanMove:
                        map_.map_[(*map_.zombies[i]).GetPos().first][(*map_.zombies[i]).GetPos().second].swap(map_.map_[buf2.first][buf2.second]);
                        (*map_.zombies[i]).move(buf2.first, buf2.second);
                        break;
                    case CanAttack:
                        (*map_.map_[buf2.first][buf2.second]).Hit((*map_.zombies[i]).GetDamage());
                    }
                }
            }
            t = clock();
        }
        if ((clock() - t_dragon) >= (one_action) * 1.5) {
            for (int i = 0; i < map_.dragons.size(); i++) {
                if (map_.dragons[i] != nullptr) {
                    std::pair<int, int> delta = dir();
                    std::pair<int, int> buf2((*map_.dragons[i]).GetPos().first + delta.first, (*map_.dragons[i]).GetPos().second + delta.second);
                    res_col flag = (*map_.dragons[i]).Collide(&(*map_.map_[buf2.first][buf2.second]));
                    switch (flag) {
                    case CanMove:
                        map_.map_[(*map_.dragons[i]).GetPos().first][(*map_.dragons[i]).GetPos().second].swap(map_.map_[buf2.first][buf2.second]);
                        (*map_.dragons[i]).move(buf2.first, buf2.second);
                        break;
                    case CanAttack:
                        (*map_.map_[buf2.first][buf2.second]).Hit((*map_.dragons[i]).GetDamage());
                    }
                }

            }
            t_dragon = clock();
        }
        char buf = getch(); // ожидаем символа от пользователя
        if (buf != ERR) {
            if ((clock() - last_knight_action) >= (one_action * 1.2)) {
                
                std::pair<int, int> buf2 = (*map_.Pers).try_move(buf);
                res_col flag = (*map_.Pers).Collide(&(*map_.map_[buf2.first][buf2.second]));
                switch (flag) {
                case CanMove:
                    map_.map_[(*map_.Pers).GetPos().first][(*map_.Pers).GetPos().second].swap(map_.map_[buf2.first][buf2.second]);
                    (*map_.Pers).move(buf2.first, buf2.second);
                    last_knight_action = clock();
                    break;
                case AidHP:
                    map_.destroy_obj(buf2.first, buf2.second);
                    map_.map_[(*map_.Pers).GetPos().first][(*map_.Pers).GetPos().second].swap(map_.map_[buf2.first][buf2.second]);
                    (*map_.Pers).move(buf2.first, buf2.second);
                    (*map_.Pers).Regeneration();
                    last_knight_action = clock();
                    break;
                case CanAttack:
                    (*map_.map_[buf2.first][buf2.second]).Hit((*map_.Pers).GetDamage());
                    if ((*map_.map_[buf2.first][buf2.second]).GetHp() <= 0) {
                        map_.destroy_obj(buf2.first, buf2.second);
                    }
                    last_knight_action = clock();
                    break;
                }
            }
        }    
        map_.Win_Or_Lose();
        map_.Paint();
    }
    nodelay(stdscr, true);
}
