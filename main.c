#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//-----Окрема власна функція для розрахунку значення y в залежності від x
double calculate_y(double x) {
    double y;

    if (x >= -0.5 && x < 1.5) {
        y = pow(x - 1.0, 3);
    }
    else if (x >= 1.5 && x < 5.125) {
        y = (x) - 2.0;
        //----Реалізує  логічне віднімання x
    }
    else if (x >= 5.125 && x < 9.5) {
        y = 1.0 / (x + 10.0);
    }
    else {
        y = pow(x, 2) - 1.0;
    }

    return y;
}
//---Оглошення змінних
int main() {
    double x, y;
//----Введення даних
    printf("Enter x: ");
    if (scanf("%lf", &x) != 1) {
        return 1;
    }

    //-----Виклик функції
    y = calculate_y(x);

    //-----Очищення консолі та виведення результату
    system("cls");

    printf("x = %lf\n", x);
    printf("y = %lf\n", y);

    return 0;
}
