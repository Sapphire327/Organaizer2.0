#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <conio.h>
using namespace std;
void SetCursor(int, int);//Прототип функции

class Note {
    string name;
    string note;
    SYSTEMTIME createtime;
    SYSTEMTIME changetime;
    bool done = 0;
public:
    Note() {
        changetime.wYear = 0;
        createtime.wYear = 0;
    }
    Note(string name) {
        this->name = name;
        changetime.wYear = 0;
        createtime.wYear = 0;
    }

    string get_name() {
        return name;
    }
    string get_note() {
        return note;
    }
    SYSTEMTIME get_createtime() {
        return createtime;
    }
    SYSTEMTIME get_changetime() {
        return changetime;
    }
    bool get_done() {
        return done;
    }
    void set_name(string name) {
        this->name = name;
    }
    void set_note(string note) {
        this->note = note;
    }
    void set_createtime(SYSTEMTIME createtime) {
        this->createtime = createtime;
    }
    void set_changetime(SYSTEMTIME changetime) {
        this->changetime = changetime;
    }
    void set_done(bool done) {
        this->done = done;
    }
    void ClearChangeTime() {
        changetime.wYear = 0;
    }
    void printcreatetime() {
        cout << createtime.wYear << "." << createtime.wMonth << "." << createtime.wDay << " " << createtime.wHour << ":" << createtime.wMinute;
    }
    void printchangetime() {
        cout << changetime.wYear << "." << changetime.wMonth << "." << changetime.wDay << " " << changetime.wHour << ":" << changetime.wMinute;
    }

    void SetChangeTime() {
        GetLocalTime(&changetime);
    }
    void ClearName() {
        name = "";
    }
    void SetCreateTime() {
        GetLocalTime(&createtime);
    }
    void printgraph(bool noteorname) {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        if (!noteorname)
            SetConsoleTextAttribute(handle, 3);
        SetCursor(34, 4); cout << "|";
        SetCursor(35, 4); cout << name;
        SetCursor(85, 4); cout << "|";
        SetCursor(35, 3);
        cout << "==================================================";
        SetCursor(35, 5);
        if (!noteorname) {
            cout << "==================================================";
            SetConsoleTextAttribute(handle, 8);
        }
        else {
            SetConsoleTextAttribute(handle, 3);
            cout << "==================================================";
        }
        int x = 35;
        int y = 6;
        SetCursor(x, y);
        for (int i = 0; i < note.size(); i++) {
            if (i != 0 && i % 50 == 0) {
                SetCursor(x, ++y);
            }
            cout << note[i];
        }
        int i = 0;
        for (i; i < 10; i++) {
            SetCursor(34, 6 + i); cout << "|";
            SetCursor(85, 6 + i); cout << "|";
        }
        SetCursor(35, 6 + i);
        cout << "==================================================";
        SetConsoleTextAttribute(handle, 8);

    }
    void change() {
        bool choice = 0;
        int press = 0;
        while (press != 27) {
            printgraph(choice);
            press = _getch();
            if (press == 119 || press == 72 || press == 115 || press == 80)
                choice = !choice;
            if (press != 27 && !choice && press != 224 && press != 72 && press != 75 && press != 80 && press != 77&&press != 13) {
                cinname(press);
                if (createtime.wYear != 0)
                    SetChangeTime();
            }
            if (press != 27 && choice && press != 224 && press != 72 && press != 75 && press != 80 && press != 77 && press != 13) {
                cinnote(press);
                if (createtime.wYear != 0)
                    SetChangeTime();

            }
            if (press == 27) {
                system("cls");
                break;
            }
        }
    }
    void cinname(char a) {//Функция для ввода(Не допускает больше определенного количества букв и позволяет изменять записанный ранее текс)
        SetCursor(35, 4);//Устанавливаем курсор в положение,где стоит нужная строка
        bool first = 1;
        while (a != '\r' && a != '\x1b') {//Пока не нажмем на Enter цикл не завершится
            SetCursor(35, 4);//Устанавливаем курсор в положение,где стоит нужная строка
            cout << "                                                 ";//Очищаем её от предыдущего текста
            SetCursor(35, 4);//Устанавливаем курсор в положение,где стоит нужная строка
            cout << name;//Выводим строку
            if (!first) {
                a = _getch();//Забираем символ,который ввёл пользователь
            }
            if (a != '\b' && name.size() < 49 && a != '\r' && a != '\x1b' && a != 72 && a != 75 && a != 80 && a != 77) {//Если это не backspace и не Enter,и букв меньше 49,то добавляем букву к нашему тексту
                name += a;
            }
            if (a == '\b' && name.size() > 0 && a != '\x1b') {//Если нажали на backspace,тогда убираем последний символ
                name.pop_back();
            }
            first = 0;
        }
    }
    void cinnote(char a) {
        int x = 35;
        int y = 6;
        bool first = 1;
        SetCursor(x, y);
        while (a != '\r' && a != '\x1b') {

            SetCursor(x, y);
            cout << "                                                  ";
            x = 35;
            y = 6;
            SetCursor(x, y);
            for (int i = 0; i < note.size(); i++) {
                if (i != 0 && i % 50 == 0) {
                    SetCursor(x, ++y);
                }
                cout << note[i];
            }

            if (!first) {
                a = _getch();//Забираем символ,который ввёл пользователь
            }
            if (a != '\b' && note.size() <= 499 && a != '\r' && a != 72 && a != 75 && a != 80 && a != 77 && a != '\x1b') {
                note += a;
            }
            if (a == '\b' && note.size() > 0) {
                note.pop_back();
            }
            first = 0;
        }
    }
    void printNote(int i) {
        SetCursor(20, 11 + i);       //ставим курсор в нужную позицию
        cout << name;
        if (createtime.wYear != 0) {
            SetCursor(72, 11 + i);
            printcreatetime();
        }
        if (changetime.wYear != 0) {
            SetCursor(90, 11 + i);
            printchangetime();
        }
        SetCursor(15, 11 + i);
        if (done)
            cout << "\\/";
        else
            cout << "  ";
    }
};

void printrules() {//Рисуем инструкцию
    SetCursor(19, 1);
    cout << "Чтобы создать или изменить заметку,нажмите Enter";
    SetCursor(19, 2);
    cout << "Чтобы удалить заметку нажмите del";
    SetCursor(19, 3);
    cout << "Чтобы отметить заметку нажмите пробел";
    SetCursor(19, 4);
    cout << "Чтобы скопировать заметку нажмите C";
    SetCursor(19, 5);
    cout << "Чтобы Вырезать заметку нажмите X";
    SetCursor(19, 6);
    cout << "Чтобы Вставить заметку нажмите V";
}
void printobolochka(int lenght = 10) {//Рисуем графику
    SetCursor(19, 9);
    cout << "Ваши заметки";
    SetCursor(73, 9);
    cout << "Дата создания";
    SetCursor(92, 9);
    cout << "Дата изменения";
    SetCursor(19, 10);
    if (lenght < 10)lenght = 10;
    cout << "=================================================== ================== ==================";
    int i = 0;
    for (i; i < lenght; i++) {
        SetCursor(18, 11 + i); cout << "|                                                   |                  |                  |";
    }
    SetCursor(19, 11 + i);
    cout << "=================================================== ================== ==================";
    SetCursor(16, 11 + i + 1);
    cout << "                                                                                                    ";


}
void SetCursor(int x, int y) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord; coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(handle, coord);
}
void save(vector<Note>spisok) {
    ofstream fout("Spisok.txt");
    vector<Note>::iterator it;
    it = spisok.begin();
    fout << spisok.size() - 1 << endl;
    for (; it + 1 != spisok.end(); it++) {
        fout << it->get_name() << endl;
        fout << it->get_note() << endl;

        fout << it->get_createtime().wYear << " ";
        fout << it->get_createtime().wMonth << " ";
        fout << it->get_createtime().wDay << " ";
        fout << it->get_createtime().wHour << " ";
        fout << it->get_createtime().wMinute << endl;

        fout << it->get_changetime().wYear << " ";
        fout << it->get_changetime().wMonth << " ";
        fout << it->get_changetime().wDay << " ";
        fout << it->get_changetime().wHour << " ";
        fout << it->get_changetime().wMinute << endl;
        fout << it->get_done() << endl;
    }
    fout.close();
}
void load(vector<Note>& spisok) {//функция загрузки данных
    ifstream fout("Spisok.txt");    //Проверка на наличие файла
    fout.close();
    if (!fout) {
        ofstream ft("Spisok.txt");
        ft.close();
    }

    ifstream fin("Spisok.txt");//открываем файл под названием Spisok.txt
    int size;
    fin >> size;
    char tempchar[500];
    SYSTEMTIME temptime;
    bool done;
    for (int i = 0; i < size; i++) {
        fin.getline(tempchar, 1);
        Note temp;
        fin.getline(tempchar, 50);
        temp.set_name(tempchar);
        fin.getline(tempchar, 500);
        temp.set_note(tempchar);
        fin >> temptime.wYear;
        fin >> temptime.wMonth;
        fin >> temptime.wDay;
        fin >> temptime.wHour;
        fin >> temptime.wMinute;
        fin.getline(tempchar, 1);
        temp.set_createtime(temptime);
        fin >> temptime.wYear;
        fin >> temptime.wMonth;
        fin >> temptime.wDay;
        fin >> temptime.wHour;
        fin >> temptime.wMinute;
        temp.set_changetime(temptime);
        fin.getline(tempchar, 1);
        fin >> done;
        temp.set_done(done);
        spisok.push_back(temp);
    }

    fin.close();
}
void menu(vector<Note>& spisok) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 8);
    vector<Note>::iterator it;//Итератор
    int choice = 0;//переменная для выбора 
    int press;     //переменная для нажатий клавиш
    Note newnote("Создать новую заметку");
    Note Buffer;
    spisok.push_back(newnote);//Добавляем в конец массива заметку"Создать новую заметку"
    while (1)
    {
        SetCursor(20, 11);
        printrules();
        int i = 0;
        printobolochka(spisok.size() + 1);//Рисуем оболочку проги
        it = spisok.begin();            //инициализируем итератор в начало списка
        for (; it != spisok.end(); it++)//перебираем весь массив
        {
            if (choice == i)            //Если мы выбрали этот элемент,то выделяем его
            {
                SetConsoleTextAttribute(handle, 7);
                it->printNote(i);
                SetConsoleTextAttribute(handle, 8);
            }
            else {
                it->printNote(i);
            }//Иначе нет
            i++;
        }
        do {
            press = _getch();               //Захватываем клавишу
            if ((press == 119 || press == 72) && choice > 0) {
                SetCursor(20, 11 + choice);
                spisok[choice].printNote(choice);
                choice--;//вверх  
                SetCursor(20, 11 + choice);
                SetConsoleTextAttribute(handle, 7);
                spisok[choice].printNote(choice);
                SetConsoleTextAttribute(handle, 8);
            }
            if ((press == 115 || press == 80) && choice < i - 1) {
                SetCursor(20, 11 + choice);
                spisok[choice].printNote(choice);
                choice++;//вниз  
                SetCursor(20, 11 + choice);
                SetConsoleTextAttribute(handle, 7);
                spisok[choice].printNote(choice);
                SetConsoleTextAttribute(handle, 8);
            }
            if (press == 13 && choice != spisok.size() - 1) {//изменить заметку
                system("cls");
                spisok[choice].change();
                //spisok[choice].SetChangeTime();
                save(spisok);
                break;
            }//изменить заметку//изменить заметку//изменить заметку
            if (press == 13 && choice == spisok.size() - 1) {//Добавление новой заметки
                Note temp("Создать новую заметку");
                //SetCursor(20, 5 + i);//Ставим курсор в нужное место
                system("cls");
                spisok[choice].ClearName();
                spisok[choice].change();
                spisok[choice].SetCreateTime();
                spisok.push_back(temp);//Создаем новую заметку в последнее место в списке со словами "Создать новую заметку"
                save(spisok);//Сохраняем список
                break;
            }
            if ((press == 83) && choice < i - 1) {//Удаление элемента в списке
                spisok.erase(spisok.begin() + choice);//Удаляем выделенный элемент
                save(spisok);//Сохраняем список
                break;
            }
            if ((press == 32) && choice < i - 1) {
                spisok[choice].set_done(!spisok[choice].get_done());
                save(spisok);
                break;
            }
            if ((press == 241 || press == 99) && choice < i - 1) {//Скопировать
                Buffer = spisok[choice];
            }
            if ((press == 120 || press == 247) && choice < i - 1) {//вырезать
                Buffer = spisok[choice];
                spisok.erase(spisok.begin() + choice);//Удаляем выделенный элемент
                save(spisok);//Сохраняем список
                break;
            }
            if ((press == 118 || press == 236) && choice < i - 1 && Buffer.get_createtime().wYear != 0) {//вставить
                spisok.insert(spisok.begin() + choice + 1, Buffer);
                save(spisok);
                break;
            }

        } while (1);

    }
}
int main()
{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("mode con:cols=120 lines=500");

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    //Убираем мигание курсора
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(handle, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(handle, &structCursorInfo);

    vector<Note>spisok;
    load(spisok);
    menu(spisok);//запуск меню
}

//Версия 3.1