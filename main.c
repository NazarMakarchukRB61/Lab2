#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//-----Функція для розрахунку y
double calculate_y(double x) {
    double y;

    if (x >= -0.5 && x < 1.5) {
        y = pow(x - 1.0, 3);
    }
    else if (x >= 1.5 && x < 5.125) {
        y = (x) - 2.0;
    }
    else if (x >= 5.125 && x < 9.5) {
        y = 1.0 / (x + 10.0);
    }
    else {
        y = pow(x, 2) - 1.0;
    }

    return y;
}
//---Оголошення змінних
int main() {
    double x, y;
//----Введення x
    printf("Enter x: ");
    if (scanf("%lf", &x) != 1) {
        return 1;
    }

    //-----Розрахунок y
    y = calculate_y(x);

    //-----Виведення результату
    system("cls");

    printf("x = %lf\n", x);
    printf("y = %lf\n", y);

    return 0;
}
