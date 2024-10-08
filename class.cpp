#include "class.h"




class salary
{
private:
    const unsigned indiv {450};
    const unsigned trial {500};
    const unsigned lesson {350};
    

public:
    

    void showday(){
        time_t now = time(0);
        tm *ltm = localtime(&now);
        char* dt = ctime(&now);


        cout << "local time: " << dt << endl;
        cout << "time now: " << ltm->tm_hour << ':' << ltm->tm_min << ':' << ltm->tm_sec << endl;
    }

    void salaryin(){
        string date {};
        int input{};
        cout << "дата и время формата дд:мм чч:мм: ";
        getline(cin, date);
        cout << "выбери урок: " << endl << "1. пробный" << endl << "2. урок" << endl << "3. индивидуальное" << endl << "выбор: ";
        cin >> input;
        cin.clear();
        switch (input)
        {
        case 1:
            data_in(date, l_type::trial);
            break;
        case 2:
            data_in(date, l_type::lesson);
            break;
        case 3:
            data_in(date, l_type::indiv);
            break;
        default:
            cout << "error occured" << endl;
        }
    }

// сделать запись общей суммы за месяц в бинарный файл
// сделать помесячный учет полной суммы через бинарные файлы
// делать объекты на каждый месяц

    int data_in(string date, l_type type){
        int f = 0;
        fstream out;
        out.open("maindata.txt", ios::app);
        if (out.is_open()){
            if (type == l_type::trial) {
                out << date << ' ' << "пробный " << trial << endl;
                out.close();
            }
            else
            if (type == l_type::lesson) {
                out << date << ' ' << "урок " << lesson << endl;
                out.close();
            }
            else
            if (type == l_type::indiv) {
                out << date << ' ' << "индив " << indiv << endl;
                out.close(); 
            }
        }
        else {
            f = 1;
        }
        return f;
    }
};