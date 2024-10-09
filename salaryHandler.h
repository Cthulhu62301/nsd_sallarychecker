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
#include <ctime>


enum LessonType
{
    trial, 
    lesson, 
    indiv,
    count, 
};


class SalaryHandler
{
public:
    void printLocalTime();
    void writeUserLessonInfo();

private:
    
    const unsigned int lessonsCost[LessonType::count] {500, 350, 450};

    int writeLessonInfoToFile(std::string date, LessonType type);
};
