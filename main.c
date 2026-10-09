#include <stdio.h>  // Директива підключення бібліотеки введення та виведення
#include <math.h>   // Бібліотека математичних функцій

double integrand_expression(double x)
{
    return (1.0 + sqrt(x)) / (x * x);
}

double left_rectangles(double a, double b, unsigned int n)
{
    double h = (b - a) / n, sum = 0.0;
    unsigned int i;

    for (i = 0; i < n; i++)
        sum += integrand_expression(a + i * h);

    return h * sum;
}

double right_rectangles(double a, double b, unsigned int n)
{
    double h = (b - a) / n, sum = 0.0;
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

int main(void)
{
    double a = 0.5, b = 4.0, eps, i1, i2, delta;

    // Вказівник на функцію:
    // double — тип значення, яке повертає функція
    // *calc_method — оголошення вказівника
    // (double, double, unsigned int) — типи параметрів
    // NULL — спеціальне значення нульового вказівника
    double (*calc_method)(double, double, unsigned int) = NULL;

    unsigned int n, N;
    unsigned int values[] = {10, 100, 1000, 10000};
    unsigned int k;
    int method;

    printf("Variant 8: f(x) = (1 + sqrt(x)) / x^2\n");
    printf("Interval: [%.1f; %.1f]\n", a, b);
    printf("1 - Left rectangles\n");
    printf("2 - Right rectangles\n");
    printf("3 - Trapezoids\n");
    printf("4 - Simpson\n");
    printf("Choose method: ");
    scanf("%d", &method);

    // switch — оператор вибору одного з варіантів
    // case — позначення конкретного варіанта
    // break — завершення поточної гілки switch
    switch (method)
    {
        case 1:
            calc_method = left_rectangles;
            break;
        case 2:
            calc_method = right_rectangles;
            break;
        case 3:
            calc_method = trapezoids;
            break;
        case 4:
            calc_method = simpson;
            break;
        default:
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

    // Виклик функції через вказівник
    // calc_method(...) — виклик функції, адресу якої збережено
    n = 2;

    do
    {
        i1 = calc_method(a, b, n);
        i2 = calc_method(a, b, n + 2);
        delta = fabs(i1 - i2);

        if (delta > eps)
            n += 2;

    } while (delta > eps && n < 1000000);

    N = n;

    printf("\nRequired N = %u\n", N);
    printf("I(N) = %.10f\n", i1);
    printf("I(N+2) = %.10f\n", i2);
    printf("Delta = %.10f\n", delta);

    return 0;
}
