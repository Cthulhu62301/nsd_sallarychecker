#include "class.h"
#include "class.cpp"
#include <string>




int main(){
    
    salary test{};
    int f {0};
    test.showday();
    do {
        f = 0;
        int in {};
        cout << "1. обновить время" << endl <<  "2. внести урок" << endl << "0. выход" << endl << "Выберите опцию: ";
        cin >> in;
        switch (in){
        case 1:
            cout << endl;
            test.showday();
            f = 1;
            break;
        case 2:
            cout << endl;
            cin.clear();
            test.salaryin();
            f = 1;
            break;
        default:
            f = 1;
            cout << endl << "Введите корректную опцию" << endl << endl << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        

    }
    while (f == 1);
    return 0;
}