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


class SalaryHandler
{
public:
    void printLocalTime();
    void writeUserLessonInfo();
    int readUserLessonInfo();

private:
    
    const unsigned int lessonsCost[LessonType::count] {500, 350, 450};

    int readLessonInfoFromFile(int l_pos);
    int writeLessonInfoToFile(std::string date, LessonType type);
    void encryptData();
};
