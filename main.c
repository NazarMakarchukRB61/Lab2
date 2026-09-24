#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//-----Функція для розрахунку y
    if (variant == 8) {
        //----Варіант 8
        if (x >= -100 && x < -50) {
            y = -x;
        }
        else if (x >= 50 && x < 100) {
            y = x;
        }
        else if (x >= 200 && x < 1000) {
            y = log10(x) + 1;
        }
        else {
            y = 0;
        }
    }
    else if (variant == 9) {
        //----Варіант 9
        if (x >= 0.5 && x < 1.5) {
            y = 2 / x - 1;
        }
        else if (x >= 1.5 && x < 5.125) {
            y = x - 2;
        }
        else if (x >= 5.125 && x < 9.5) {
            y = sqrt(x + 1) / sqrt(x * x - 10) - pow(x, 3);
        }
        else {
            y = 1;
        }
    }
    else {
        printf("Unknown variant!\n");
        y = 0.0;
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
    y = calculate_y(x, variant);

    //-----Виведення результату
    system("cls");

    printf("Variant = %d\n", variant);
    printf("x = %lf\n", x);
    printf("y = %lf\n", y);

    return 0;
}
