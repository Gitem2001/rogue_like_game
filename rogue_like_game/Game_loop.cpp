//
// Created by Rashid on 18.01.2021.
//
#include <curses.h>
#include "Game_loop.h"
#include "Map.h"
#include <stdlib.h>
#include <ctime>
#include <memory>
#include "Gameobject.h"
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
    long long t_projectile = clock();
    long long one_action = 200;
    while (true) {
        if ((clock() - t_projectile) >= (one_action) * 0.5) {
            for (int i = 0; i < map_.projectiles.size(); i++) {
                if (map_.projectiles[i] != nullptr) {
                    int buf_x = (*map_.projectiles[i]).x;
                    int buf_y = (*map_.projectiles[i]).y;
                    res_col flag = (*map_.projectiles[i]).Collide(&(*map_.map_[buf_x + (*map_.projectiles[i]).direction.first][buf_y + (*map_.projectiles[i]).direction.second]));
                    switch (flag) {
                    case CanMove:
                        map_.map_[buf_x][buf_y].swap(map_.map_[buf_x + (*map_.projectiles[i]).direction.first][buf_y + (*map_.projectiles[i]).direction.second]);
                        (*map_.projectiles[i]).Fly();
                        break;
                    case Destroy:
                        map_.destroy_obj(buf_x, buf_y);
                        map_.projectiles[i] = nullptr;
                        break;
                    case CanAttack:
                        (*map_.map_[buf_x + (*map_.projectiles[i]).direction.first][buf_y + (*map_.projectiles[i]).direction.second]).Hit((*map_.projectiles[i]).damage);
                        if ((*map_.map_[buf_x + (*map_.projectiles[i]).direction.first][buf_y + (*map_.projectiles[i]).direction.second]).GetHp() <= 0) {
                            map_.destroy_obj(buf_x + (*map_.projectiles[i]).direction.first, buf_y + (*map_.projectiles[i]).direction.second);
                        }
                        map_.destroy_obj(buf_x, buf_y);
                        map_.projectiles[i] = nullptr;
                        break;
                    }
                }
            }
            t_projectile = clock();
        }
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
        if ((clock() - t_dragon) >= (one_action) * 3) {
            for (int i = 0; i < map_.dragons.size(); i++) {
                if (map_.dragons[i] != nullptr) {
                    std::pair<int, int> delta = dir();
                    std::pair<int, int> buf2((*map_.dragons[i]).GetPos().first + delta.first, (*map_.dragons[i]).GetPos().second + delta.second);
                    res_col flag = (*map_.dragons[i]).Collide(&(*map_.map_[buf2.first][buf2.second]));
                    switch (flag) {
                    case CanMove:
                        map_.map_[(*map_.dragons[i]).GetPos().first][(*map_.dragons[i]).GetPos().second].swap(map_.map_[buf2.first][buf2.second]);
                        (*map_.dragons[i]).move(buf2.first, buf2.second);
                        map_.projectiles.push_back(std::make_shared<Projectile>(buf2.first, buf2.second, std::pair<int, int>{ 0, 0 }));
                        (*map_.projectiles[map_.projectiles.size() - 1]).direction = delta;
                        (*map_.projectiles[map_.projectiles.size() - 1]).Fly();
                        flag = (*map_.projectiles[map_.projectiles.size() - 1]).Collide(&(*map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y]));
                        if (flag == CanAttack) {
                            (*map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y]).Hit((*map_.projectiles[map_.projectiles.size() - 1]).damage);
                            map_.projectiles[map_.projectiles.size() - 1] = nullptr;
                        }
                        else if (flag == CanMove) {
                            map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y].~shared_ptr();
                            map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y] = map_.projectiles[map_.projectiles.size() - 1];
                        }
                        else {
                            map_.projectiles[map_.projectiles.size() - 1] = nullptr;
                        }
                        break;
                    case CanAttack:
                        (*map_.map_[buf2.first][buf2.second]).Hit((*map_.dragons[i]).GetDamage());
                        break;
                    }
                    
                }

            }
            t_dragon = clock();
        }
        char buf = getch(); // ожидаем символа от пользователя
        if (buf != ERR) {
            if ((clock() - last_knight_action) >= (one_action * 1)) {
                std::pair<int, int> buf2 = (*map_.Pers).try_move(buf);
                std::pair<int, int> a;
                res_col flag;
                switch (buf) {
                case '\x3':
                    map_.projectiles.push_back(std::make_shared<Projectile>(buf2.first, buf2.second, std::pair<int, int>{ 0, 0 }));
                    a= { -1, 0 };
                    (*map_.projectiles[map_.projectiles.size()-1]).direction = a;
                    (*map_.projectiles[map_.projectiles.size() - 1]).Fly();
                    flag = (*map_.projectiles[map_.projectiles.size() - 1]).Collide(&(*map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y]));
                    if (flag == CanAttack) {
                        (*map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y]).Hit((*map_.projectiles[map_.projectiles.size() - 1]).damage);
                        map_.projectiles[map_.projectiles.size() - 1] = nullptr;
                    } else if (flag == CanMove){
                        map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y].~shared_ptr();
                        map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y] = map_.projectiles[map_.projectiles.size() - 1];
                    }
                    else {
                        map_.projectiles[map_.projectiles.size() - 1] = nullptr;
                    }
                    t_projectile = clock();
                    last_knight_action = clock();
                    break;
                case '\x2':
                    map_.projectiles.push_back(std::make_shared<Projectile>(buf2.first, buf2.second, std::pair<int, int>{ 0, 0 }));
                    a = { 1, 0 };
                    (*map_.projectiles[map_.projectiles.size() - 1]).direction = a;
                    (*map_.projectiles[map_.projectiles.size() - 1]).Fly();
                    flag = (*map_.projectiles[map_.projectiles.size() - 1]).Collide(&(*map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y]));
                    if (flag == CanAttack) {
                        (*map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y]).Hit((*map_.projectiles[map_.projectiles.size() - 1]).damage);
                        map_.projectiles[map_.projectiles.size() - 1] = nullptr;
                    }
                    else if (flag == CanMove) {
                        map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y].~shared_ptr();
                        map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y] = map_.projectiles[map_.projectiles.size() - 1];
                    }
                    else {
                        map_.projectiles[map_.projectiles.size() - 1] = nullptr;
                    }
                    t_projectile = clock();
                    last_knight_action = clock();
                    break;
                case '\x4':
                    map_.projectiles.push_back(std::make_shared<Projectile>(buf2.first, buf2.second, std::pair<int, int>{ 0, 0 }));
                    a = { 0, -1 };
                    (*map_.projectiles[map_.projectiles.size() - 1]).direction = a;
                    (*map_.projectiles[map_.projectiles.size() - 1]).Fly();
                    flag = (*map_.projectiles[map_.projectiles.size() - 1]).Collide(&(*map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y]));
                    if (flag == CanAttack) {
                        (*map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y]).Hit((*map_.projectiles[map_.projectiles.size() - 1]).damage);
                        map_.projectiles[map_.projectiles.size() - 1] = nullptr;
                    }
                    else if (flag == CanMove) {
                        map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y].~shared_ptr();
                        map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y] = map_.projectiles[map_.projectiles.size() - 1];
                    }
                    else {
                        map_.projectiles[map_.projectiles.size() - 1] = nullptr;
                    }
                    t_projectile = clock();
                    last_knight_action = clock();
                    break;
                case '\x5':
                    map_.projectiles.push_back(std::make_shared<Projectile>(buf2.first, buf2.second, std::pair<int, int>{ 0, 0 }));
                    a = { 0, 1 };
                    (*map_.projectiles[map_.projectiles.size() - 1]).direction = a;
                    (*map_.projectiles[map_.projectiles.size() - 1]).Fly();
                    flag = (*map_.projectiles[map_.projectiles.size() - 1]).Collide(&(*map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y]));
                    if (flag == CanAttack) {
                        (*map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y]).Hit((*map_.projectiles[map_.projectiles.size() - 1]).damage);
                        map_.projectiles[map_.projectiles.size() - 1] = nullptr;
                    }
                    else if (flag == CanMove) {
                        map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y].~shared_ptr();
                        map_.map_[(*map_.projectiles[map_.projectiles.size() - 1]).x][(*map_.projectiles[map_.projectiles.size() - 1]).y] = map_.projectiles[map_.projectiles.size() - 1];
                    }
                    else {
                        map_.projectiles[map_.projectiles.size() - 1] = nullptr;
                    }
                    t_projectile = clock();
                    last_knight_action = clock();
                    break;
                default:
                    flag = (*map_.Pers).Collide(&(*map_.map_[buf2.first][buf2.second]));
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
        }    
        map_.Win_Or_Lose();
        map_.Paint();
    }
    nodelay(stdscr, true);
}
