#include "salaryHandler.h"


//std::string::find - поиск подстроки

void SalaryHandler::printLocalTime()
{
    std::time_t now = std::time(nullptr); 
    std::tm *local = std::localtime(&now);
    std::cout << "Local time: " << std::ctime(&now) << '\n';
    std::cout << "Time now: " << local->tm_hour << ':' << local->tm_min << ':' << local->tm_sec << "\n\n\n";
}

void SalaryHandler::writeUserLessonInfo()
{
    // int error{};
    int shouldExit{};
    std::string date { };
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // getline() ложится, если не чистить буфер 0_0   
    consoleDateIn(date, shouldExit);
    //TODO: записывать структуры в файл и оттуда же их читать
    //реализовать поиск по индексу, дате
    //прикрутить сортировку по дате
    if (shouldExit == 0){
        std::cout << "выбери урок: \n1. пробный\n2. урок\n3. индивидуальное\n0. выйти в меню\nвыбор: ";
        int input { };
        consoleWriteIn(input); 
        if (input == 0);
        else if (input != 0){
            writeLessonInfoToFile(date, static_cast<LessonType>(input - 1));
            writeLessonToBin(date, static_cast<LessonType>(input - 1));
        }
    }
}

void SalaryHandler::consoleDateIn(std::string& date, int& shouldExit){
    int error{};
    do {
        error = 0;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Для выхода введите q\nДата и время формата дд.мм чч:мм: "; 
        std::getline(std::cin, date);
        if (date == "q") {
            shouldExit = 2;
        }
        else
        if(!validDateCk(date)) {
            error = 1;
            std::cout << "Введите в верном формате\nНажмите любую кнопку,чтобы продолжить...";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        }
    } while (error == 1 || shouldExit == 1);
}

bool SalaryHandler::validInCk(int in){return !(in  >= 0 && in  <= LessonType::count);}

bool SalaryHandler::validDateCk(std::string date){
    //TODO: проверка на 28, 29, 30, 31 дней в месяце
    //возможно сделать структуру под время и записывать ее в бинарник
    if(date.length() != 11) return false;
    std::string month{date.substr(3,2)};
    std::string day{date.substr(0,2)};
    std::string min{date.substr(9,2)};
    std::string hour{date.substr(6,2)};
    bool b_month {(atoi(month.c_str()) > 0 && atoi(month.c_str()) <= 12)};
    bool b_day{(atoi(day.c_str()) > 0 && atoi(day.c_str()) <= 31)};
    bool b_min{(atoi(min.c_str()) >= 0 && atoi(min.c_str()) <= 60)};
    bool b_hour{(atoi(hour.c_str())>= 0 && atoi(hour.c_str()) <= 23)};
    bool f{
        date.find('.', 2) != std::string::npos &&
        date.find(':', 8) != std::string::npos &&
        date.find(' ', 5) != std::string::npos &&
        b_month && b_day && b_min && b_hour 
    };
    return f;
}

int SalaryHandler::getMonth(std::string date){
    std::string t_sub{date.substr(3,2)};
    return (atoi(t_sub.c_str()));
}

// TODO: запись общей суммы за месяц в бинарный файл
// помесячный учет полной суммы через бинарные файлы
// делать объекты на каждый месяц
int SalaryHandler::writeLessonInfoToFile(std::string date, LessonType lessonType)
{
    std::fstream dataFile("maindata.txt", std::ios::app);
    if (!dataFile.is_open()) return 1;
    int count {getCountOfData()};
    dataFile << count + 1 << ' ' << date << ' ';
    if (lessonType == LessonType::trial)
        dataFile  << " пробный " << lessonsCost[trial];
    else if (lessonType == LessonType::lesson)
        dataFile  << " урок " << lessonsCost[lesson];
    else if (lessonType == LessonType::indiv)
        dataFile  << " индив " << lessonsCost[indiv];
    dataFile << '\n';
    dataFile.close();
    // Lesson n{1, getMonth(date), date, lessonType, lessonsCost[lessonType]};
    return 0;
}
int SalaryHandler::getFullPayment(){
    std::ifstream file("maindata.bin", std::ios::binary);
    if (!file.is_open()){
        std::cout << "Can't open file for read\n";
        return 1;
    }
    unsigned int salary{};
    for(int i = 0; i < getCountOfData(); i++){
        Lesson tmp = readStruct(file);
        salary += tmp.cost;
    }
    std::cout << "Полная зарплата: " << salary << " Рублей\n";
    return 0;
}

int SalaryHandler::readUserLessonIdx(){
    int data_pos {};
    int count {getCountOfData()};
    std::cout << "количество записей: " << count << '\n';
    std::cout << "выберете номер записи: ";
    std::cin.clear();
    consoleReadIn(data_pos,count);
    readLessonInfoFromFile(data_pos);
    std::cout << "\nчтение с бинарника\n";
    readLessonFromBin(data_pos);
    std::cout << "введите любой символ, чтобы вернуться в меню...\n";
    std::scanf("%*s");
    std::getchar();
    return 0;
}

int SalaryHandler::readUserLessonDate(){
    std::cin.clear();
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max());
    std::string date;
    int shouldExit {};
    consoleDateIn(date, shouldExit);
    std::cout << '\n';
    std::ifstream file("maindata.bin", std::ios::binary);
    if (!file.is_open()){
        std::cout << "Can't open file\n";
        return 1;
    }
    Lesson out;
    L_date tmp(date);
    std::cout << "Найденные уроки за " << tmp.month << '.' << tmp.day << ":\n";
    if(shouldExit == 0){
        int i{};
        
        for (; i < getCountOfData(); i++){
            out = readStruct(file);
            if(out.date.month == tmp.month && out.date.day == tmp.day){
                std::cout << getLType(&out) << ' ' << out.cost << " Рублей\n";
            }
        }
        if (i == 0) std::cout << "Уроков не найдено\n";
    }
    file.close();
    return 0;
}

void SalaryHandler::readUserLessonUI(){
    std::cout << "1. По индексу\n2. По дате\n3. По типу урока\nВыберите метод поиска: ";
    std::cin.clear();
    char UserIn{};
    std::cin >> UserIn;
    switch (UserIn){
    case '1':
        readUserLessonIdx();
        break;
    case '2':
        std::cin.clear();
        // TODO: исправить баг со входом
        readUserLessonDate();
        break;
    case '3':
        // TODO: сделать поиск по типу уроков
        break;
    default:
        break;
    }
}

Lesson readStruct(std::ifstream& file){
    //TODO: сделать отдельную функцию чтения структуры из файла
    Lesson out;
    file.read(reinterpret_cast<char*>(&out), sizeof(Lesson));
    if (file.fail()){
        std::cout << "can't read file\n";
    }
    return out;
}



int SalaryHandler::writeLessonToBin(std::string date, LessonType type){
    Lesson tmp(getCountOfData(), L_date(date), type, lessonsCost[type]);
    std::ofstream file("maindata.bin", std::ios::binary | std::ios::app);
    if (!file.is_open()){
        std::cout << "can't open file for write\n";
        return 1;
    }
    file.write(reinterpret_cast<const char*>(&tmp), sizeof(Lesson));
    file.close();
    return 0;
}

int SalaryHandler::readLessonFromBin(unsigned int idx){
    std::ifstream file("maindata.bin", std::ios::binary);
    if (!file.is_open()){
        std::cout << "can't open file for reading\n";
        return 1;
    }
    if (idx > 0){
        file.seekg(sizeof(Lesson) * (idx - 1));
    }
    Lesson tmp = readStruct(file);
    std::cout << "Найденный урок: \n" << tmp.date.month << '.' << tmp.date.day << ' ' << tmp.date.hour << ':' << formatMin(&tmp) << ' ' 
    << getLType(&tmp) << ' ' << "\nСтоимость урока: " << tmp.cost << " Рублей\n";
    file.close();
    return 0;
}
std::string SalaryHandler::formatMin(Lesson* ptr){
    std::string out;
    if (ptr->date.min == 0) out = "00";
    else out = ptr->date.min;
    return out;
}
std::string SalaryHandler::getLType(Lesson* ptr) {
    std::string out;
    if (ptr->l_type == 0) out = "Пробный";
    else if(ptr->l_type == 1) out = "Урок";
    else if(ptr->l_type == 2) out = "Индивидуальное занятие";
    return out;
}


int SalaryHandler::getCountOfData(){
    std::ifstream data_count("maindata.txt", std::ios::in);
    if (!data_count.is_open()){
        std::cout << "Can't open file, try again\n";
        return -1;
    }
    std::string data_store;
    int count{};
    while (getline(data_count, data_store)){
        count++;
    }
    data_count.close();
    return count;
}
void SalaryHandler::consoleReadIn(int& var,int count){
    std::cin.clear();
    int f {};
    do{
        f = 0;
        std::cin >> var ;
        if (std::cin.fail() || validReadCk(count, var)){
            f = 1;
            std::cout << "введите коректное число: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (f == 1);
}
void SalaryHandler::consoleWriteIn(int& var){
    std::cin.clear();
    int f {};
    do {
        f = 0;
        std::cin >> var;
        if(std::cin.fail() || validInCk(var)){
            std::cout << var << '\n';
            f = 1;
            std::cout << "введи правильный тип урока\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (f == 1);
}

bool SalaryHandler::validReadCk(int count, int in){return !(in >= 1 && in <= count);} 

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
    std::cout << "\n";
    std::cin.clear();
    dataFile.close();
    return 0;
}




void SalaryHandler::encryptData() {
    //TODO: прикрутить шифрование
}

