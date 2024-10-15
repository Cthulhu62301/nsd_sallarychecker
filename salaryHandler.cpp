#include "salaryHandler.h"


//std::string::find - поиск подстроки

void SalaryHandler::printLocalTime()
{

    
    std::time_t now = std::time(nullptr); // nullptr - это литерал указателя, лучше юзать его, вместо 0 или NULL (что тоже = 0)
    std::tm *local = std::localtime(&now);

    
    std::cout << "Local time: " << std::ctime(&now) << '\n';
    std::cout << "Time now: " << local->tm_hour << ':' << local->tm_min << ':' << local->tm_sec << "\n\n\n";
}

void SalaryHandler::writeUserLessonInfo()
{
    int f{};
    std::string date { };
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // getline() ложится, если не чистить буфер 0_0
    do {
        f = 0;
        std::cout << "дата и время формата дд.мм чч:мм: "; 
        std::getline(std::cin, date);
        if(!validDateCk(date)) {
            f = 1;
            std::cout << "введите в верном формате\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // getline() ложится, если не чистить буфер 0_0
        }
    } while (f == 1);

    // Использовать std::endl не круто, т к он принудительно очищает буфер, что немного замедляет терминал
    // Лучше его не использовать, если нет на то везких причин
    // (Например, тебе надо быть уверенным, что ошибка выведется, перед тем, как прога крашнится)
    std::cout << "выбери урок: \n1. пробный\n2. урок\n3. индивидуальное\n0. выйти в меню\nвыбор: ";
    int input { };
    console_in(input, validInCk); 
    if (input == 0);
    else if (input != 0)
        
        writeLessonInfoToFile(date, static_cast<LessonType>(input - 1)); 
}

bool validInCk(int in){return !(in  >= 0 && in  <= LessonType::count);}

bool validDateCk(std::string date){
    //TODO: более строки условия валидации для даты и времени
    bool f{
        date.find('.', 2) != std::string::npos &&
        date.find(':', 8) != std::string::npos &&
        date.find(' ', 5) != std::string::npos &&
        date.length() == 11 
    };
    return f;
}

int SalaryHandler::getMonth(std::string date){
    std::string t_sub{date.substr(3,2)};
    return static_cast<Month>(atoi(t_sub.c_str()));
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
    std::cin.clear();
    //TODO: сделать более ООП коллбэк
    console_in(data_pos,count, validReadCk);
    readLessonInfoFromFile(data_pos);
    std::cout << "введите любой символ, чтобы вернуться в меню...\n";
    std::scanf("%*s");
    std::getchar();
    return 0;
}


void SalaryHandler::console_in(int& var,int count, bool (*callback)(int, int)){
    std::cin.clear();
    int f {};
    do{
        f = 0;
        std::cin >> var ;
        if (std::cin.fail() || callback(count, var)){
            f = 1;
            std::cout << "введите коректное число: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (f == 1);
}
void SalaryHandler::console_in(int& var, bool(*callback)(int)){
    std::cin.clear();
    int f {};
    do {
        f = 0;
        std::cin >> var;
        if(std::cin.fail() || callback(var)){
            std::cout << var << '\n';
            f = 1;
            std::cout << "введи правильный тип урока\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (f == 1);
}

bool validReadCk(int count, int in){return !(in >= 1 && in <= count);} 

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
    //TODO: прикрутить шифрование
}

