#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <locale>

using namespace std;

// РОДИТЕЛЬСКИЙ КЛАСС - PERSON
class Person {
protected:
    string name;
    int age;
    string passport;

public:
    Person() {
        name = "Unknown";
        age = 0;
        passport = "0000-000000";
        cout << "[Person] Конструктор без параметров: "
             << name << ", " << age << ", " << passport << endl;
    }

    Person(string n, int a, string pass) {
        name = n;
        age = a;
        passport = pass;
        cout << "[Person] Конструктор с параметрами: "
             << name << ", " << age << ", " << passport << endl;
    }

    virtual ~Person() {
        cout << "[Person] Деструктор: "
             << name << ", " << age << ", " << passport << endl;
    }

    void introduce() {
        cout << "[Person] Представление: " << name << ", " << age << " лет, паспорт: " << passport << endl;
    }
};

// КЛАСС - ACCOUNT
class Account {
private:
    int accountNumber;
    double balance;

public:
    Account() : accountNumber(0), balance(0.0) {
        cout << "[Account] Конструктор без параметров: №" << accountNumber << ", баланс " << balance << endl;
    }

    Account(int num, double bal) : accountNumber(num), balance(bal) {
        cout << "[Account] Конструктор с параметрами: №" << accountNumber << ", баланс " << balance << endl;
    }

    Account(const Account& other) : accountNumber(other.accountNumber), balance(other.balance) {
        cout << "[Account] Конструктор копирования: №" << accountNumber << ", баланс " << balance << endl;
    }

    ~Account() {
        cout << "[Account] Деструктор: №" << accountNumber << ", баланс " << balance << endl;
    }

    void show() {
        cout << "[Account] Счёт №" << accountNumber << ", Баланс: " << balance << endl;
    }
};

// КЛАСС - LOAN
class Loan {
private:
    double amount;
    double interestRate;
    bool approved;

public:
    Loan() : amount(0.0), interestRate(0.0), approved(false) {
        cout << "[Loan] Конструктор без параметров: сумма " << amount << ", ставка " << interestRate << "%, одобрен: " << approved << endl;
    }

    Loan(double amt, double rate) : amount(amt), interestRate(rate), approved(false) {
        cout << "[Loan] Конструктор с параметрами: сумма " << amount << ", ставка " << interestRate << "%, одобрен: " << approved << endl;
    }

    ~Loan() {
        cout << "[Loan] Деструктор: сумма " << amount << ", ставка " << interestRate << "%, одобрен: " << approved << endl;
    }

    void approve() {
        approved = true;
        cout << "[Loan] Кредит одобрен!" << endl;
    }

    void show() {
        cout << "[Loan] Кредит: " << amount << ", ставка " << interestRate << "%, одобрен: " << (approved ? "Да" : "Нет") << endl;
    }
};

// КЛАСС - CLIENT PAGE
class ClientPage {
private:
    vector<Account*> accounts;
    vector<Loan*> loans;
    string email;
    string phone;

public:
    ClientPage() : email("no email"), phone("no phone") {
        cout << "[ClientPage] Конструктор без параметров: " << email << ", " << phone << endl;
    }

    ClientPage(string e, string p) : email(e), phone(p) {
        cout << "[ClientPage] Конструктор с параметрами: " << email << ", " << phone << endl;
    }

    ~ClientPage() {
        // Сначала удаляем содержимое
        for (Account* acc : accounts) delete acc;
        for (Loan* ln : loans) delete ln;
        accounts.clear();
        loans.clear();
        cout << "[ClientPage] Деструктор: " << email << ", " << phone << endl;
    }

    void createAccount(int num, double balance) {
        Account* acc = new Account(num, balance);
        accounts.push_back(acc);
    }

    void takeLoan(double amount, double rate) {
        Loan* ln = new Loan(amount, rate);
        loans.push_back(ln);
    }

    void showAll() {
        cout << "[ClientPage] Данные страницы: email=" << email << ", phone=" << phone << endl;
        for (Account* acc : accounts) acc->show();
        for (Loan* ln : loans) ln->show();
    }

    vector<Loan*>& getLoans() { return loans; }
};

// КЛАСС - CLIENT
class Client : public Person {
private:
    int clientID;
    ClientPage page;

public:
    Client() : Person(), clientID(0) {
        cout << "[Client] Конструктор без параметров: ID " << clientID << endl;
    }

    Client(string n, int a, string pass, int id, string email, string phone)
        : Person(n, a, pass), page(email, phone), clientID(id) {
        cout << "[Client] Конструктор с параметрами: ID " << clientID << endl;
    }

    ~Client() {
        cout << "[Client] Деструктор: ID " << clientID << endl;
    }

    void openAccount(int num, double balance) {
        page.createAccount(num, balance);
    }

    void requestLoan(double amount, double rate) {
        page.takeLoan(amount, rate);
    }

    void showInfo() {
        introduce();
        cout << "[Client] ID Клиента: " << clientID << endl;
        page.showAll();
    }

    ClientPage& getPage() { return page; }
};

// КЛАСС - BASE CARD
class BaseCard {
public:
    BaseCard() {
        cout << "[BaseCard] Конструктор без параметров" << endl;
    }
    virtual ~BaseCard() {
        cout << "[BaseCard] Деструктор" << endl;
    }
    virtual void showPrivileges() = 0;
};

// КЛАСС - ASSISTANT CARD
class AssistantCard : public BaseCard {
public:
    AssistantCard() {
        cout << "[AssistantCard] Конструктор без параметров" << endl;
    }

    AssistantCard(const AssistantCard& other) {
        cout << "[AssistantCard] Конструктор копирования" << endl;
    }

    ~AssistantCard() {
        cout << "[AssistantCard] Деструктор" << endl;
    }

    void showPrivileges() override {
        cout << "[AssistantCard] Привилегии: только простой доступ в систему" << endl;
    }
};

// КЛАСС - MANAGER CARD
class ManagerCard : public BaseCard {
private:
    int managerCode;
    string department;

public:
    ManagerCard(int code, string dept) : managerCode(code), department(dept) {
        cout << "[ManagerCard] Конструктор с параметрами: код " << managerCode << ", отдел " << department << endl;
    }

    ~ManagerCard() {
        cout << "[ManagerCard] Деструктор: код " << managerCode << ", отдел " << department << endl;
    }

    void showPrivileges() override {
        cout << "[ManagerCard] Привилегии: полный доступ к системе, можно одобрять кредиты" << endl;
    }

    void approveLoan(Loan* loan) {
        if (loan) {
            loan->approve();
            cout << "[ManagerCard] Кредит одобрен менеджером " << managerCode << endl;
        }
    }
};

// КЛАСС - EMPLOYEE
class Employee : public Person {
private:
    int employeeID;
    double salary;
    BaseCard* card;

public:
    Employee() : Person(), employeeID(0), salary(0.0), card(new AssistantCard()) {
        cout << "[Employee] Конструктор без параметров: ID " << employeeID << ", зарплата " << salary << endl;
    }

    Employee(string n, int a, string pass, int id, double sal)
        : Person(n, a, pass), employeeID(id), salary(sal), card(new AssistantCard()) {
        cout << "[Employee] Конструктор с параметрами: ID " << employeeID << ", зарплата " << salary << endl;
    }

    ~Employee() {
        cout << "[Employee] Деструктор: ID " << employeeID << ", зарплата " << salary << endl;
        delete card;
    }

    void promoteToManager(int code, string dept) {
        cout << "[Employee] Повышение до менеджера..." << endl;
        delete card;
        card = new ManagerCard(code, dept);
        cout << "[Employee] Карта обновлена до ManagerCard" << endl;
    }

    void showInfo() {
        introduce();
        cout << "[Employee] ID: " << employeeID << ", зарплата: " << salary << endl;
        card->showPrivileges();
    }

    BaseCard* getCard() { return card; }
};

// ДЕМОНСТРАЦИЯ

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    cout << "\n=== Создаем клиента ===" << endl;
    Client client1("Иван Сандалов", 22, "8024 595595", 1001, "ivan@mail.com", "+79171112233");
    client1.openAccount(5001, 1000.0);
    client1.openAccount(5002, 500.0);
    client1.requestLoan(30000, 10.0);
    client1.showInfo();

    cout << "\n=== Создаем работника ===" << endl;
    Employee emp1("Сидоров", 42, "345335335", 200, 40000);
    emp1.showInfo();

    cout << "\n=== Повышаем работника ===" << endl;
    emp1.promoteToManager(100, "Operations");
    emp1.showInfo();


    cout << "\n=== Одобрим кредит ===" << endl;

    // Получаем указатель на менеджерскую карту
    ManagerCard* mgrCard = dynamic_cast<ManagerCard*>(emp1.getCard());
    if (mgrCard) {
        // Получаем кредиты клиента
        vector<Loan*>& loans = client1.getPage().getLoans();
        if (!loans.empty()) {
            // Одобряем первый кредит
            mgrCard->approveLoan(loans[0]);
            cout << "Кредит одобрен" << endl;
        } else {
        cout << "У клиента нет запросов на кредит" << endl;
        }
    } else {
        cout << "Сотрудник не является менеджером" << endl;
    }

    // Покажем обновлённую информацию о клиенте
    cout << "\n=== Обновлённая информация о клиенте ===" << endl;
    client1.showInfo();

    cout << "\n=== Демонстрация конструктора копирования ===" << endl;

    // Создаём оригинальный объект
    cout << "--- Создание оригинального объекта ---" << endl;
    AssistantCard original;
    cout << "Оригинальный объект создан, его привилегии: ";
    original.showPrivileges();

    // Создаём копию с помощью конструктора копирования
    cout << "\n--- Создание копии (конструктор копирования) ---" << endl;
    AssistantCard copy(original);
    cout << "Копия создана, её привилегии: ";
    copy.showPrivileges();
}