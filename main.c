#include <stdio.h>
#include <math.h>

/**
 * @brief Обчислює значення підінтегральної функції (варіант 8).
 *
 * double (тип значення, що повертається) — базовий тип даних для зберігання
 * дійсних чисел (чисел із плаваючою комою) подвійної точності.
 *
 * @param x Значення аргументу. Тип double — дійсне число подвійної точності.
 * @return double Значення f(x) = (1 + sqrt(x)) / x^2.
 */
double integrand_expression(double x);

/**
 * @brief Обчислює інтеграл методом лівих прямокутників.
 *
 * double (тип значення, що повертається) — базовий тип даних для зберігання
 * дійсних чисел (чисел із плаваючою комою) подвійної точності.
 * unsigned int — беззнаковий цілий тип, що зберігає лише невід'ємні
 * цілі числа (кількість проміжків не може бути від'ємною).
 *
 * @param a Ліва межа інтегрування. Тип double — дійсне число.
 * @param b Права межа інтегрування. Тип double — дійсне число.
 * @param n Кількість проміжків розбиття. Тип unsigned int — ціле без знака.
 * @return double Наближене значення інтегралу.
 */
double left_rectangles(double a, double b, unsigned int n);

/**
 * @brief Обчислює інтеграл методом правих прямокутників.
 *
 * double (тип значення, що повертається) — базовий тип даних для зберігання
 * дійсних чисел (чисел із плаваючою комою) подвійної точності.
 * unsigned int — беззнаковий цілий тип, що зберігає лише невід'ємні
 * цілі числа.
 *
 * @param a Ліва межа інтегрування. Тип double — дійсне число.
 * @param b Права межа інтегрування. Тип double — дійсне число.
 * @param n Кількість проміжків розбиття. Тип unsigned int — ціле без знака.
 * @return double Наближене значення інтегралу.
 */
double right_rectangles(double a, double b, unsigned int n);

/**
 * @brief Обчислює інтеграл методом трапецій.
 *
 * double (тип значення, що повертається) — базовий тип даних для зберігання
 * дійсних чисел (чисел із плаваючою комою) подвійної точності.
 * unsigned int — беззнаковий цілий тип, що зберігає лише невід'ємні
 * цілі числа.
 *
 * @param a Ліва межа інтегрування. Тип double — дійсне число.
 * @param b Права межа інтегрування. Тип double — дійсне число.
 * @param n Кількість проміжків розбиття. Тип unsigned int — ціле без знака.
 * @return double Наближене значення інтегралу.
 */
double trapezoids(double a, double b, unsigned int n);

/**
 * @brief Обчислює інтеграл методом парабол (Сімпсона).
 *
 * Метод працює лише для парної кількості проміжків,
 * тому непарне n збільшується на 1.
 *
 * double (тип значення, що повертається) — базовий тип даних для зберігання
 * дійсних чисел (чисел із плаваючою комою) подвійної точності.
 * unsigned int — беззнаковий цілий тип, що зберігає лише невід'ємні
 * цілі числа.
 *
 * @param a Ліва межа інтегрування. Тип double — дійсне число.
 * @param b Права межа інтегрування. Тип double — дійсне число.
 * @param n Кількість проміжків розбиття. Тип unsigned int — ціле без знака.
 * @return double Наближене значення інтегралу.
 */
double simpson(double a, double b, unsigned int n);

/**
 * @brief Обирає метод обчислення інтегралу за його номером.
 *
 * double (тип значення, що повертається) — базовий тип даних для зберігання
 * дійсних чисел (чисел із плаваючою комою) подвійної точності.
 * int — базовий тип даних для зберігання цілих чисел зі знаком.
 * unsigned int — беззнаковий цілий тип, що зберігає лише невід'ємні
 * цілі числа.
 *
 * @param method Номер методу (1 - ліві, 2 - праві, 3 - трапеції, 4 - парабол).
 *               Тип int — ціле число зі знаком.
 * @param a Ліва межа інтегрування. Тип double — дійсне число.
 * @param b Права межа інтегрування. Тип double — дійсне число.
 * @param n Кількість проміжків розбиття. Тип unsigned int — ціле без знака.
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
 * int (тип значення, що повертається) — базовий тип даних для зберігання
 * цілих чисел зі знаком. Тут використовується як код завершення програми.
 *
 * @return int 0 у разі успішного виконання, 1 у разі некоректного введення.
 */
int main()
{
    /**
     * @brief Ліва межа інтегрування.
     *
     * double — базовий тип даних для зберігання дійсних чисел
     * (чисел із плаваючою комою) подвійної точності.
     */
    double a = 0.5;

    /**
     * @brief Права межа інтегрування.
     *
     * double — дійсне число подвійної точності.
     */
    double b = 4.0;

    /**
     * @brief Задана похибка обчислень (0.00001 <= eps <= 0.001).
     *
     * double — дійсне число подвійної точності.
     */
    double eps = 0.0;

    /**
     * @brief Значення інтегралу при N проміжках (I1).
     *
     * double — дійсне число подвійної точності.
     */
    double i1 = 0.0;

    /**
     * @brief Значення інтегралу при N+2 проміжках (I2).
     *
     * double — дійсне число подвійної точності.
     */
    double i2 = 0.0;

    /**
     * @brief Модуль різниці |I1 - I2|.
     *
     * double — дійсне число подвійної точності.
     */
    double delta = 0.0;

    /**
     * @brief Номер обраного методу обчислення (1-4).
     *
     * int — базовий тип даних для зберігання цілих чисел зі знаком.
     */
    int method = 0;

    /**
     * @brief Поточна кількість проміжків розбиття.
     *
     * unsigned int — беззнаковий цілий тип, що зберігає лише невід'ємні
     * цілі числа (кількість проміжків не може бути від'ємною).
     */
    unsigned int n = 0;

    /**
     * @brief Масив кількостей проміжків для таблиці результатів.
     *
     * unsigned int values[] — масив беззнакових цілих чисел.
     * Розмір масиву визначається за кількістю елементів у фігурних дужках.
     */
    unsigned int values[] = {10, 100, 1000, 10000};

    /**
     * @brief Лічильник циклу for.
     *
     * unsigned int — беззнаковий цілий тип, індекс елемента масиву values.
     */
    unsigned int k = 0;

        /**
     * printf — функція виведення форматованого тексту в консоль.
     * Специфікатор %.1f виводить дійсне число з одним знаком після коми.
     */
    printf("Variant 8: f(x) = (1 + sqrt(x)) / x^2\n");
    printf("Interval: [%.1f; %.1f]\n", a, b);
    printf("1 - Left rectangles\n");
    printf("2 - Right rectangles\n");
    printf("3 - Trapezoids\n");
    printf("4 - Simpson\n");
    printf("Choose method: ");
        /**
     * scanf — функція зчитування даних з клавіатури.
     * Специфікатор %d — ціле число зі знаком, &method — адреса змінної,
     * куди записується введене значення.
     */
    scanf("%d", &method);

        /**
     * if — оператор розгалуження. Якщо номер методу поза межами 1-4,
     * виводимо повідомлення і завершуємо програму з кодом помилки 1.
     * Оператор || — логічне «АБО».
     */
    if (method < 1 || method > 4)
    {
        printf("Incorrect method.\n");
        return 1;
    }
printf("Enter epsilon (0.00001 - 0.001): ");

        /**
     * Специфікатор %lf — дійсне число типу double.
     */
    scanf("%lf", &eps);

        /**
     * Перевірка того, що похибка лежить у допустимих межах.
     */
    if (eps < 0.00001 || eps > 0.001)
    {
        printf("Incorrect epsilon.\n");
        return 1;
    }

        /**
     * Виведення таблиці результатів. Символ \t — табуляція,
     * \n — перехід на новий рядок. Специфікатор %u — unsigned int,
     * %.8f — дійсне число з вісьмома знаками після коми.
     */
    printf("\nTable of integral values:\n");
    printf("n\tLeft\t\tRight\t\tTrapezoid\tSimpson\n");

        /**
     * for — цикл із лічильником: перебирає всі елементи масиву values
     * і для кожної кількості проміжків n обчислює інтеграл усіма методами.
     */
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

    /**
     * Підбір N за заданою похибкою для обраного методу.
     * Починаємо з двох проміжків.
     */
    n = 2;

    /**
     * do-while — цикл із післяумовою: тіло виконується щонайменше раз.
     * На кожному кроці обчислюємо I1 (для N) та I2 (для N+2),
     * знаходимо Delta = |I1 - I2| (fabs — модуль дійсного числа)
     * і збільшуємо N на 2, доки Delta не потрапить у межі eps.
     * Умова n < 1000000 захищає від нескінченного циклу.
     * Оператор && — логічне «І».
     */
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

/**
     * return 0 — повідомляємо операційній системі про успішне завершення.
     */
    return 0;
}

/**
 * @brief Реалізація підінтегральної функції f(x) = (1 + sqrt(x)) / x^2.
 */
double integrand_expression(double x)
{
    return (1.0 + sqrt(x)) / (x * x);
}

/**
 * @brief Реалізація методу лівих прямокутників.
 */
double left_rectangles(double a, double b, unsigned int n)
{
    double h = (b - a) / n;
    double sum = 0.0;
    unsigned int i;

    for (i = 0; i < n; i++)
        sum += integrand_expression(a + i * h);

    return h * sum;
}

/**
 * @brief Реалізація методу правих прямокутників.
 */
double right_rectangles(double a, double b, unsigned int n)
{
    double h = (b - a) / n;
    double sum = 0.0;
    unsigned int i;

    for (i = 1; i <= n; i++)
        sum += integrand_expression(a + i * h);

    return h * sum;
}

/**
 * @brief Реалізація методу трапецій.
 */
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

/**
 * @brief Реалізація методу парабол (Сімпсона).
 *
 * odd — сума значень у вузлах з непарними номерами (коефіцієнт 4),
 * even — сума значень у вузлах з парними номерами (коефіцієнт 2).
 */
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

/**
 * @brief Реалізація вибору методу обчислення за номером через switch.
 */
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
