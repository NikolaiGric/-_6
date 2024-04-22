#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Drink {
public:
    string name;
    int volume;

    Drink(string n, int v) : name(n), volume(v) {} // Происходит инициализация переменных как n и v это базовый синтаксис
};

class AlcoholicDrink : public Drink {
public:
    int alcoholContent;
    string color;
    string type;
    string taste;
    string origin;

    AlcoholicDrink(string n, int v, int ac, string c, string t, string o, string ta)
        : Drink(n, v), alcoholContent(ac), color(c), type(t), taste(ta), origin(o) {}
};

class NonAlcoholicDrink : public Drink {
public:
    string taste;
    int sugarContent;
    string color;
    string type;
    bool carbonated;
    string consistency;

    NonAlcoholicDrink(string n, int v, string t, int sc, string c, bool ga, string co)
        : Drink(n, v), taste(t), sugarContent(sc), color(c), carbonated(ga), consistency(co) {}
};

class HotDrink : public Drink {
public:
    string aroma;
    int temperature;
    string taste;
    string composition;

    HotDrink(string n, int v, string a, int temp, string t, string c)
        : Drink(n, v), aroma(a), temperature(temp), taste(t), composition(c) {}
};

class Bar {
private:
    vector<Drink*> drinks;

public:
    void addDrink(Drink* d) {
        drinks.push_back(d);
    }

    void removeDrink(int index) {
        drinks.erase(drinks.begin() + index);
    }

    void editDrink(int index, Drink* newDrink) {
        drinks[index] = newDrink;
    }

    void viewDrinks() {
        for (int i = 0; i < drinks.size(); i++) {
            cout << i + 1 << ". " << drinks[i]->name << ", " << drinks[i]->volume << " мл" << endl;
        }
    }

    int placeOrder() {
        int orderTotal = 0;
        cout << "Введите номер напитка, который хотите заказать (0 для завершения заказа): ";
        int choice;
        while (true) {
            cin >> choice;
            if (choice == 0) {
                break;
            }
            if (choice > 0 && choice <= drinks.size()) {
                orderTotal += drinks[choice - 1]->volume;
                cout << "Напиток добавлен в заказ. Общая стоимость заказа: " << orderTotal << " $" << endl;
            }
            else {
                cout << "Неверный номер напитка. Попробуйте еще раз." << endl;
            }
            cout << "Введите номер напитка, который хотите заказать (0 для завершения заказа): ";
        }
        return orderTotal;
    }

    int calculateCost(int orderTotal) {
        return orderTotal;
    }

    void receivePayment(int cost) {
        int payment;
        cout << "Введите сумму платежа: ";
        cin >> payment;
        if (payment >= cost) {
            int change = payment - cost;
            cout << "Сдача: " << change << " Рублей)" << endl;
        }
        else {
            cout << "Недостаточно средств. Попробуйте еще раз." << endl;
            receivePayment(cost);
        }
    }
};

int main() {
    setlocale(LC_ALL, "Rus");
    Bar bar;

    bar.addDrink(new AlcoholicDrink("Водка", 500, 40, "Белый", "Водка", "Классический", "Россия"));
    bar.addDrink(new NonAlcoholicDrink("Кола", 330, "Сладкий", 110, "Коричневый", true, "Газированная"));
    bar.addDrink(new HotDrink("Кофе", 200, "Ароматный", 85, "Горький", "Кофеин, вода"));

    while (true) {
        cout << "Выберите действие:\n"
            << "1. Просмотр напитков\n"
            << "2. Заказ напитков\n"
            << "3. Выход\n"
            << "Ваш выбор: ";

        int choice;
        cin >> choice;


        if (choice == 1) {
            bar.viewDrinks();
        }
        else if (choice == 2) {
            int orderTotal = bar.placeOrder();
            if (orderTotal > 0) {
                int cost = bar.calculateCost(orderTotal);
                bar.receivePayment(cost);
            }
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Неверный выбор. Попробуйте еще раз." << endl;
        }
    }

    return 0;
}