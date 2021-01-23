//
// Created by Rashid on 18.01.2021.
//
#include <fstream>
#include "Map.h"
#include <curses.h>

Map::Map() {  // конструктор карты
    std::ifstream fin("map1.txt");  // подключаем файл с изначальной картой
    int num_row = 0;    // создаем счетчик для строк
    fin>>num_row;      // считываем количество строк карты
    for(int i=0;i<num_row;i++){  // переводим карту в vector<vector<char>> которым является приватное поле map_
        std::string buf;  // создаем буферную переменную
        fin>>buf;  // считываем строку карты
        std::vector<char> buf2; // создаем буферный вектор
        for (int j=0;j<buf.size();j++){  // заполняем вектор элементами считанной строки
            buf2.push_back(buf[j]);
        }
        this->map_.push_back(buf2);  // добавляем полученный vector<char> в map_
    }
    fin.close(); // закрываем входной поток
}
char Map::Get_Sym(int x, int y) {
    return this->map_[x][y];
}
void Map::Paint(std::vector<Character*> characters) { // отрисовка карты вокруг персонажа

    int size_map = (*characters[0]).GetVision(); // определяем сколько клеток вокруг видит персонаж
    int x = (*characters[0]).GetPos().first; // определяем его координату по х (строка)
    int y = (*characters[0]).GetPos().second; // определяем его координату по у (столбец)
    int first_x;  // создаем буферную переменную индекса первой видимой строки
    if (x-size_map-1<0){   // проверка на выход за карту сверху
        first_x = 0;   // если видимость выходит за границы карты сверху присваиваем 0
    }else{
        first_x = x-size_map-1; // если видимость не выходит за границы карты присваиваем первую видимую строку
    }
    int second_x; // создаем буферную переменную индекса последней видимой строки
    if (x+size_map+1>map_.size()-1){ // проверка на выход за карту снизу
        second_x = map_.size(); // если выходим то присваиваем количество строк
    }else{
        second_x = x+size_map + 1; // если видимость не выходит за границы карты присваиваем последнюю видимую строку
    }
    int first_y; // создаем буферную переменную первого видимого столбца
    if (y-size_map-1<0){  // проверка на выход за карту  слева
        first_y=0; // если видимость выходит за границы присваиваем 0
    }else{
        first_y=y-size_map-1;// если видимость не выходит за границы карты присваиваем первый видимый столбец
    }
    int second_y; // создаем буферную переменную последнего видимого столбца
    if (y+size_map+1>map_[x].size()-1){  // проверка на выход за карту справа
        second_y = map_[x].size(); //если видимость выходит за границы карты присваиваем количество столбцов в строке
    }else{
        second_y = y+size_map+1; // если видимость не выходит за границы карты присваиваем последний видимый столбец
    }
    std::vector<std::vector<char>> visible_map; // создаем переменную для эскиза
    for(int i=first_x;i<second_x;i++){  // заполнение карты которую выведем идем по строчкам
        std::vector<char> buf; // создаем буферную переменную для строки карты
        for (int j=first_y;j<second_y;j++){ // заполнение карты которую выведем идем по  столбцам
            buf.push_back(map_[i][j]); // заполняем буферный вектор
        }
        visible_map.push_back(buf); // заполняем эскиз
    }
    for (int i=0;i<characters.size();i++){ // добавление персонажей
        int x_ch=(*characters[i]).GetPos().first; // считываем положения живого обьекта (строка)
        int y_ch=(*characters[i]).GetPos().second; // считываем положение живого обьекта (столбец)
        if ((first_x<=x_ch && x_ch<second_x) && (first_y<=y_ch && y_ch<second_y)){ // если попадает в область видимости
            visible_map[x_ch-first_x][y_ch-first_y] = (*characters[i]).GetSym();// отрисовываем в эскизе
        }
    }
    for (int i=0;i<visible_map.size();i++){ // вывод полученного эскиза на экран
        for(int j=0;j<visible_map[i].size();j++){
            mvaddch(i, j, visible_map[i][j]);
        }
    }
}