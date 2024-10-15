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

struct Lesson
{
    Lesson (int number, Month mon, std::string date, LessonType type, unsigned int cost):number{number}, mon{mon}, date{date}, type{type}, cost{cost}{}
    int number;
    Month mon;
    std::string date;
    LessonType type;
    unsigned int cost;
};

class SalaryHandler
{
public:
    void printLocalTime();
    void writeUserLessonInfo();
    int readUserLessonInfo();

private:
    
    const unsigned int lessonsCost[LessonType::count] {500, 350, 450};
    // bool readValid = [](int count, int in) { return (in > count || in < 1);};
    bool (*callback)(int, int);
    void setCallback(bool(*fn)(int, int));
    int readLessonInfoFromFile(int l_pos);
    void console_in(int& var, int count, bool (*callback)(int, int));
    void console_in(int& var, bool(*callback)(int));
    int writeLessonInfoToFile(std::string date, LessonType type);
    void encryptData();
};
bool validReadCk(int count, int in);
bool validInCk(int in);