/* Copyright 2018, Sergey Popov (me@sergobot.me) */

#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_CTYPE, "Russian");
    printf("Добро пожаловать в 5.3! Введите число до 99:\n");
    int n, a, b;
    if (scanf("%d", &n) != 1)
    {
        printf("Ошибка ввода.");
        return 1;
    }
    else if (n < 1 || n > 99)
    {
        printf("Число не попадает в оговоренные рамки.");
        return 1;
    }
    a = n / 10;
    b = n % 10;
    if (a == 1)
    {
        switch (b)
        {
        case 0: printf("Десять");       break;
        case 1: printf("Одиннадцать");  break;
        case 2: printf("Двенадцать");   break;
        case 3: printf("Тринадцать");   break;
        case 4: printf("Четырнадцать"); break;
        case 5: printf("Пятнадцать");   break;
        case 6: printf("Шестнадцать");  break;
        case 7: printf("Семнадцать");   break;
        case 8: printf("Восемнадцать"); break;
        case 9: printf("Девятнадцать"); break;
        }
        printf(" рублей");
    }
    else
    {
        switch (a)
        {
        case 0: break;
        case 2: printf("Двадцать ");    break;
        case 3: printf("Тридцать ");    break;
        case 4: printf("Сорок ");       break;
        case 5: printf("Пятьдесят ");   break;
        case 6: printf("Шестьдесят ");  break;
        case 7: printf("Семьдесят ");   break;
        case 8: printf("Восемьдесят "); break;
        case 9: printf("Девяносто ");   break;
        }

        switch (b)
        {
        case 0: printf("рублей");        break;
        case 1: printf("один рубль");    break;
        case 2: printf("два рубля");     break;
        case 3: printf("три рубля");     break;
        case 4: printf("четыре рубля");  break;
        case 5: printf("пять рублей");   break;
        case 6: printf("шесть рублей");  break;
        case 7: printf("семь рублей");   break;
        case 8: printf("восемь рублей"); break;
        case 9: printf("девять рублей"); break;
        }
    }
    printf("\n");

    return 0;
}
