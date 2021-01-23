//
// Created by Rashid on 18.01.2021.
//
#include <fstream>
#include "Map.h"
#include <curses.h>
#include "Wall.h"
#include "Gameobject.h"
#include "Zombie.h"
#include "Dragon.h"
#include <string>
#include <map>
#include "Knight.h"
#include "floor.h"
#include "AidKit.h"
std::map<std::string, std::string> read_config() {
    std::ifstream fin("config.txt");   // считываем константные значения
    std::string buf;
    std::map<std::string, std::string> constants;
    while (fin >> buf) {
        auto index = buf.find('='); // парсим значения и их ключи
        constants.emplace(buf.substr(0, index), buf.substr(index + 1)); // сохраняем в std map
    }
    fin.close();
    return constants;
}
Map::Map() {  // конструктор карты
    std::map<std::string, std::string> constants = read_config();
    std::ifstream fin("map.txt");          // cчитываем карту
    int num_row = 0;
    fin >> num_row;
    for (int i = 0; i < num_row; i++) {
        std::string buf;
        fin >> buf;
        std::vector<std::shared_ptr<Gameobject>> buf2;
        for (int j = 0; j < buf.size(); j++) {   // создаем нужный указатель в зависимости от символа на карте
            if (buf[j] == '#') {
                buf2.push_back(std::make_shared<Wall>(i, j, constants["WALL_CHAR"]));
            }
            else if (buf[j] == '.') {
                buf2.push_back(std::make_shared<Floor>(i, j, constants["FLOOR_CHAR"]));
            }
            else if (buf[j] == '+') {
                buf2.push_back(std::make_shared<AidKit>(i, j, constants["AIDKIT_CHAR"]));
            }
            else if (buf[j] == 'K') {
                this->Pers = std::make_shared<Knight>(i, j, constants["KNIGHT_CHAR"], constants["KNIGHT_HP"], constants["KNIGHT_DAMAGE"], constants["KNIGHT_VISION"]);
                buf2.push_back(this->Pers);
                
            }
            else if (buf[j] == 'P') {
                this->Princ = std::make_shared<Princess>(i, j, constants["PRINCESS_CHAR"], constants["PRINCESS_HP"], constants["PRINCESS_DAMAGE"]);
                buf2.push_back(this->Princ);
                
            }
            else if (buf[j] == 'Z') {
                buf2.push_back(std::make_shared<Zombie>(i, j, constants["ZOMBIE_CHAR"], constants["ZOMBIE_HP"], constants["ZOMBIE_DAMAGE"]));
            }
            else if (buf[j] == 'D') {
                buf2.push_back(std::make_shared<Dragon>(i, j, constants["DRAGON_CHAR"], constants["DRAGON_HP"], constants["DRAGON_DAMAGE"]));
            }
        }
        this->map_.push_back(buf2);
    }
    fin.close();
}
char Map::Get_Sym(int x, int y) {    // геттер символа элемента карты
    return (*this->map_[x][y]).GetSym();
}
void Map::Paint() { // отрисовка карты вокруг персонажа
    int size_map = (*this->Pers).GetVision(); // определяем сколько клеток вокруг видит персонаж
    int x = (*this->Pers).GetPos().first; // определяем его координату по х (строка)
    int y = (*this->Pers).GetPos().second; // определяем его координату по у (столбец)
    int first_x;  // создаем буферную переменную индекса первой видимой строки
    bool flag_up = 0;
    if (x-size_map-3<0){   // проверка на выход за карту сверху
        first_x = 0;   // если видимость выходит за границы карты сверху присваиваем 0
        flag_up = 1;   // туман войны не отрисовывается
    }else{
        first_x = x-size_map-2; // если видимость не выходит за границы карты присваиваем первую видимую строку
    }
    int second_x; // создаем буферную переменную индекса последней видимой строки
    bool flag_down = 0;
    if (x+size_map+3>map_.size()-1){ // проверка на выход за карту снизу
        second_x = map_.size(); // если выходим то присваиваем количество строк
        flag_down = 1; // туман войны не отрисовывается
    }else{
        second_x = x+size_map + 2; // если видимость не выходит за границы карты присваиваем последнюю видимую строку
    }
    int first_y; // создаем буферную переменную первого видимого столбца
    bool flag_left = 0;
    if (y-size_map-3<0){  // проверка на выход за карту  слева
        first_y=0; // если видимость выходит за границы присваиваем 0
        flag_left = 1; // туман войны не отрисовывается
    }else{
        first_y=y-size_map-2;// если видимость не выходит за границы карты присваиваем первый видимый столбец
    }
    int second_y; // создаем буферную переменную последнего видимого столбца
    bool flag_right = 0;
    if (y+size_map+3>map_[x].size()-1){  // проверка на выход за карту справа
        flag_right = 1; // туман войны не отрисовывается
        second_y = map_[x].size(); //если видимость выходит за границы карты присваиваем количество столбцов в строке
    }else{
        second_y = y+size_map+2; // если видимость не выходит за границы карты присваиваем последний видимый столбец
    }
    std::vector<char> buf2;
    for (int i = 0; i < (second_y - first_y); i++) {
        buf2.push_back('~');
    }
    std::vector<std::vector<char>> visible_map; // создаем переменную для эскиза
    for(int i=first_x;i<second_x;i++){  // заполнение карты которую выведем идем по строчкам
        std::vector<char> buf; // создаем буферную переменную для строки карты
        for (int j=first_y;j<second_y;j++){ // заполнение карты которую выведем идем по  столбцам
            buf.push_back(this->Get_Sym(i,j)); // заполняем буферный вектор
        }
        visible_map.push_back(buf); // заполняем эскиз
    }
    if (flag_up == 0) {  // туман войны сверху
        visible_map[0] = buf2;
    }
    if (flag_down == 0) {  // туман войны снизу
        visible_map[visible_map.size() - 1] = buf2;
    }
    if (flag_left == 0) {  // туман войны слева
        for (int i = 0; i < visible_map.size(); i++) {
            visible_map[i][0] = '~';
        }
    }
    if (flag_right == 0) {  // туман войны справа
        for (int i = 0; i < visible_map.size(); i++) {
            visible_map[i][buf2.size()-1] = '~';
        }
    }
    for (int i=0;i<visible_map.size();i++){ // вывод полученного эскиза на экран
        for(int j=0;j<visible_map[i].size();j++){
            mvaddch(i, j, visible_map[i][j]);
        }
    }
}
void Map::Win_Or_Lose() { // функция проверки победы или проигрыша
    if ((abs((*this->Pers).GetPos().first - (*this->Princ).GetPos().first) == 1) || abs((*this->Pers).GetPos().second - (*this->Princ).GetPos().second) == 1) {
        this->Paint_Win();
    }
    if ((*this->Pers).GetHp() == 0) {
        this->Paint_Lose();
    }
}
void Map::Paint_Win() {  // вывод экрана победы
    clear();
    printw("YOU ARE WIN!");
    getch();
    exit(0);
}
int Map::Paint_Lose() { // вывод экрана поражения
    clear();
    printw("You are lose =((");
    char buf = getch();
    exit(0);
}
