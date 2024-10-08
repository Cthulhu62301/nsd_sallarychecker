// Никогда не инклюдь ничего, кроме хэдеров
#include "salaryHandler.h"

// Скобочки - это дело вкуса)
int main()
{
    SalaryHandler salaryHandler { };
    salaryHandler.printLocalTime();

    // Более понятные имена
    int shouldExit, userChoise;
    do {
        // Логику с выходом я изменил, т к не понял прикола каждый раз (в каждом ветвлении) присваивать значение 1
        // получается копирование кода на ровном месте (если в этом был все-таки какой-то смысл, то тогда нужно
        // изменить подход к проверке)
        shouldExit = 0;

        std::cout << "1. обновить время\n2. внести урок\n0. выход\nВыберите опцию: ";
        std::cin >> userChoise;
        std::cout << '\n';

        switch (userChoise)
        {
            // Часто пишут в одну строку, если у нас всего одна инструкция в кейса (не считая брэйк, конечно)
            // Но, все равно, все зависит от код стайла проекта
            case 0: shouldExit = 1; break;
            case 1: salaryHandler.printLocalTime(); break;
            case 2: salaryHandler.writeUserLessonInfo(); break;

            default:
                std::cout << "Введите корректную опцию \n\n" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
    } while (!shouldExit);

    return 0;
}
