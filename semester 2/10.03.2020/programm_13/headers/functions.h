/*
(10-40 баллов)
Написать программу для настольной карточной игры (в текстовой форме). 
1)Игрок выбирает действия (2-3 типа)
2)4-5 видов карт (с возможностью развития)
3)Взаимодействие между игроками определяется наборами карт, модификаторами, случайными событиями
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define ESC "\033"
// Управление выводом в консоль
#define clrscr()                    printf(ESC "[2J")              // Очистить экран, переместить курсор в (1, 1)
#define clrstr()                    printf(ESC "[2K")              // Очистить экран
#define gotoxy(x, y)                printf(ESC "[%d;%dH", y, x)    // Переместить в место экрана (x, y)
#define resetcolor()                printf(ESC "[0m")              // Сбросить настройки
#define set_display_atrib(color)    printf(ESC "[%dm", color)      // Установить режим вывода текста

// Формат текста
#define RESET 		0
#define BRIGHT 		1
#define DIM		    2
#define UNDERSCORE	3
#define BLINK		4
#define REVERSE		5
#define HIDDEN		6

// Цвета текста
#define F_BLACK 	30
#define F_RED		31
#define F_GREEN		32
#define F_YELLOW	33
#define F_BLUE		34
#define F_MAGENTA 	35
#define F_CYAN		36
#define F_WHITE		37

// Цвета фона
#define B_BLACK 	40
#define B_RED		41
#define B_GREEN		42
#define B_YELLOW	44
#define B_BLUE		44
#define B_MAGENTA 	45
#define B_CYAN		46
#define B_WHITE		47

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;

// Данные "Снайпера"
const int SniperHealth  = 15;
const int SniperCost    = 10;
const int SniperAbility = 3;
const int SniperDamage  = 100;

// Данные "Доктора"
const int HillerHealth  = 40;
const int HillerCost    = 8;
const int HillerAbility = 6;

// Данные "Защитника"
const int DefenderHealth  = 25;
const int DefenderCost    = 6;
const int DefenderAbility = 6;

// Данные "Танка"
const int TankHealth  = 100;
const int TankShotCost = 10;
const int TankCost    = 10;
const int TankDamage  = 20;

// Данные "Бойца"
const int FighterHealth = 30;
const int FighterShotCost = 2;
const int FighterCost   = 2;
const int FighterDamage = 15;

// Данные класса Игрок
const int NumberSlots = 4;
const int NumberCards = 5;
const int PlayerHealth = 5;
const int PlayerDamage = 1;
const int PlayerDamageCost = 20;
const int LevelUpMoney = 6;

// верхний левый угол, отсчитывая от поля игрока №1
const int WindowX = 5;
const int WindowY = 10;

class Carcas
{
  protected:
    int x, y;
  public:
    ~Carcas();
    void draw_background();
    void erase_card();
};

class Card : public Carcas
{
  protected:
    int health;
    int maxHealth;
    bool hasShield;
  public:
    void draw_hp();
    int return_hp();
    template <typename objType>
    void take_skill(objType& obj);
};

class AbilityCard : public Card
{
  protected:
    int abilityCount;
  public:
    void draw_ability();
};

class Sniper : public AbilityCard
{
  public:
    Sniper(int x_c, int y_c);
    void draw_card();
    void use_skill(int& hp, int& maxhp, bool& shield);
};

class Hiller : public AbilityCard
{
  public:
    Hiller(int x_c, int y_c);
    void refresh();
    void draw_card();
    void use_skill(int& hp, int& maxhp, bool& shield);
};

class Defender : public AbilityCard
{
  public:
    Defender(int x_c, int y_c);
    void refresh();
    void draw_card();
    void use_skill(int& hp, int& maxhp, bool& shield);
};

class Tank : public Card
{
  public:
    Tank(int x_c, int y_c);
    void draw_card();
    void use_skill(int& hp, int& maxhp, bool& shield);
};

class Fighter : public Card
{
  public:
    Fighter(int x_c, int y_c);
    void draw_card();
    void use_skill(int& hp, int& maxhp, bool& shield);
};

struct CardPlace
{
  public:
    // Верхний левый угол слота карты
    int x, y;
    // Коды распознавания карт
    Defender* d;    // 0
    Fighter* f;     // 1
    Hiller* h;      // 2
    Sniper* s;      // 3
    Tank* t;        // 4
  public:
    CardPlace();
    ~CardPlace();
    void clean();
    void add_new_card(int num);
    int return_card_num();
    template <typename objType>
    bool change_card(objType& obj);
};

class Player
{
  private:
    int xMain, yMain;   // Верхний левый угол поля Игрока
    int health;         // Жизни игрока
    int coinSumLast;    // Последняя сумма на счету
    int coinSum;        // Текущая сумма
    int number;         // Номер игрока 1 или 2
    bool exit;          // Запрос на выход из игры
    Player* enemy;      // Привязка к оппоненту
    CardPlace table[NumberSlots];   // Массив слотов
  public:
    Player(int x1, int y1, int num);
    Player();
    void initialization(int x1, int y1, int num);
    void show_health();
    void show_coins();
    void draw_frame();
    void show_input_window();
    void hide_input_window();
    void draw();
    bool have_exit();
    int read_command(int& num1, int& num2);
    void check_slots();
    void take_card(int num1, int num2);
    void use_card(int num1, int num2);
    void turn();
    void attach_enemy(Player& alien);
    bool have_cards();
    void use_hit();
    int return_hp();
    void change_hp(int newhp);
    void refresh();
    template <typename objType>
    void take_attack(bool* array, objType& obj);
};

class Game
{
  private:
    Player p1;
    Player p2;
  public:
    Game();
    void draw_frame();
    void draw_icons();
    void draw_winner(int x, int y, int num);
    void draw_field();
    int winner_number();
    void run();
    void exit();
};

#endif
