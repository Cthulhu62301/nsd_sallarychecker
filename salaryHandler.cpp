#include "salaryHandler.h"

void SalaryHandler::printLocalTime()
{
    std::time_t now = std::time(nullptr);
    std::tm *local = std::localtime(&now);

    std::cout << "Local time: " << std::ctime(&now) << '\n';
    std::cout << "Time now: " << local->tm_hour << ':' << local->tm_min << ':' << local->tm_sec << '\n';
}

void SalaryHandler::writeUserLessonInfo()
{
    std::cout << "дата и время формата дд:мм чч:мм: ";
    std::string date { };
    std::getline(std::cin, date);

    std::cout << "выбери урок: \n1. пробный\n2. урок\n3. индивидуальное\nвыбор: ";
    int input { };
    std::cin >> input;
    std::cin.clear();

    if (input >= 1 && input <= 3)
        writeLessonInfo(date, static_cast<LessonType>(input));
    else
        std::cout << "Incorrect input!" << std::endl;
}

// TODO: запись общей суммы за месяц в бинарный файл
// помесячный учет полной суммы через бинарные файлы
// делать объекты на каждый месяц
int SalaryHandler::writeLessonInfo(std::string date, LessonType type)
{
    std::fstream dataFile("maindata.txt", std::ios::app);
    if (!dataFile.is_open())
        return 1;

    dataFile << date << ' ';
    if (type == LessonType::trial)
        dataFile << "пробный " << TRIAL_COST;
    else if (type == LessonType::lesson)
        dataFile << "урок " << LESSON_COST;
    else if (type == LessonType::indiv)
        dataFile << "индив " << INDIV_COST;
    dataFile << '\n';

    dataFile.close();
    return 0;
}
