#include "salaryHandler.h"


int main()
{
    SalaryHandler salaryHandler { };
    

    int shouldExit; 
    char userChoise;
    do {
        shouldExit = 0;
        salaryHandler.printLocalTime();
        std::cout << "1. обновить время\n2. внести урок\n3. просмотреть уроки\n5. TEST WRITE\n6. TEST READ\nq. выход\nВыберите опцию: ";
        std::cin >> userChoise;
        std::cout << '\n';
        switch (userChoise)
        {
            case 'q': 
                shouldExit = 1; 
                break;
            case '1': 
                salaryHandler.printLocalTime(); 
                break;
            case '2': 
                salaryHandler.writeUserLessonInfo(); 
                break;
            case '3':
                salaryHandler.readUserLessonInfo();
                break;
            default:
                std::cout << "Введите корректную опцию \n\n" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
    } while (!shouldExit);

    return 0;
}
