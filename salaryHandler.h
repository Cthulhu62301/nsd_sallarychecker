#pragma once

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <ctime>

enum LessonType
{
    trial = 1, // На самом деле, последующие элементы будут нумероваться по порядку автоматически
    lesson = 2, // Пронумерованы явно для наглядности
    indiv = 3,
};

class SalaryHandler
{
public:
    void printLocalTime();
    void writeUserLessonInfo();

private:
    const unsigned int TRIAL_COST { 500 };
    const unsigned int LESSON_COST { 350 };
    const unsigned int INDIV_COST { 450 };

    int writeLessonInfo(std::string date, LessonType type);
};
