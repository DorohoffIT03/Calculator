#include <iostream>
#include <Windows.h> // для функцій підтримки українського вводу
#include <stdlib.h> // для команди очищення консолі system("cls")

using namespace std;

// Коректне введення числа
void correctInput(float* px) { 
    while (true)
    {
        cin >> *px;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "\nВи ввели не число. Cпробуйте ще раз: ";
        }
        else
        {
            cin.ignore(32767, '\n');
            break;
        }
    }
}

int main()
{
    SetConsoleCP(1251);       // Підтримка українського алфавіту 
    SetConsoleOutputCP(1251); //

    float a, b; // Операнди калькулятора
    float rezult; // змінна зберігання результату операції

   /* do
    {


    } while (true);*/

    cout << "Введіть перше число: ";
    correctInput(&a);

    cout << "Введіть друге число: ";
    correctInput(&b);

    char symbol; 
    do
    {
        cout << "\nВведіть символ операції (+, -, *, /): ";
        cin >> symbol;
        switch (symbol)
        {
        case '+':
            rezult = a + b;
            break;

        case '-':
            rezult = a - b;
            break;

        case '*':
            rezult = a * b;
            break;

        case '/':
            if (b != 0)
                rezult = a / b;
            else
            {
                cout << "\nПомилка: Ділення на нуль неможливе.\n";
                return 0;
            }
            break;

        default:
            cout << "\nВведення не вірне. Спробуйте ще раз.\n";
            continue;
        }

        break;
    } while (true); 
    
    system("cls");

    cout << "\nОтриманий вираз: " << a << ' ' << symbol << ' ' << b << " = " << rezult;

}