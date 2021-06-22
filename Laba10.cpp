﻿
#include <iostream>
#include <string>
#include <cstring> // использование функций для работы со строками
#include <algorithm> // испольование функции swap()
#include <fstream> // работа с файлами
#include <Windows.h> // для русификации 
#include <locale>
using namespace std;

// ---------------------------------------------- Вспомогательные функции (начало)
// функция вывода меню
void print_menu() {
    cout << "1. Добавить новый элемент" << endl;
    cout << "2. Распечатать базу данных" << endl;
    cout << "3. Поиск врача по ФИО" << endl;
    cout << "4. Фильтр по квалификации и специальности (найти врачей заданной специальности и квалификации)" << endl;
    cout << "5. Сортировать по алфавиту" << endl;
    cout << "6. Записаться к врачу" << endl;
    cout << "7. Количество записей в определённую дату " << endl;
    cout << "8. Выход из программы" << endl;
    cout << ">";
}
// функция проверки корректности ввода пункта меню / специальности / квалификации
int check_input(char choice[]) {
    int var = -1;
    int str;
    bool flag = false;
    while (flag == false) {
        try {
            cin >> str;
            if (strcmp(choice, "spec") == 0) {
                if (!cin.fail()) {
                    if (1 <= str && str <= 3) {
                        flag = true;
                        break;
                    }
                    else {
                        throw invalid_argument("Ошибка: введенное число не соответствует диапазону! Попробуйте снова\n>");
                    }
                }
                else {
                    throw invalid_argument("Ошибка: на вход ожидалось целое число! Попробуйте снова\n>");
                }
            }
                if (strcmp(choice, "qual") == 0) {
                    if (!cin.fail()) {
                        if (0 <= str && str <= 2) {
                            flag = true;
                            break;
                        }
                        else {
                            throw invalid_argument("Ошибка: введенное число не соответствует диапазону! Попробуйте снова\n>");
                        }
                    }
                    else {
                        throw invalid_argument("Ошибка: на вход ожидалось целое число! Попробуйте снова\n>");
                    }
                }
            }
                catch (invalid_argument e) {
                    cout << e.what();
                    cin.clear();
                    cin.ignore(cin.rdbuf()->in_avail());
                };
        }
        return str;
    }



//    if (strlen(str) == 1) {
//        char symb = str[0];
//        if (isdigit(symb)) {
//            symb = symb - '0'; // '5' (char) -> 5 (int)
//            if (strcmp(choice, "menu") == 0) {
//                if (1 <= symb && symb <= 7) {
//                    var = symb;
//                }
//            }
//            if (strcmp(choice, "spec") == 0) {
//                if (1 <= symb && symb <= 3) {
//                    var = symb;
//                }
//            }
//            if (strcmp(choice, "qual") == 0) {
//                if (0 <= symb && symb <= 2) {
//                    var = symb;
//                }
//            }
//        }
//    }
//    return var;
//}
// функция ввода пункта меню / специальности / квалификации
int get_variant() {
    bool flag = false;
    int ans;
    while (flag == false) {
        try {
            cin >> ans;
            if (!cin.fail()) {
                if (1 <= ans && ans <= 8) {
                    flag = true;
                    break;
                }
                else {
                    throw invalid_argument("Ошибка: введенное число не соответствует диапазону! Попробуйте снова\n>");
                }
            }
            else {
                throw invalid_argument("Ошибка: на вход ожидалось целое число! Попробуйте снова\n>");
            }
        }
        catch (invalid_argument e) {
            cout << e.what();
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail());
        };
    }
    return ans;
}
         
// функция вывода шапки базы данных для врачей
void print_title_doc() {
    cout << "№:\t";
    cout << "Специальность:\t";
    cout << "Квалификация:\t";
    cout << "ФИО врача:\t";
    cout << endl;
    cout << "-------------------------------------------------------------------------" << endl;
}

//функция шапки для клиентов
void print_title_client() {
    cout << "№:\t\t";
    cout << "ФИО клиента:\t\t";
    cout << "Дата приёма:\t\t";
    cout << "ФИО ведущего врача:\t";
    cout << endl;
    cout << "-------------------------------------------------------------------------" << endl;
}
// ---------------------------------------------- Вспомогательные функции (конец)

// ---------------------------------------------- Класс Full_name (начало) 
class Full_name {
private:
    char surname[50]; // фамилия
    char name[50];  // имя
    char patronymic[50]; // отчество
public:
    Full_name()
    {
        cout << "Full_name init" << endl;
    }
    friend class Doctor;
    friend class Clinic;
    friend class Date;
    friend bool operator == (const Full_name&, const Full_name&);

    // перезагрузка оператора >> для ФИО
    friend istream& operator >> (istream& input, Full_name& fio) {
        cout << "Введите ФИО : ";
        cin >> fio.surname;
        cin >> fio.name;
        cin >> fio.patronymic;
        return input;
    }

    // перегрузка оператора << для ФИО
    friend ostream& operator << (ostream& output, Full_name& fio) {
        cout << fio.surname << " " << fio.name << " " << fio.patronymic;
        return output;
    }
};

// перезагрузка оператора ==
bool operator == (const Full_name& fio1, const Full_name& fio2) {
    bool ans = false;
    if (strcmp(fio1.surname, fio2.surname) == 0 &&
        strcmp(fio1.name, fio2.name) == 0 &&
        strcmp(fio1.patronymic, fio2.patronymic) == 0) {
        ans = true;
    }
    return ans;
}




//// функция вывода ФИО
//void Full_name::print_full_name() {
//    cout << surname << " " << name << " " << patronymic;
//}
// ---------------------------------------------- Класс Full_name (конец) 

// ---------------------------------------------- Класс Date (начало)

class Date {
private:
    int day;
    int month;
    int year;
public:
    void print_date();
    friend class Doctor;
    friend class Clinic;
    friend class Common;
    friend class Client;
    friend bool operator == (const Date&, const Date&);
    friend ostream& operator << (ostream& output, Date& date) {
        cout << date.day << "." << date.month << "." << date.year;
        return output;
    }
};

bool operator == (const Date& date1, const Date& date2) {
    bool ans = false;
    if ((date1.year == date2.year)  &&
        (date1.month == date2.month) &&
        (date1.day == date2.day)) {
        ans = true;
    }
    return ans;
}

//void Date::print_date() {
//    cout << day << "." << month << "." << year;
//}

// ---------------------------------------------- Класс Date (конец)

// ---------------------------------------------- Класс Common (начало)

class Common {
protected:
    Full_name fio;
};

//void Common::basic_print() {
//    cout << kolp;
//    fio.print_full_name();
//    cout << endl;
//}

// ---------------------------------------------- Класс Common (конец)


// ---------------------------------------------- Класс Clinic (начало)
class Clinic : public Common {
private:
    int specialty; // специальность (1-терапевт, 2-кардиолог, 3-стоматолог)
    int qualification; // квалификация (0-высшая, 1-первая, 2-вторая)
    int kolvo = 0;    //количество записей
public:
    friend class Doctor;
    friend class Client;
    // перезагрузка оператора >>
    friend std::istream& operator >> (std::istream& input, Clinic& doc)
    {
        cout << "Специализация: ";
        char choice1[] = "spec";
        doc.specialty = check_input(choice1);
        cout << "Квалификация: ";
        char choice2[] = "qual";
        doc.qualification = check_input(choice2);
        cin >> doc.fio;
        return input;
    }
    friend ostream& operator << (ostream& output, Clinic& doc)
    {
        cout << doc.specialty << "\t\t";
        cout << doc.qualification << "\t\t";
        cout << doc.fio << "\t\t";
        cout << endl;
        return output;
    }
};

// функция вывода полей класса Clinic
//void Clinic::basic_print() {
//    cout << specialty << "\t\t";
//    cout << qualification << "\t\t";
//    fio.print_full_name();
//    cout << endl;
//}

// ---------------------------------------------- Класс Clinic (конец)


// ---------------------------------------------- Класс Client (начало)
class Client : public Common {
private:
    Date date;
    int num;
    Full_name fio2;
public:
    friend class Doctor;
    friend class Clinic;
    friend ostream& operator << (ostream& output, Client& clients)
    {
        cout << clients.fio << "\t\t";
        cout << clients.date << "\t\t";
        cout << clients.fio2 << "\t\t";
        cout << endl;
        return output;
    }
}; 
// функция вывода полей класса Client
//void Client::print_info() {
//    fio.print_full_name();
//    cout << "\t";
//    date.print_date();
//    cout << "\t";
//}

// ---------------------------------------------- Класс Client (конец)

// ---------------------------------------------- Класс Doctor (начало)

class Doctor {
private:
    int count;  // счетчик объектов БД
    int kolclient; // счётчк объектов клиентов
    Clinic* clinics;
    Client* clients;
public:
    Doctor() {
        count = 0;
        kolclient = 0;
        Clinic* clinics = new Clinic[count];
    }
    void reading_DB_from_file();
    void add_new_item_to_DB();
    void print_DB();
    void search_by_full_name();
    void search_by_spec_and_qual();
    void sort_by_alphabet();
    void writing_DB_to_file();
    void zapis();
    void check_date();

    ~Doctor() {
        delete[] clinics;
    }

};




// функция чтения базы данных из файла 
void Doctor::reading_DB_from_file() {
    fstream f_in;
    f_in.open("BD1.txt", ios::in);
    if (f_in.peek() == EOF) {
        cout << "Файл пуст. Приступаем к заполнению БД." << endl;
    }
    else {
        cout << "В БД уже есть записи. Считываю и распечатываю данные." << endl;
        int id; // номер доктора в таблице
        int i = 0; // счетчик цикла;
        while (!f_in.eof()) {
            clinics = (Clinic*)realloc(clinics, (count + 1) * sizeof(Clinic)); // увеличиваем вместимость массива
            f_in >> id >> clinics[i].specialty >> clinics[i].qualification;
            f_in >> clinics[i].fio.surname >> clinics[i].fio.name >> clinics[i].fio.patronymic;
            i += 1;
            count += 1; // увеличиваем размер массива
        }
        count -= 1;
    }
    f_in.close();
    f_in.open("BD2.txt", ios::in);
    if (f_in.peek() == EOF) {
        cout << "Записей нет" << endl;
        system("pause");
    }
    else {
        int i = 0;  // счетчик цикла;
        int id;
        while (!f_in.eof()) {
            clients = (Client*)realloc(clients, (kolclient + 1) * sizeof(Client));
            f_in >> id >> clients[i].fio.surname >> clients[i].fio.name >> clients[i].fio.patronymic;
            f_in >> clients[i].date.day >> clients[i].date.month >> clients[i].date.year;
            f_in >> clients[i].fio2.surname >> clients[i].fio2.name >> clients[i].fio2.patronymic;
            i += 1;
            kolclient += 1;
        }
        kolclient -= 1;
        f_in.close();
        print_DB();
    }
}

// функция добавления нового элемента в базу данных 
void Doctor::add_new_item_to_DB() {
    clinics = (Clinic*)realloc(clinics, (count + 1) * sizeof(Clinic)); // увеличиваем вместимость массива
    cin >> clinics[count];    // вводим данные и добавляем новый элемент в базу данных
    count += 1;    // увеличиваем переменную count на 1
}


// функция вывода базы данных
void Doctor::print_DB() {
    print_title_doc();
    for (int i = 0; i < count; i++) {
        cout << i << "\t";
        cout << clinics[i];
    }
    cout << endl;
    print_title_client();
    for (int i = 0; i < kolclient; i++) {
        cout << i << "\t";
        cout << clients[i];
    }
    cout << "Кол-во записей: " << kolclient << endl;
}

// функция поиска докторов по ФИО
void Doctor::search_by_full_name() {
    cout << "Введите ФИО интересующего врача: ";
    Full_name new_full_name;
    cin >> new_full_name.surname;
    cin >> new_full_name.name;
    cin >> new_full_name.patronymic;
    int flag = 0; // флаг для подсчета кол-ва совпадений
    for (int i = 0; i < count; i++) {
        if (clinics[i].fio == new_full_name) {
            flag += 1;
            cout << "Найдено совпадение:" << endl;
            print_title_doc();
            cout << i << "\t";
            cout << clinics[i];
        }
    }
    if (flag == 0) {
        cout << "Не найдено совпадений :(" << endl;
    }
}

// функция поиска докторов по специальности и квалификации 
void Doctor::search_by_spec_and_qual() {
    cout << "Введите специальность: ";
    char choice1[] = "spec";
    int new_spec = get_variant();
    cout << "Введите квалификацию: ";
    char choice2[] = "qual";
    int new_qual = get_variant();
    int flag = 0; // флаг для подсчета кол-ва совпадений
    for (int i = 0; i < count; i++) {
        if (clinics[i].specialty == new_spec && clinics[i].qualification == new_qual) {
            flag += 1;
            cout << "Найдено совпадение:" << endl;
            print_title_doc();
            cout << i << "\t";
            cout << clinics[i];
        }
    }
    if (flag == 0) {
        cout << "Не найдено совпадений :(" << endl;
    }
}

// функция сортировки базы данных по фамилии доктора
void Doctor::sort_by_alphabet() {
    cout << "Отсортированная база данных по фамилии врача: " << endl;
    // Сортировка
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (clinics[j].fio.surname[0] > clinics[j + 1].fio.surname[0]) {
                swap(clinics[j], clinics[j + 1]);
            }
        }
    }
    print_DB();
}

// функция записи к врачу
void Doctor::zapis() {
    int flag = 0; // флаг для подсчета кол-ва совпадений
    clients = (Client*)realloc(clients, (kolclient + 1) * sizeof(Client));
    while (flag == 0) {
        cout << "Введите ФИО интересующего врача: ";
        Full_name new_full_name;
        cin >> new_full_name;
        for (int i = 0; i < count; i++) {
            if (clinics[i].fio == new_full_name) {
                flag += 1;
                clients[kolclient].fio2 = clinics[i].fio;
                cout << "Найдено совпадение:" << endl;
                print_title_doc();
                cout << i << "\t";
                cout << clinics[i];
            }
        }
        if (flag == 0) {
            cout << "Не найдено совпадений, внимательно проверьте ФИО врача или запишитесь к другому специалисту" << endl;
        }
    }
    cout << "Выберите удобную дату посещения DDMMYYYY" << endl;
    cout << "Год: ";
    cin >> clients[kolclient].date.year;
    cout << endl;
    cout << "Месяц: ";
    cin >> clients[kolclient].date.month;
    cout << endl;
    cout << "день: ";
    cin >> clients[kolclient].date.day;
    cout << endl;
    cin >> clients[kolclient].fio;
    cout << "Вы успешно записаны!" << endl;
    kolclient += 1;
}


// проверка записи на дату 
void Doctor::check_date() {
    int kol = 0;
    Date newdate;
    cout << "Введите интересующую дату: " << endl;
    cout << "Год: ";
    cin >> newdate.year;
    cout << endl;
    cout << "Месяц: ";
    cin >> newdate.month;
    cout << endl;
    cout << "день: ";
    cin >> newdate.day;
    cout << endl;
    for (int i = 0; i < kolclient; ++i) {
        if (clients[i].date == newdate) {
            kol++;
        }
    }
    cout << "Количество записей в данный день: " << kol << endl;
}

// функция записи базы данных в файл
void Doctor::writing_DB_to_file() {
    fstream f_out;
    f_out.open("BD1.txt", ios::out);
    for (int i = 0; i < count; i++) {
        f_out << i << " ";
        f_out << clinics[i].specialty << " ";
        f_out << clinics[i].qualification << " ";
        f_out << clinics[i].fio.surname << " " << clinics[i].fio.name << " " << clinics[i].fio.patronymic<<" ";
    }
    f_out << endl;
    f_out.close();

    f_out.open("BD2.txt", ios::out);
    for (int i = 0; i < kolclient; i++) {
        f_out << i << " ";
        f_out << clients[i].fio.surname << " " << clients[i].fio.name << " " << clients[i].fio.patronymic << " ";
        f_out << clients[i].date.day << " " << clients[i].date.month << " " << clients[i].date.year << " ";
        f_out << clients[i].fio2.surname << " " << clients[i].fio2.name << " " << clients[i].fio2.patronymic << " ";
    }
    f_out << endl;
    f_out.close();
}


// функция работы меню
void menu(Doctor* first_clinic) {
    int var; // выбранный пункт меню
    do {
        print_menu(); // выводим меню на экран
        //char choice[] = "menu";
        var = get_variant(); // получаем номер выбранного пункта меню
        switch (var) {
        case 1:
            first_clinic->add_new_item_to_DB();
            break;
        case 2:
            first_clinic->print_DB();
            break;
        case 3:
            first_clinic->search_by_full_name();
            break;
        case 4:
            first_clinic->search_by_spec_and_qual();
            break;
        case 5:
            first_clinic->sort_by_alphabet();
            break;
        case 6:
            first_clinic->zapis();
            break;
        case 7:
            first_clinic->check_date();
            break;
        }
        if (var != 8)
            system("pause"); // задерживаем выполнение
    } while (var != 8);
}
// ---------------------------------------------- Класс Doctor (конец)
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    Doctor first_doctor;
    first_doctor.reading_DB_from_file();
    menu(&first_doctor);
    first_doctor.writing_DB_to_file();
}




