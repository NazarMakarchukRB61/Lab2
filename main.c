#include <stdio.h>  // Директива підключення бібліотеки введення та виведення
#include <math.h>   // Бібліотека математичних функцій

/**
 * @brief Обчислює значення підінтегральної функції (варіант 8).
 *
 * @param x Значення аргументу.
 * @return double Значення f(x) = (1 + sqrt(x)) / x^2.
 */
double integrand_expression(double x);

/**
 * @brief Обчислює інтеграл методом лівих прямокутників.
 *
 * @param a Ліва межа інтегрування.
 * @param b Права межа інтегрування.
 * @param n Кількість проміжків розбиття.
 * @return double Наближене значення інтегралу.
 */
double left_rectangles(double a, double b, unsigned int n);

/**
 * @brief Обчислює інтеграл методом правих прямокутників.
 *
 * @param a Ліва межа інтегрування.
 * @param b Права межа інтегрування.
 * @param n Кількість проміжків розбиття.
 * @return double Наближене значення інтегралу.
 */
double right_rectangles(double a, double b, unsigned int n);

/**
 * @brief Обчислює інтеграл методом трапецій.
 *
 * @param a Ліва межа інтегрування.
 * @param b Права межа інтегрування.
 * @param n Кількість проміжків розбиття.
 * @return double Наближене значення інтегралу.
 */
double trapezoids(double a, double b, unsigned int n);

/**
 * @brief Обчислює інтеграл методом парабол (Сімпсона).
 *
 * Метод працює лише для парної кількості проміжків,
 * тому непарне n збільшується на 1.
 *
 * @param a Ліва межа інтегрування.
 * @param b Права межа інтегрування.
 * @param n Кількість проміжків розбиття.
 * @return double Наближене значення інтегралу.
 */
double simpson(double a, double b, unsigned int n);

/**
 * @brief Обирає метод обчислення інтегралу за його номером.
 *
 * @param method Номер методу (1 - ліві, 2 - праві, 3 - трапеції, 4 - парабол).
 * @param a Ліва межа інтегрування.
 * @param b Права межа інтегрування.
 * @param n Кількість проміжків розбиття.
 * @return double Значення інтегралу або 0.0 для некоректного номера методу.
 */
double calculate_integral(int method, double a, double b, unsigned int n);

/**
 * @brief Головна функція програми.
 *
 * Виводить меню, зчитує номер методу та похибку eps, будує таблицю
 * значень інтегралу всіма методами, після чого збільшує N на 2,
 * доки Delta = |I(N) - I(N+2)| не стане не більшою за eps.
 *
 * @return int 0 у разі успішного виконання, 1 у разі некоректного введення.
 */
int main(void)
{
    double a = 0.5;
    double b = 4.0;
    double eps = 0.0;
    double i1 = 0.0;
    double i2 = 0.0;
    double delta = 0.0;
    int method = 0;
    unsigned int n = 0;
    unsigned int values[] = {10, 100, 1000, 10000};
    unsigned int k = 0;

    printf("Variant 8: f(x) = (1 + sqrt(x)) / x^2\n");
    printf("Interval: [%.1f; %.1f]\n", a, b);
    printf("1 - Left rectangles\n");
    printf("2 - Right rectangles\n");
    printf("3 - Trapezoids\n");
    printf("4 - Simpson\n");
    printf("Choose method: ");
    scanf("%d", &method);

    if (method < 1 || method > 4)
    {
        printf("Incorrect method.\n");
        return 1;
    }
printf("Enter epsilon (0.00001 - 0.001): ");
    scanf("%lf", &eps);

    if (eps < 0.00001 || eps > 0.001)
    {
        printf("Incorrect epsilon.\n");
        return 1;
    }

    printf("\nTable of integral values:\n");
    printf("n\tLeft\t\tRight\t\tTrapezoid\tSimpson\n");

    for (k = 0; k < 4; k++)
    {
        n = values[k];

        printf("%u\t%.8f\t%.8f\t%.8f\t%.8f\n",
               n,
               left_rectangles(a, b, n),
               right_rectangles(a, b, n),
               trapezoids(a, b, n),
               simpson(a, b, n));
    }

    n = 2;

    do
    {
        i1 = calculate_integral(method, a, b, n);
        i2 = calculate_integral(method, a, b, n + 2);
        delta = fabs(i1 - i2);

        if (delta > eps)
            n += 2;

    } while (delta > eps && n < 1000000);

    printf("\nRequired N = %u\n", n);
    printf("I(N) = %.10f\n", i1);
    printf("I(N+2) = %.10f\n", i2);
    printf("Delta = %.10f\n", delta);

    return 0;
}
double integrand_expression(double x)
{
    return (1.0 + sqrt(x)) / (x * x);
}

double left_rectangles(double a, double b, unsigned int n)
{
    double h = (b - a) / n;
    double sum = 0.0;
    unsigned int i;

    for (i = 0; i < n; i++)
        sum += integrand_expression(a + i * h);

    return h * sum;
}

double right_rectangles(double a, double b, unsigned int n)
{
    double h = (b - a) / n;
    double sum = 0.0;
    unsigned int i;

    for (i = 1; i <= n; i++)
        sum += integrand_expression(a + i * h);

    return h * sum;
}

double trapezoids(double a, double b, unsigned int n)
{
    double h = (b - a) / n;
    double sum = (integrand_expression(a) +
                  integrand_expression(b)) / 2.0;
    unsigned int i;

    for (i = 1; i < n; i++)
        sum += integrand_expression(a + i * h);

    return h * sum;
}

double simpson(double a, double b, unsigned int n)
{
    double h, odd = 0.0, even = 0.0;
    unsigned int i;

    if (n % 2 != 0)
        n++;

    h = (b - a) / n;

    for (i = 1; i < n; i++)
    {
        if (i % 2 != 0)
            odd += integrand_expression(a + i * h);
        else
            even += integrand_expression(a + i * h);
    }

    return h / 3.0 *
           (integrand_expression(a) +
            integrand_expression(b) +
            4.0 * odd + 2.0 * even);
}

double calculate_integral(int method, double a, double b, unsigned int n)
{
    switch (method)
    {
        case 1:
            return left_rectangles(a, b, n);
        case 2:
            return right_rectangles(a, b, n);
        case 3:
            return trapezoids(a, b, n);
        case 4:
            return simpson(a, b, n);
        default:
            return 0.0;
    }
}
