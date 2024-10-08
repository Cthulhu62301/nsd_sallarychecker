#include "salaryHandler.h"

// Определение функции-члена
// (таким же образом можно определить и константы и другие переменные)
void SalaryHandler::printLocalTime()
{
    // Ну тут просто имена более понятные дал
    // Имена в C - шляпа полнейшая, не учись плохому
    std::time_t now = std::time(nullptr); // nullptr - это литерал указателя, лучше юзать его, вместо 0 или NULL (что тоже = 0)
    std::tm *local = std::localtime(&now);

    // Про то, почему убрал std::endl, написал ниже
    std::cout << "Local time: " << std::ctime(&now) << '\n';
    std::cout << "Time now: " << local->tm_hour << ':' << local->tm_min << ':' << local->tm_sec << '\n';
}

void SalaryHandler::writeUserLessonInfo()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // getline() ложится, если не чистить буфер 0_0

    std::cout << "дата и время формата дд:мм чч:мм: ";
    std::string date { }; // Объявляю локальную переменную как можно ближе к ее первому использованию
    std::getline(std::cin, date);

    // Использовать std::endl не круто, т к он принудительно очищает буфер, что немного замедляет терминал
    // Лучше его не использовать, если нет на то везких причин
    // (Например, тебе надо быть уверенным, что ошибка выведется, перед тем, как прога крашнится)
    std::cout << "выбери урок: \n1. пробный\n2. урок\n3. индивидуальное\nвыбор: ";
    int input { }; // Объявляю локальную переменную как можно ближе к ее первому использованию
    std::cin >> input;
    std::cin.clear(); // Если честно, не уверен, что он здесь нужен, но работает - не трожь)

    if (input >= 1 && input <= LessonType::count) // Проверка на валидность числа
        // Если число валидное, то получаем тип урока (у каждого типа есть свой порядковый номер)
        writeLessonInfoToFile(date, static_cast<LessonType>(input - 1)); 
    else // Иначе - ошибка
        std::cout << "Incorrect input!" << std::endl;
}

// Используй слово туду, если хочешь оставить "метку" для фикса в будущем
// TODO: запись общей суммы за месяц в бинарный файл
// помесячный учет полной суммы через бинарные файлы
// делать объекты на каждый месяц
int SalaryHandler::writeLessonInfoToFile(std::string date, LessonType lessonType)
{
    // Инициализировал одной строкой, т к нет смысла разбивать объявление и присваение на две строки
    std::fstream dataFile("maindata.txt", std::ios::app);
    // Я знаю, что в 21 школе учили иначе, но на практике, все делают так)
    // (меньше вложенность и проще читать код, когда у тебя в самом начале обрабатываются краевые случаи)
    if (!dataFile.is_open())
        return 1;

    // Если у тебя от типа урока зависит еще какая-то информация,
    // то лучше всего вынести ее в отдельный класс или структуру,
    // если цена - это вся информация, то можно создать массив,
    // где будут храниться цены на уроки, по типу этого:
    // const int lessonCosts[LessonType::count] { 450, 600, 250 };
    // и тогда можно будет получить цену таким образом:
    // lessonCosts[static_cast<int>(lessonType)];
    // Предлагаю эти варианты, т к то, как реализовано это сейчас, не очень круто
    // (у нас же все таки ООП язык)
    dataFile << date << ' ';
    if (lessonType == LessonType::trial)
        dataFile << "пробный " << TRIAL_COST;
    else if (lessonType == LessonType::lesson)
        dataFile << "урок " << LESSON_COST;
    else if (lessonType == LessonType::indiv)
        dataFile << "индив " << INDIV_COST;
    dataFile << '\n';

    dataFile.close();
    return 0;
}
