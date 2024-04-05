#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;

public:
    BankAccount(int accNum, double initialBalance) {
        this->accountNumber = accNum;
        if (initialBalance < 0) {
            throw invalid_argument("Начальный баланс не может быть отрицательным.");
        }
        this->balance = initialBalance;
        this->interestRate = 0;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Некорректная сумма внесения.");
        }
        balance += amount;
        cout << "Средства успешно внесены. Остаток на счете: " << balance << endl;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Некорректная сумма снятия.");
        }
        if (balance < amount) {
            throw invalid_argument("Недостаточно средств для снятия.");
        }
        balance -= amount;
        cout << "Средства успешно сняты. Остаток на счете: " << balance << endl;
    }

    double getBalance() {
        return balance;
    }

    double getInterest() {
        return balance * interestRate * (1.0 / 12.0);
    }

    void setInterestRate(double rate) {
        interestRate = rate;
    }

    double getInterestRate() {
        return interestRate;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    friend bool transfer(BankAccount& from, BankAccount& to, double amount);
};

bool transfer(BankAccount& from, BankAccount& to, double amount) {
    if (amount <= 0) {
        throw invalid_argument("Некорректная сумма перевода.");
    }

    if (&from == &to) {
        throw invalid_argument("Невозможно выполнить перевод на тот же счет.");
    }

    if (from.getBalance() >= amount) {
        from.withdraw(amount);
        to.deposit(amount);
        cout << "Перевод успешно выполнен." << endl;
        return true;
    }
    else {
        cout << "Недостаточно средств." << endl;
        return false;
    }
}




int main() {
    SetConsoleCP(65001);
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(65001);
    try {
        BankAccount User(1, 0);
        BankAccount User2(2, 0);

        int choice;
        double amount;
        int recipientAccountNumber;
        bool success;

        while (true) {
            cout << "Выберите действие:\n1. Пополнить счет\n2. Снять деньги\n3. Изменить процентную ставку\n4. Перевод\n5. Посмотреть баланс\n6. Получить номер банковского счёта\n7. Выйти\n";

            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Введите сумму для пополнения: ";
                cin >> amount;
                try {
                    User.deposit(amount);
                }
                catch (const invalid_argument& e) {
                    cerr << e.what() << endl;
                }
                break;
            case 2:
                cout << "Введите сумму для снятия: ";
                cin >> amount;
                try {
                    User.withdraw(amount);
                }
                catch (const invalid_argument& e) {
                    cerr << e.what() << endl;
                }
                break;
            case 3:
                cout << "Введите новую процентную ставку: ";
                cin >> amount;
                User.setInterestRate(amount);
                break;
            case 4:
                cout << "Введите сумму для перевода: ";
                cin >> amount;
                cout << "Введите номер счета получателя: ";
                cin >> recipientAccountNumber;
                try {
                    transfer(User, User2, amount);
                }
                catch (const invalid_argument& e) {
                    cerr << e.what() << endl;
                }
                break;
            case 5:
                cout << "Баланс на счете: " << User.getBalance() << endl;
                break;
            case 6:
                cout << "Номер банковского счета: " << User.getAccountNumber() << endl;
                break;
            case 7:
                return 0; 
            default:
                cout << "Ошибка. Введите корректный вариант" << endl;
                break;
            }
        }
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }
    return 0;
};
