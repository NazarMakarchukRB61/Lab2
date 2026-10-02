// Забезпечує функціонал для введення та виведення даних (printf)
#include <stdio.h>
// Стандартна бібліотека загального призначення.
#include <stdlib.h>
// Надає математичні функції та константи.
#include <math.h>
// бібліотека для консольного введення/виведення. використовується для функції getch()
#include <conio.h>

//----Підінтегральна функція----
//----Для кожного варіанту використовується своя формула----
double integrand_expression(double x, int variant)
{
    //----Функція для 8-го варіанту----
    //----f(x) = (1 + sqrt(x)) / x^2----
    if (variant == 8)
        return (1.0 + sqrt(x)) / (x * x);

    //----Функція для 9-го варіанту----
    //----f(x) = x * e^(x^2)----
    else
        return x * exp(x * x);
}


//----Метод лівих прямокутників----
double left_rectangles(double a, double b, unsigned int n, int variant)
{
    //----Обчислюємо ширину одного проміжку----
    double h = (b - a) / (double)n;

    //----Змінна для накопичення суми----
    double sum = 0.0;

    //----Обчислюємо значення функції в лівих точках----
    for (unsigned int i = 0; i < n; i++)
        sum += integrand_expression(a + i * h, variant);

    //----Множимо суму висот на ширину проміжку----
    return sum * h;
}


//----Метод правих прямокутників----
double right_rectangles(double a, double b, unsigned int n, int variant)
{
    //----Обчислюємо ширину одного проміжку----
    double h = (b - a) / (double)n;

    //----Змінна для накопичення суми----
    double sum = 0.0;

    //----Обчислюємо значення функції в правих точках----
    for (unsigned int i = 1; i <= n; i++)
        sum += integrand_expression(a + i * h, variant);

    //----Множимо суму висот на ширину проміжку----
    return sum * h;
}


//----Метод трапецій----
double trapezoids(double a, double b, unsigned int n, int variant)
{
    //----Обчислюємо ширину одного проміжку----
    double h = (b - a) / (double)n;

    //----Змінна для накопичення суми внутрішніх точок----
    double sum = 0.0;

    //----Додаємо значення функції у внутрішніх точках----
    for (unsigned int i = 1; i < n; i++)
        sum += integrand_expression(a + i * h, variant);

    //----Формула методу трапецій----
    //----Кінцеві значення функції додаються окремо----
    return (h / 2.0) *
           (integrand_expression(a, variant) +
            integrand_expression(b, variant) +
            2.0 * sum);
}


//----Метод парабол (метод Сімпсона)----
double simpson(double a, double b, unsigned int n, int variant)
{
    //----Для методу Сімпсона кількість проміжків повинна бути парною----
    if (n % 2 != 0)
        n++;

    //----Обчислюємо ширину одного проміжку----
    double h = (b - a) / (double)n;

    //----Суми для непарних і парних точок----
    double odd = 0.0;
    double even = 0.0;

    //----Обчислюємо суму значень у непарних точках----
    for (unsigned int i = 1; i < n; i += 2)
        odd += integrand_expression(a + i * h, variant);

    //----Обчислюємо суму значень у парних точках----
    for (unsigned int i = 2; i < n; i += 2)
        even += integrand_expression(a + i * h, variant);

    //----Формула методу Сімпсона----
    return (h / 3.0) *
           (integrand_expression(a, variant) +
            integrand_expression(b, variant) +
            4.0 * odd +
            2.0 * even);
}


//----Головна функція програми----
int main()
{
    //----Оголошення змінних----
    double a, b, eps;
    double I1, I2, delta;

    unsigned int n;
    int variant, method;


    //----Вибір варіанту----
    do
    {
        printf("\nEnter variant (8 or 9): ");
        scanf("%d", &variant);

    } while (variant != 8 && variant != 9);


    //----Встановлення меж інтегрування----
    //----Для 8-го варіанту: [0.5; 4]----
    //----Для 9-го варіанту: [1; 2]----
    if (variant == 8)
    {
        a = 0.5;
        b = 4.0;
    }
    else
    {
        a = 1.0;
        b = 2.0;
    }


    //----Виведення меж інтегрування----
    printf("\nIntegration interval: [%.2lf; %.2lf]\n", a, b);


    //----Введення кількості проміжків N----
    do
    {
        printf("\nEnter number of intervals (N > 0): ");
        scanf("%u", &n);

    } while (n == 0);


    //----Введення допустимої похибки----
    do
    {
        printf("\nEnter measurement error: ");
        scanf("%lf", &eps);

    } while (eps <= 0);


    //----Вибір методу обчислення інтеграла----
    do
    {
        printf("\nChoose the method:\n");
        printf("\t1. Left rectangles\n");
        printf("\t2. Right rectangles\n");
        printf("\t3. Trapezoids\n");
        printf("\t4. Simpson\n");
        printf("(1-4): ");

        scanf("%d", &method);

    } while (method < 1 || method > 4);


    //----Вказівник на обраний метод----
    //----Дозволяє використовувати один алгоритм пошуку N----
    //----для будь-якого з чотирьох методів----
    double (*calc_method)(double, double, unsigned int, int) = NULL;


    //----Визначаємо обраний метод----
    switch (method)
    {
        case 1:
            printf("\n*Left rectangles method*\n");
            calc_method = left_rectangles;
            break;

        case 2:
            printf("\n*Right rectangles method*\n");
            calc_method = right_rectangles;
            break;

        case 3:
            printf("\n*Trapezoids method*\n");
            calc_method = trapezoids;
            break;

        case 4:
            printf("\n*Simpson method*\n");
            calc_method = simpson;
            break;
    }


    //----Підбір N за заданою точністю----
    //----Порівнюємо I(N) та I(N+2)----
    //----Умова зупинки: |I(N) - I(N+2)| <= eps----
    do
    {
        //----Обчислюємо інтеграл для поточного N----
        I1 = calc_method(a, b, n, variant);

        //----Обчислюємо інтеграл для N+2----
        I2 = calc_method(a, b, n + 2, variant);

        //----Знаходимо різницю між двома результатами----
        delta = fabs(I1 - I2);

        //----Якщо точність недостатня, збільшуємо N на 2----
        if (delta > eps)
            n += 2;

    } while (delta > eps && n < 500000);


    //----Виведення підсумкового результату----
    printf("\n\ta = %.2lf", a);
    printf("\n\tb = %.2lf", b);
    printf("\n\tIntegral = %.8lf", I2);
    printf("\n\tN = %u", n);
    printf("\n\tDelta = %.8lf", delta);


    //----Очікуємо натискання клавіші----
    printf("\n\nPress any key to finish the program.");
    getch();

    return 0;
}
