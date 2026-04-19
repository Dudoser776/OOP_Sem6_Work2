#include <iostream>
#include <string>

using namespace std;

// БАЗОВЫЙ КЛАСС - PERSON
class Person {
protected:
    string name;
    int age;
    string passport;

public:
    // Конструктор без параметров
    Person() {
        name = "Unknown";
        age = 0;
        passport = "0000-000000";
        cout << "[Person] Конструктор без параметров: "
             << name << ", " << age << ", " << passport << endl;
    }

    // Конструктор с параметрами
    Person(string n, int a, string pass) {
        name = n;
        age = a;
        passport = pass;
        cout << "[Person] Конструктор с параметрами: "
             << name << ", " << age << ", " << passport << endl;
    }

    // Конструктор копирования
    Person(const Person& other) {
        name = other.name;
        age = other.age;
        passport = other.passport;
        cout << "[Person] Конструктор копирования: "
             << name << ", " << age << ", " << passport << endl;
    }

    // Деструктор
    virtual ~Person() {
        cout << "[Person] Деструктор: "
             << name << ", " << age << ", " << passport << endl;
    }

    // Метод для вывода информации
    void introduce() {
        cout << "[Person] Представление: " << name << ", " << age << " лет, паспорт: " << passport << endl;
    }
};


int main() {
    cout << "\n=== Статическое создание объектов Person ===" << endl;
    Person p1;                                    // конструктор без параметров
    Person p2("Иван Иванов", 30, "1234-567890");  // конструктор с параметрами
    Person p3(p2);                                // конструктор копирования

    p1.introduce();
}
