/*
(10-40 баллов)
Написать программу для настольной карточной игры (в текстовой форме). 
1)Игрок выбирает действия (2-3 типа)
2)4-5 видов карт (с возможностью развития)
3)Взаимодействие между игроками определяется наборами карт, модификаторами, случайными событиями
*/

#include "functions.h"

// <================================ Carcas ================================>
Carcas::~Carcas()
{
    erase_card();
}

void Carcas::draw_background()
{
    set_display_atrib(B_BLUE);
    set_display_atrib(F_WHITE);
    set_display_atrib(BRIGHT);
    gotoxy(x, y);
    cout << "+--------+";
    gotoxy(x, y + 1);
    cout << "|        |";
    gotoxy(x, y + 2);
    cout << "|        |";
    gotoxy(x, y + 3);
    cout << "|        |";
    gotoxy(x, y + 4);
    cout << "|        |";
    gotoxy(x, y + 5);
    cout << "+--------+";
    resetcolor();
}

void Carcas::erase_card()
{
    set_display_atrib(B_GREEN);
    gotoxy(x, y);
    cout << "          ";
    gotoxy(x, y + 1);
    cout << "          ";
    gotoxy(x, y + 2);
    cout << "          ";
    gotoxy(x, y + 3);
    cout << "          ";
    gotoxy(x, y + 4);
    cout << "          ";
    gotoxy(x, y + 5);
    cout << "          ";
    gotoxy(1, WindowY + 23);
    resetcolor();
}

// <================================ Card ================================>
void Card::draw_hp()
{
    set_display_atrib(B_BLUE);
    set_display_atrib(F_WHITE);
    set_display_atrib(BRIGHT);
    gotoxy(x + 1, y + 1);
    cout << health << " ";
    gotoxy(x + 1, y + 2);
    if (hasShield)
    {
        cout << "<s>";
    }
    else
    {
        cout << "   ";
    }
    resetcolor();
}

int Card::return_hp()
{
    return health;
}

template <typename objType>
void Card::take_skill(objType& obj)
{
    obj.use_skill(health, maxHealth, hasShield);
    draw_hp();
}

// <================================ AbilityCard ================================>
void AbilityCard::draw_ability()
{
    set_display_atrib(B_BLUE);
    set_display_atrib(F_YELLOW);
    set_display_atrib(BRIGHT);
    gotoxy(x + 6, y + 1);
    cout << abilityCount << " ";
    resetcolor();
}

// <================================ Sniper ================================>
Sniper::Sniper(int x_c, int y_c)
{
    health = SniperHealth;
    maxHealth = SniperHealth;
    abilityCount = SniperAbility;
    hasShield = false;
    x = x_c;
    y = y_c;
}

void Sniper::draw_card()
{
    draw_background();
    draw_hp();
    draw_ability();
    set_display_atrib(B_BLUE);
    set_display_atrib(F_RED);
    set_display_atrib(BRIGHT);
    gotoxy(x + 2, y + 4);
    cout << "Sniper";
    resetcolor();
}

void Sniper::use_skill(int& hp, int& maxhp, bool& shield)
{
    if (abilityCount > 0)
    {
        if (!shield)
        {
            hp -= SniperDamage;
        }
        else
        {
            shield = false;
        }
        --abilityCount;
        draw_ability();
    }
}

// <================================ Hiller ================================>
Hiller::Hiller(int x_c, int y_c)
{
    health = HillerHealth;
    maxHealth = health;
    abilityCount = HillerAbility;
    hasShield = false;
    x = x_c;
    y = y_c;
}

void Hiller::draw_card()
{
    draw_background();
    draw_hp();
    draw_ability();
    set_display_atrib(B_BLUE);
    set_display_atrib(F_GREEN);
    set_display_atrib(BRIGHT);
    gotoxy(x + 2, y + 4);
    cout << "Hiller";
    resetcolor();
}

void Hiller::use_skill(int& hp, int& maxhp, bool& shield)
{
    if (hp < maxhp && abilityCount > 0)
    {
        hp = maxhp;
        --abilityCount;
        draw_ability();
    }
}

void Hiller::refresh()
{
    health = maxHealth;
    draw_hp();
}

// <================================ Defender ================================>
Defender::Defender(int x_c, int y_c)
{
    health = DefenderHealth;
    maxHealth = DefenderHealth;
    abilityCount = DefenderAbility;
    hasShield = true;
    x = x_c;
    y = y_c;
}

void Defender::draw_card()
{
    draw_background();
    draw_hp();
    draw_ability();
    set_display_atrib(B_BLUE);
    set_display_atrib(F_WHITE);
    set_display_atrib(BRIGHT);
    gotoxy(x + 1, y + 4);
    cout << "Defender";
    resetcolor();
}

void Defender::use_skill(int& hp, int& maxhp, bool& shield)
{
    if (!shield && abilityCount > 0)
    {
        shield = true;
        --abilityCount;
        draw_ability();
    }
}

void Defender::refresh()
{
    hasShield = true;
    draw_hp();
}

// <================================ Tank ================================>
Tank::Tank(int x_c, int y_c)
{
    health = TankHealth;
    maxHealth = TankHealth;
    hasShield = true;
    x = x_c;
    y = y_c;
}

void Tank::draw_card()
{
    draw_background();
    draw_hp();
    set_display_atrib(B_BLUE);
    set_display_atrib(F_CYAN);
    set_display_atrib(BRIGHT);
    gotoxy(x + 3, y + 4);
    cout << "Tank";
    resetcolor();
}

void Tank::use_skill(int& hp, int& maxhp, bool& shield)
{
    if (!shield)
    {
        hp -= TankDamage;
    }
    else
    {
        shield = false;
    }
}

// <================================ Fighter ================================>
Fighter::Fighter(int x_c, int y_c)
{
    health = FighterHealth;
    maxHealth = FighterHealth;
    hasShield = false;
    x = x_c;
    y = y_c;
}

void Fighter::draw_card()
{
    draw_background();
    draw_hp();
    set_display_atrib(B_BLUE);
    set_display_atrib(F_YELLOW);
    set_display_atrib(BRIGHT);
    gotoxy(x + 1, y + 4);
    cout << "Fighter!";
    resetcolor();
}

void Fighter::use_skill(int& hp, int& maxhp, bool& shield)
{
    if (!shield)
    {
        hp -= FighterDamage;
    }
    else
    {
        shield = false;
    }
}

// <================================ CardPlace ================================>
void CardPlace::clean()
{
    if (f != NULL)
    {
        delete f;
        f = NULL;
    }
    if (d != NULL)
    {
        delete d;
        d = NULL;
    }
    if (s != NULL)
    {
        delete s;
        s = NULL;
    }
    if (h != NULL)
    {
        delete h;
        h = NULL;
    }
    if (t != NULL)
    {
        delete t;
        t = NULL;
    }
}

CardPlace::~CardPlace()
{
    clean();
}

CardPlace::CardPlace()
{
    f = NULL;
    d = NULL;
    s = NULL;
    h = NULL;
    t = NULL;
}

void CardPlace::add_new_card(int num)
{
    clean();
    switch(num)
    {
        case 0 :
            d = new Defender(x, y);
        break;
        case 1 :
            f = new Fighter(x, y);
        break;
        case 2 :
            h = new Hiller(x, y);
        break;
        case 3 :
            s = new Sniper(x, y);
        break;
        case 4 :
            t = new Tank(x, y);
        break;
    }
}

int CardPlace::return_card_num()
{
    if (d != NULL)
    {
        return 0;
    } else
    if (f != NULL)
    {
        return 1;
    } else
    if (h != NULL)
    {
        return 2;
    } else
    if (s != NULL)
    {
        return 3;
    } else
    if (t != NULL)
    {
        return 4;
    } else
    {
        return -1;
    }
}

template <typename objType>
bool CardPlace::change_card(objType& obj)
{
    switch(return_card_num())
    {
        case 0 :
            (*d).take_skill(obj);
            return true;
        break;
        case 1 :
            (*f).take_skill(obj);
            return true;
        break;
        case 2 :
            (*h).take_skill(obj);
            return true;
        break;
        case 3 :
            (*s).take_skill(obj);
            return true;
        break;
        case 4 :
            (*t).take_skill(obj);
            return true;
        break;
        default :
            return false;
        break;
    }
}

// <================================ Player ================================>
void Player::initialization(int x1, int y1, int num)
{
    xMain = x1;
    yMain = y1;
    number = num;
    health = PlayerHealth;
    coinSum = 0;
    coinSumLast = 0;
    enemy = NULL;
    exit = false;
    table[0].x = xMain + 3;
    table[0].y = yMain + 4;
    table[1].x = xMain + 16;
    table[1].y = yMain + 4;
    table[2].x = xMain + 29;
    table[2].y = yMain + 4;
    table[3].x = xMain + 42;
    table[3].y = yMain + 4;
}

Player::Player(int x1, int y1, int num)
{
    initialization(x1, y1, num);
}

Player::Player()
{
    initialization(1, 1, 1);
}

void Player::draw_frame()
{
    set_display_atrib(B_GREEN);
    set_display_atrib(F_WHITE);
    set_display_atrib(BRIGHT);
    gotoxy(xMain, yMain);
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    gotoxy(xMain, yMain + 1);
    cout << "| Player" << number << "                                             |";
    gotoxy(xMain, yMain + 2);
    cout << "| Coins:       Health:                                |";
    gotoxy(xMain, yMain + 3);
    cout << "| [0]--------+ [1]--------+ [2]--------+ [3]--------+ |";
    gotoxy(xMain, yMain + 4);
    cout << "| |          | |          | |          | |          | |";
    gotoxy(xMain, yMain + 5);
    cout << "| |          | |          | |          | |          | |";
    gotoxy(xMain, yMain + 6);
    cout << "| |          | |          | |          | |          | |";
    gotoxy(xMain, yMain + 7);
    cout << "| |          | |          | |          | |          | |";
    gotoxy(xMain, yMain + 8);
    cout << "| |          | |          | |          | |          | |";
    gotoxy(xMain, yMain + 9);
    cout << "| |          | |          | |          | |          | |";
    gotoxy(xMain, yMain + 10);
    cout << "| +----------+ +----------+ +----------+ +----------+ |";
    gotoxy(xMain, yMain + 11);
    cout << "|                                                     |";
    gotoxy(xMain, yMain + 12);
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    resetcolor();
}

void Player::show_health()
{
    set_display_atrib(B_GREEN);
    set_display_atrib(F_YELLOW);
    set_display_atrib(BRIGHT);
    gotoxy(xMain + 23, yMain + 2);
    cout << health << " " ;
    resetcolor();
}

void Player::show_coins()
{
    set_display_atrib(B_GREEN);
    set_display_atrib(F_YELLOW);
    set_display_atrib(BRIGHT);
    gotoxy(xMain + 9, yMain + 2);
    cout << coinSum << " ";
    resetcolor();
}

void Player::show_input_window()
{
    set_display_atrib(F_YELLOW);
    set_display_atrib(BRIGHT);
    gotoxy(xMain + 2, yMain + 16);
    cout << "Player" << number << " : ";
    resetcolor();
}

void Player::hide_input_window()
{
    gotoxy(xMain + 2, yMain + 16);
    clrstr();
    gotoxy(xMain + 2, yMain + 17);
    clrstr();
}

void Player::draw()
{
    draw_frame();
    show_health();
    show_coins();
}

int Player::read_command(int& num1, int& num2)
{
    string command, word;
    num1 = num2 = -1;
    cin >> command;
    if (command.length() > 2 && command.length() < 10)
    {
        int i = 0;
        while (command[i] != '(' && i < command.length())
        {
            word += command[i];
            ++i;
        }
        if (word == "take")
        {
                if (command.length() == 9 && command[5] >= '0' && command[5] < '5' && command[7] >= '0' && command[7] < '4')
                {
                    num1 = command[5] - '0';
                    num2 = command[7] - '0';
                    return 0;
                }
                else
                {
                    return -1;
                }
        } else
        if (word == "use")
        {
                if (command.length() == 6 && command[4] >= '0' && command[4] < '4')
                {
                    num1 = command[4] - '0';
                    return 1;
                } else
                if (command.length() == 8 && command[4] >= '0' && command[4] < '4' && command[6] >= '0' && command[6] < '4')
                {
                    num1 = command[4] - '0';
                    num2 = command[6] - '0';
                    return 1;
                }
                else
                {
                    return -1;
                }
        } else
        if (command == "miss")
        {
                return 2;
        } else
        if (command == "esc")
        {
                return 3;
        } else
        if (command == "hit")
        {
                return 4;
        }
        else
        {
                return -1;
        }
    }
    else
    {
        return -1;
    }
    
}

void Player::check_slots()
{
    for (int i = 0; i < NumberSlots; ++i)
    {
        switch(table[i].return_card_num())
        {
            case 0 :
                if ((*(table[i].d)).return_hp() <= 0)
                {
                    table[i].clean();
                }
            break;
            case 1 :
                if ((*(table[i].f)).return_hp() <= 0)
                {
                    table[i].clean();
                }
            break;
            case 2 :
                if ((*(table[i].h)).return_hp() <= 0)
                {
                    table[i].clean();
                }
            break;
            case 3 :
                if ((*(table[i].s)).return_hp() <= 0)
                {
                    table[i].clean();
                }
            break;
            case 4 :
                if ((*(table[i].t)).return_hp() <= 0)
                {
                    table[i].clean();
                }
            break;
        }
    }
}

void Player::attach_enemy(Player& alien)
{
    enemy = &alien;
}

void Player::take_card(int num1, int num2)
{
    int fine = 0;
    if (table[num2].return_card_num() != -1)
    {
        fine = 1;
    }
    switch(num1)
    {
        case 0 :
            if (coinSum >= DefenderCost + fine)
            {
                table[num2].add_new_card(0);
                (*(table[num2].d)).draw_card();
                coinSum -= DefenderCost + fine;
            }
        break;
        case 1 :
            if (coinSum >= FighterCost + fine)
            {
                table[num2].add_new_card(1);
                (*(table[num2].f)).draw_card();
                coinSum -= FighterCost + fine;
            }
        break;
        case 2 :
            if (coinSum >= HillerCost + fine)
            {
                table[num2].add_new_card(2);
                (*(table[num2].h)).draw_card();
                coinSum -= HillerCost + fine;
            }
        break;
        case 3 :
            if (coinSum >= SniperCost + fine)
            {
                table[num2].add_new_card(3);
                (*(table[num2].s)).draw_card();
                coinSum -= SniperCost + fine;
            }
        break;
        case 4 :
            if (coinSum >= TankCost + fine)
            {
                table[num2].add_new_card(4);
                (*(table[num2].t)).draw_card();
                coinSum -= TankCost + fine;
            }
        break;
    }
}

void Player::use_card(int num1, int num2)
{
    bool isTaggedSlot[NumberSlots];
    for (int i = 0; i < NumberSlots; ++i)
    {
        isTaggedSlot[i] = false;
    }
    switch (table[num1].return_card_num())
    {
        case 0:
            for (int i = 0; i < NumberSlots; ++i)
            {
                isTaggedSlot[i] = true;
            }
            isTaggedSlot[num1] = false;
            take_attack(isTaggedSlot, *(table[num1].d));
        break;
        case 1:
            if (coinSum > FighterShotCost && num2 != -1)
            {
                coinSum -= FighterShotCost;
                isTaggedSlot[num2] = true;
                (*(enemy)).take_attack(isTaggedSlot, *(table[num1].f));
                (*(enemy)).check_slots();
            }
        break;
        case 2:
            for (int i = 0; i < NumberSlots; ++i)
            {
                isTaggedSlot[i] = true;
            }
            isTaggedSlot[num1] = false;
            take_attack(isTaggedSlot, *(table[num1].h));
        break;
        case 3:
            if (num2 != -1)
            {
                isTaggedSlot[num2] = true;
                (*(enemy)).take_attack(isTaggedSlot, *(table[num1].s));
                (*(enemy)).check_slots();
            }
        break;
        case 4:
            if (coinSum >= TankShotCost)
            {
                for (int i = 0; i < NumberSlots; ++i)
                {
                    isTaggedSlot[i] = true;
                }
                coinSum -= TankShotCost;
                (*(enemy)).take_attack(isTaggedSlot, *(table[num1].t));
                (*(enemy)).check_slots();
            }
        break;
    }
}

template <typename objType>
void Player::take_attack(bool* array, objType& obj)
{
    for (int i = 0; i < NumberSlots; ++i)
    {
        if (array[i])
        {
            table[i].change_card(obj);
        }
    }
}

void Player::turn()
{
    bool locExit = false;
    int num1, num2;

    refresh();
    while (!locExit)
    {
        show_input_window();
        switch (read_command(num1, num2))
        {
            case 0 :
                take_card(num1, num2);
                show_coins();
            break;
            case 1 :
                use_card(num1, num2);
                show_coins();
            break;
            case 2 :
                locExit = true;
            break;
            case 3 :
                exit = true;
                locExit = true;
            break;
            case 4 :
                use_hit();
                show_coins();
                if ((*(enemy)).return_hp() == 0)
                {
                    locExit = true;
                }
            break;
        }
        locExit = locExit || coinSum == 0;
        hide_input_window();
    }
}

bool Player::have_exit()
{
    return exit;
}

bool Player::have_cards()
{
    bool temp = false;
    for (int i = 0; i < NumberSlots; ++i)
    {
        temp = temp || table[i].return_card_num() != -1;
    }
    return temp;
}

int Player::return_hp()
{
    return health;
}

void Player::change_hp(int newhp)
{
    health = newhp;
}

void Player::use_hit()
{
    if (!(*(enemy)).have_cards() && coinSum >= PlayerDamageCost)
    {
        coinSumLast -= PlayerDamageCost;
        coinSum -= PlayerDamageCost;
        (*(enemy)).change_hp((*(enemy)).return_hp() - PlayerDamage);
        (*(enemy)).show_health();
    }
}

void Player::refresh()
{
    coinSum = coinSumLast + LevelUpMoney;
    coinSumLast = coinSum;
    show_coins();
    for (int i = 0; i < NumberSlots; ++i)
    {
        switch(table[i].return_card_num())
        {
            case 0 :
                (*(table[i].d)).refresh();  
            break;
            case 2 :
                (*(table[i].h)).refresh();  
            break;
        }
    }
}

// <================================ Game ================================>
Game::Game()
{
    p1.initialization(WindowX + 2, WindowY + 2, 1);
    p2.initialization(WindowX + 60, WindowY + 2, 2);
    p1.attach_enemy(p2);
    p2.attach_enemy(p1);
    clrscr();
}

void Game::draw_frame()
{
    set_display_atrib(B_BLUE);
    set_display_atrib(F_WHITE);
    set_display_atrib(BRIGHT);
    gotoxy(WindowX, WindowY);
    cout << "+---------------------------------------------------------+---------------+-----------------------------------------+";
    for (int i = 1; i <= 15; ++i)
    {
        gotoxy(WindowX, WindowY + i);
        cout << "|                                                         |                                                         |";
    }
    gotoxy(WindowX, WindowY + 16);
    cout << "+---------------------------------------------------------+---------------------------------------------------------+";
    resetcolor();
}

void Game::draw_icons()
{
    string name;
    int cost;
    set_display_atrib(B_BLUE);
    set_display_atrib(F_WHITE);
    set_display_atrib(BRIGHT);
    gotoxy(WindowX, WindowY - 8);
    cout << "+-------------------------------------------------------------------------+";
    for (int i = 1; i <= 7; ++i)
    {
        gotoxy(WindowX, WindowY - 8 + i);
    cout << "|                                                                         |";
    }
    set_display_atrib(F_YELLOW);
    for (int i = 0; i < NumberCards + 1; ++i)
    {
        switch (i)
        {
            case 0 :
                name = "Defender";
                cost = DefenderCost;
            break;
            case 1 :
                name = "Fighter!";
                cost = FighterCost;
            break;
            case 2 :
                name = " Hiller ";
                cost = HillerCost;
            break;
            case 3 :
                name = " Sniper ";
                cost = SniperCost;
            break;
            case 4 :
                name = "  Tank  ";
                cost = TankCost;
            break;
            case 5 :
                name = "  Hit!  ";
                cost = PlayerDamageCost;
            break;
        }
        gotoxy(WindowX + 2 * (i + 1) + i * 10, WindowY - 6);
        if (i != NumberCards)
        {
            cout << "[" << i << "]------+";
        }
        else
        {
            cout << "[X]------+";
        }
        gotoxy(WindowX + 2 * (i + 1) + i * 10, WindowY - 5);
        cout << "|        |";
        gotoxy(WindowX + 2 * (i + 1) + i * 10, WindowY - 4);
        cout << "|" << name << "|";
        gotoxy(WindowX + 2 * (i + 1) + i * 10, WindowY - 3);
        cout << "|        |";
        gotoxy(WindowX + 2 * (i + 1) + i * 10, WindowY - 2);
        if (cost > 9)
        {
            cout << "+-----[" << cost << "]";
        }
        else
        {
            cout << "+-----[ " << cost << "]";
        }
    }
    resetcolor();
}

void Game::draw_winner(int x, int y, int num)
{
    set_display_atrib(B_BLUE);
    set_display_atrib(F_WHITE);
    set_display_atrib(BRIGHT);
    gotoxy(x, y);
    cout << "+---------------------+";
    gotoxy(x, y + 1);
    cout << "|                     |";
    gotoxy(x, y + 2);
    cout << "+---------------------+";
    set_display_atrib(F_YELLOW);
    gotoxy(x + 2, y + 1);
    cout << "Winner is : Player" << num;
    resetcolor();
}

void Game::draw_field()
{
    draw_frame();
    draw_icons();
    p1.draw();
    p2.draw();
}

int Game::winner_number()
{
    if (p1.return_hp() == 0)
    {
        return 2;
    }
    else
    if (p2.return_hp() == 0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

void Game::exit()
{
    if (winner_number() != -1)
    {
        draw_winner(WindowX, WindowY + 19, winner_number());
    }
        gotoxy(1, WindowY + 23);
}

void Game::run()
{
    draw_field();
    while (!p1.have_exit() && !p2.have_exit() && p2.return_hp() != 0 && p1.return_hp() != 0)
    {
        p1.turn();
        if (!p1.have_exit() && p2.return_hp() != 0)
        {
            p2.turn();
        }
    }
    exit();
}