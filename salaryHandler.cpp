#include "salaryHandler.h"


void SalaryHandler::printLocalTime()
{

    
    std::time_t now = std::time(nullptr); // nullptr - это литерал указателя, лучше юзать его, вместо 0 или NULL (что тоже = 0)
    std::tm *local = std::localtime(&now);

    
    std::cout << "Local time: " << std::ctime(&now) << '\n';
    std::cout << "Time now: " << local->tm_hour << ':' << local->tm_min << ':' << local->tm_sec << "\n\n\n";
}

void SalaryHandler::writeUserLessonInfo()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // getline() ложится, если не чистить буфер 0_0

    std::cout << "дата и время формата дд:мм чч:мм: ";
    std::string date { }; 
    std::getline(std::cin, date);

    // Использовать std::endl не круто, т к он принудительно очищает буфер, что немного замедляет терминал
    // Лучше его не использовать, если нет на то везких причин
    // (Например, тебе надо быть уверенным, что ошибка выведется, перед тем, как прога крашнится)
    std::cout << "выбери урок: \n1. пробный\n2. урок\n3. индивидуальное\nвыбор: ";
    int input { }; 
    std::cin >> input;
    std::cin.clear(); 

    if (input >= 1 && input <= LessonType::count) 
        writeLessonInfoToFile(date, static_cast<LessonType>(input - 1)); 
    else 
        std::cout << "Incorrect input!" << std::endl;
}


// TODO: запись общей суммы за месяц в бинарный файл
// помесячный учет полной суммы через бинарные файлы
// делать объекты на каждый месяц
int SalaryHandler::writeLessonInfoToFile(std::string date, LessonType lessonType)
{
    std::fstream dataFile("maindata.txt", std::ios::app);
    if (!dataFile.is_open())
        return 1;

    
    dataFile << date << ' ';
    if (lessonType == LessonType::trial)
        dataFile << "пробный " << lessonsCost[trial];
    else if (lessonType == LessonType::lesson)
        dataFile << "урок " << lessonsCost[lesson];
    else if (lessonType == LessonType::indiv)
        dataFile << "индив " << lessonsCost[indiv];
    dataFile << '\n';

    dataFile.close();
    return 0;
}

int SalaryHandler::readUserLessonInfo(){
    int data_pos {};
    int count {};
    std::string data_store;
    std::ifstream data_count("maindata.txt", std::ios::in);
    if (!data_count.is_open()){
        std::cout << "can't open file, try again\n";
        return 1;
    }
    while (getline(data_count, data_store)){
        count++;
    }
    data_count.close();
    std::cout << "количество записей: " << count << '\n';
    std::cout << "выберете номер записи: ";
    int f {};
    std::cin.clear();
    do {
        f = 0;
        std::cin >> data_pos;
        if (std::cin.fail() ||(data_pos > count || data_pos < 1)){
            f = 1;
            std::cout << "введите корректный номер: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (f == 1);
    readLessonInfoFromFile(data_pos);
    std::cout << "введите любой символ, чтобы вернуться в меню...\n";
    std::scanf("%*s");
    std::getchar();
    return 0;
}

int SalaryHandler::readLessonInfoFromFile(int l_pos){
    std::ifstream dataFile("maindata.txt", std::ios::in);
    if(!dataFile.is_open()) {
        std::cout << "can't open file for reading\n";
        return 1;
    }
    std::string output{};
    int i {1};
    while (getline(dataFile, output)){
        if (i == l_pos){
            std::cout << output << '\n';
        }
        i++;
    }
    std::cout << "\n\n\n";
    std::cin.clear();
    dataFile.close();
    return 0;
}




void SalaryHandler::encryptData() {
    //TODO: придумать архетиктуру файла данных
}

