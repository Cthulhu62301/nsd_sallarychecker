// Имена файлов обычно даются по имени класса в этом файле
// Но при этом стиль именования файла может отличаться от стиля именования класса

// pragma once - это тот же хэдер гуард, но проще в написании
// его раньше не рекомендовали использовать, т к он не поддерживается старыми компиляторами
// но вряд ли у кого-то в наши дни появиться компилятор 2008 года
#pragma once

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <cstring>
#include <ctime>
#include <stdio.h>
#include <vector>
#include <openssl/evp.h>
#include <openssl/des.h>


enum LessonType
{
    trial, 
    lesson, 
    indiv,
    count, 
};

enum Month
{
    Jan = 1,
    Feb,
    Mar,
    Apr,
    May,
    Jun,
    Jul,
    Sep,
    Oct,
    Nov,
    Dec,
};

struct L_date
{
    L_date(std::string date) 
    {
        std::string m{date.substr(0,2)};
        std::string d{date.substr(3,2)};
        std::string mn{date.substr(9,2)};
        std::string h{date.substr(6,2)};
        this->month = atoi(m.c_str());
        this->day = atoi(d.c_str());
        this->hour = atoi(h.c_str());
        this->min = atoi(mn.c_str());
    }
    L_date(){}
    int month;
    int day;
    int hour;
    int min;
};

struct Lesson
{
    Lesson (int idx, L_date date, int l_type, unsigned int cost): idx{idx}, date{date}, l_type{l_type}, cost{cost}{}
    Lesson (){}
    int idx;
    L_date date;
    int l_type;
    unsigned int cost;
};

class SalaryHandler
{
public:
    void printLocalTime();
    void writeUserLessonInfo();
    void readUserLessonUI();
    
private:
    
    const unsigned int lessonsCost[LessonType::count] {500, 350, 450};
    int readLessonInfoFromFile(int l_pos);
    void consoleReadIn(int& var, int count);
    void consoleWriteIn(int& var);
    int readUserLessonIdx();
    int readUserLessonDate();
    
    void consoleDateIn(std::string& var, int& shouldExit); 
    int writeLessonInfoToFile(std::string date, LessonType type);
    void encryptData();
    int getCountOfData();
    int getMonth(std::string date);
    int writeLessonToBin(std::string date, LessonType Ltype);
    int readLessonFromBin(unsigned int idx);
    std::string getLType(Lesson* ptr);
    std::string formatMin(Lesson* ptr);
    bool validReadCk(int count, int in);
    bool validInCk(int in);
    bool validDateCk(std::string date);
};

Lesson readStruct(std::ifstream& file);