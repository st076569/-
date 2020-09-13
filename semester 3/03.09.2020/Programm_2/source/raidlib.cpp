////////// RAID 5 ////////////////////////////////////////////////////////////
// Автор  : Баталов Семен                                                   //
// Дата   : 10.09.2020                                                      //
// Задача : Решить задачу с помощью STL. Эффективно смоделировать RAID 5,   //
//          для k буферов размера n кБайт. Технология использует            //
//          контрольные суммы для восстановления данных в случае выхода из  //
//          строя одного жёсткого диска. Нужно проделать тоже самое, только //
//          на буферах (массивах фиксированной длины). В моделировании      //
//          нужно заполнить несколько буферов данных, по ним построить      //
//          буфер контрольных сумм. Затем выбрать случайным образом один из //
//          буферов, как исчезнувший. После восстановить исчезнувшие данные //
//          и сравнить восстановленные данные с настоящими.                 //
//////////////////////////////////////////////////////////////////////////////

#include "raidlib.h"

////////// struct Buffer /////////////////////////////////////////////////////
// Эта структура представляет из себя буфер, состоящий из битовых           //
// блоков и являющийся элементом массива RAID.                              //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
bat::Buffer::Buffer()
{
    blocks.clear();
    isCrashed = false;
}

// (2) Конструктор копирования
bat::Buffer::Buffer(const bat::Buffer& buffer)
{
    *this = buffer;
}

// (3) Перегрузка оператора присваивания
bat::Buffer& bat::Buffer::operator=(const bat::Buffer& buffer)
{
    // Проверка на самоприсваивание
    if (this != &buffer)
    {
        isCrashed = buffer.isCrashed;
        blocks = buffer.blocks;
    }
    return *this;
}

// (4) Вывод в консоль
void bat::Buffer::print()
{
    if (isCrashed)
    {
        std::cout << "// STATUS : 'Crashed'\n";
    }
    else
    {
        std::cout << "// STATUS : 'Available'\n";
    }
    for (int i = 0; i < blocks.size(); ++i)
    {
        if (i < 10)
        {
            std::cout << "// [" << i << "]  : ";
        }
        else
        {
            std::cout << "// [" << i << "] : ";
        }
        std::cout << blocks[i] << "\n";
    }
}

// (5) Изменяет размер буфера
void bat::Buffer::resize(const int& blockNumber)
{
    if (blockNumber >= 0)
    {
        blocks.resize(blockNumber);
    }
}

// (6) Задает случайные значения
void bat::Buffer::setRandomValues()
{
    reset();
    for (int i = 0; i < blocks.size(); ++i)
    {
        for (int j = 0; j < bat::BLOCK_SIZE; ++j)
        {
            if (rand() % 2 == 0)
            {
                blocks[i].flip(j);
            }
        }
    }
}

// (7) Сбрасывает значение статуса
void bat::Buffer::resetStatus()
{
    isCrashed = false;
}

// (8) Сбрасывает значения всех битов до нуля
void bat::Buffer::reset()
{
    for (int i = 0; i < blocks.size(); ++i)
    {
        blocks[i].reset();
    }
    resetStatus();
}

// (9) Очищает элементы буфера
void bat::Buffer::clear()
{
    blocks.clear();
    isCrashed = false;
}

// (10) Деструктор
bat::Buffer::~Buffer()
{
    clear();
}

////////// class Raid5 ///////////////////////////////////////////////////////
// Этот класс представляет модель технологии "Raid 5". Она позволяет        //
// быстро востанавливать данные в случае выхода из строя одного из          //
// носителей.                                                               //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
bat::Raid5::Raid5()
{
    buffers_.clear();
    bufferNumber_ = 0;
    bufferSize_   = 0;
}
	    
// (2) Конструктор копирования
bat::Raid5::Raid5(const Raid5& raid5)
{
    *this = raid5;
}
	    
// (3) Перегрузка оператора присваивания
bat::Raid5& bat::Raid5::operator=(const bat::Raid5& raid5)
{
    if (this != &raid5)
    {
        buffers_ = raid5.buffers_;
        bufferNumber_ = raid5.bufferNumber_;
        bufferSize_   = raid5.bufferSize_;
    }
    return *this;
}

// (4) Вывод в консоль
void bat::Raid5::print()
{
    for (int i = 0; i < bufferNumber_; ++i)
    {
        std::cout << "////////////////////////////// Buffer (" << i << ")\n";
        buffers_[i].print();
    }
}

// (5) Изменяет размеры рейда
void bat::Raid5::resize(const int& buffferNumber, const int& bufferSize)
{
    if (buffferNumber >= 0 && bufferSize >= 0)
    {
        buffers_.resize(buffferNumber);
        for (int i = 0; i < buffferNumber; ++i)
        {
            buffers_[i].resize(bufferSize);
        }
        bufferNumber_ = buffferNumber;
        bufferSize_  = bufferSize;
    }
}

// (6) Задает случайные значения буферов
void bat::Raid5::setRandomValues()
{
    for (int i = 0; i < bufferNumber_; ++i)
    {
        buffers_[i].setRandomValues();
    }
}

// (7) Записать все контрольные суммы
void bat::Raid5::setControlSums()
{
    int iBlock = 0;
    Block temp;
    
    for (int i = 0; i < bufferNumber_; ++i)
    {
        iBlock = i;
        while (iBlock < bufferSize_)
        {
            temp.reset();
            for (int j = 0; j < bufferNumber_; ++j)
            {
                if (j != i)
                {
                    temp ^= buffers_[j].blocks[iBlock];
                }
            }
            buffers_[i].blocks[iBlock] = temp;
            iBlock += bufferNumber_;
        }
    }
}

// (8) Разрушить буфер под номером "bufferNumber"
void bat::Raid5::crashBuffer(const int& bufferNumber)
{
    bool haveCrashedBuffer = false;
    
    for (int i = 0; i < bufferNumber_ && !haveCrashedBuffer; ++i)
    {
        haveCrashedBuffer = buffers_[i].isCrashed;
    }
    if (bufferNumber >= 0 && bufferNumber < bufferNumber_ && 
        !haveCrashedBuffer)
    {
        buffers_[bufferNumber].reset();
        buffers_[bufferNumber].isCrashed = true;
    }
}

// (9) Восстановить утраченную информацию
void bat::Raid5::recoverInformation()
{
    int crashedCount = 0;
    int crashedNumber = 0;
    Block temp;
    
    for (int i = 0; i < bufferNumber_; ++i)
    {
        if (buffers_[i].isCrashed)
        {
            ++crashedCount;
            crashedNumber = i;
        }
    }
    if (crashedCount == 1)
    {
        for (int i = 0; i < bufferSize_; ++i)
        {
            temp.reset();
            for (int j = 0; j < bufferNumber_; ++j)
            {
                if (j != crashedNumber)
                {
                    temp ^= buffers_[j].blocks[i];
                }
            }
            buffers_[crashedNumber].blocks[i] = temp;
        }
        resetStatuses();
    }
}

// (10) Сбрасывает значения всех статусов
void bat::Raid5::resetStatuses()
{
    for (int i = 0; i < bufferNumber_; ++i)
    {
        buffers_[i].resetStatus();
    }
}

// (11) Сбрасывает значения всех битов до нуля
void bat::Raid5::reset()
{
    for (int i = 0; i < bufferNumber_; ++i)
    {
        buffers_[i].reset();
    }
}

// (12) Очищает элементы буфера
void bat::Raid5::clear()
{
    buffers_.clear();
}

// (13) Деструктор
bat::Raid5::~Raid5()
{
    clear();
}