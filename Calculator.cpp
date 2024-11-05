#include <iostream>
#include <stack>
#include <Windows.h> // для функцій підтримки українського вводу
#include <stdlib.h> // для команди очищення консолі system("cls")

const double Pi = acos(-1);

using namespace std;

struct Leksema { // структура опису числа або операції для додавання до стеку
    char type; // для запису операції
    double value; // для запису числа
};

double Sin(double x) {
    return round(sin(x)*10000000)/ 10000000;
}

double Cos(double x) {
    return round(cos(x) * 10000000) / 10000000;
}

double ctg(double x) {
    return Cos(x) / Sin(x);
}

bool Maths(stack <Leksema> & numbers, stack <Leksema> & operations, Leksema& item) { // функція в якій відбувається розрахунок
    double a, b, rezult;
    a = numbers.top().value; // беремо верхнє число зі стеку чисел
    numbers.pop(); // видаляємо верхнє число зі стеку чисел 
    switch (operations.top().type) // перевіряємо тип верхньої операції зі стеку операцій
    {
        case '+':
            b = numbers.top().value; // беремо наступне число зі стеку чисел
            numbers.pop(); // видаляємо число зі стеку чисел 
            rezult = a + b; // проводимо розрахунок
            item.type = '0';        // заносимо дані до змінної
            item.value = rezult;    //
            numbers.push(item); // додаємо результат операції до стеку чисел
            operations.pop(); // видаляємо верхню операцію зі стеку операцій
            break;

        case '-':
            b = numbers.top().value;
            numbers.pop();
            rezult = b - a; // міняємо операнди місцями
            item.type = '0';
            item.value = rezult;
            numbers.push(item);
            operations.pop();
            break;

        case '*':
            b = numbers.top().value;
            numbers.pop();
            rezult = a * b;
            item.type = '0';
            item.value = rezult;
            numbers.push(item);
            operations.pop();
            break;

        case '^':
            b = numbers.top().value;
            numbers.pop();
            rezult = pow(b, a);
            item.type = '0';
            item.value = rezult;
            numbers.push(item);
            operations.pop();
            break;

        case '/':
            if (a == 0) {
                cerr << "Помилка: Ділення на нуль\n"; // повідомляємо користувача про помилку /0
                return false;
            }
            else {
                b = numbers.top().value;
                numbers.pop();
                rezult = b / a; // міняємо операнди місцями
                item.type = '0';
                item.value = rezult;
                numbers.push(item);
                operations.pop();
                break;
            }

        case 's':
            rezult = Sin(a);
            item.type = '0';
            item.value = rezult;
            numbers.push(item);
            operations.pop();
            break;

        case 'c':
            rezult = Cos(a);
            item.type = '0';
            item.value = rezult;
            numbers.push(item);
            operations.pop();
            break;

        case 't':
            if (Cos(a) == 0) {
                cerr << "\nНевірний агрумент для тангенса!\n";
                return false;
            }
            rezult = tan(a);
            item.type = '0';
            item.value = rezult;
            numbers.push(item);
            operations.pop();
            break;
             
        case 'g':
            if (Sin(a) == 0) {
                cerr << "\nНевірний аргумент для котангенса\n";
                return false; 
            }
            rezult = ctg(a);
            item.type = '0';
            item.value = rezult;
            numbers.push(item);
            operations.pop();
            break;

        case 'e':
            rezult = exp(a);
            item.type = '0';
            item.value = rezult;
            numbers.push(item);
            operations.pop();
            break;

        default:
            cerr << "Невідома помилка\n";
            return false;
    }

    return true;
}

int getRang(char ch) {
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '^') return 3;
    if (ch == 'c' || ch == 's' || ch == 't' || ch == 'g' || ch == 'e') return 4;
    return 0;
}

int main()
{
    SetConsoleCP(1251);       // Підтримка українського алфавіту 
    SetConsoleOutputCP(1251); //

    cout << "Для використання числа Пі введіть 'p'\n"
        << "Для використання числа Е введіть 'exp(1)'\n"
        << "Для використання тригонометричних функцій вводьте 'sin', 'cos', 'tan', 'ctg'\n"
        << "Для піднесення до степення використовуйте символ '^'\n";
    cout << "Введіть вираз для обчислення: ";

    char ch; // змінна для зчитування поточного символу
    double value;
    bool flag = 1;
    stack <Leksema> numbers; // стек чисел
    stack <Leksema> operations; // стек операцій
    Leksema item;

    do // в циклі розділяємо введений користувачем рядок на числа та операції 
    {
        ch = cin.peek(); // дивимось що ввів користувач посимвольно

        if (ch == '\n') break; // закінчуємо цикл, якщо продивились весь рядок
        
        if (ch == ' ') { // якщо зчитано пробіл - йдемо далі
            cin.ignore();
            continue;
        }

        if (ch == 's' || ch == 'c' || ch == 't' || ch == 'e') {
            char func[3];

            for (int i = 0; i < 3; i++) {
                func[i] = cin.peek();
                cin.ignore();
            }

            if (func[0] == 's' && func[1] == 'i' && func[2] == 'n') {
                item.type = 's';
                item.value = 0;
                operations.push(item); // додаємо операцію до стеку операцій
                continue;
            }

            if (func[0] == 'c' && func[1] == 'o' && func[2] == 's') {
                item.type = 'c';
                item.value = 0;
                operations.push(item); // додаємо операцію до стеку операцій
                continue;
            }

            if (func[0] == 't' && func[1] == 'a' && func[2] == 'n') {
                item.type = 't';
                item.value = 0;
                operations.push(item); // додаємо операцію до стеку операцій
                continue;
            }

            if (func[0] == 'c' && func[1] == 't' && func[2] == 'g') {
                item.type = 'g';
                item.value = 0;
                operations.push(item); // додаємо операцію до стеку операцій
                continue;
            }

            if (func[0] == 'e' && func[1] == 'x' && func[2] == 'p') {
                item.type = 'e';
                item.value = 0;
                operations.push(item); // додаємо операцію до стеку операцій
                continue;
            }
        }

        if (ch >= '0' && ch <= '9' || ( ch == '-' && flag == 1)) { // якщо зчитано цифру
            item.type = '0';        // заносимо дані до змінної
            cin >> item.value;      // *використовуємо cin для зчитування всього числа*
            numbers.push(item); // додаємо число до стеку чисел
            flag = 0;
            continue;
        }

        if (ch >= 'p') { // якщо зчитано число Пі
            item.type = '0';
            item.value = Pi;
            numbers.push(item);
            flag = 0;
            cin.ignore();
            continue;
        }

        if (ch == '+' || (ch == '-' && flag == 0)|| ch == '*' || ch == '/' || ch == '^') { // якщо зчитано операцію
            if (operations.size() == 0) {
                item.type = ch;
                item.value = 0;
                operations.push(item); // додаємо операцію до стеку операцій
                cin.ignore();
                continue;
            }

            if (operations.size() != 0 && getRang(ch) > getRang(operations.top().type)) { // якщо ранг поточної операції більший ніж ранг верхньої операції в стеці - просто додаємо операцію до стеку
                item.type = ch;
                item.value = 0;
                operations.push(item); // додаємо операцію до стеку операцій
                cin.ignore();
                continue;
            }

            if (operations.size() != 0 && getRang(ch) <= getRang(operations.top().type)) { // якщо ранг поточної операції менший або такий ж ніж ранг верхньої операції в стеці - проводимо обчислення
                if (!Maths(numbers, operations, item)) { // перевіряємо статус розрахунку, ставимо додаток на паузу якщо він хибний
                    system("pause");
                    return 0;
                }
                continue;
            }
        }

        if (ch == '(') { // якщо вираз має дужки - додаємо до стеку операцій
            item.type = ch;
            item.value = 0;
            operations.push(item); // додаємо операцію до стеку операцій
            cin.ignore();
            continue;
        }

        if (ch == ')') { // якщо дужки закінчились - проводимо розрахунки в них
            while (operations.top().type != '(')
            {
                if (!Maths(numbers, operations, item)) { // перевіряємо статус розрахунку, ставимо додаток на паузу якщо він хибний
                    system("pause");
                    return 0;
                }
                else continue;
            }
            operations.pop();
            cin.ignore();
            continue;
        }
        else
        {
            cout << "\nВираз введено не вірно\n";
            system("pause");
            return 0;
        }

    } while (true);

    while (operations.size() != 0) {
        if (!Maths(numbers, operations, item)) { // перевіряємо статус розрахунку, ставимо додаток на паузу якщо він хибний
            system("pause");
            return 0;
        }
        else continue;
    }

    cout << "Відповідь: " << numbers.top().value; // якщо помилок не виявлено виводимо результат
   
}