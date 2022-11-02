#include <iostream>

using namespace std;

union proDouble
{
    double number;
    // Размеры double и long long совпадают - 8 байт
    long long bytes; 
};

// Вывод числа в бинарном представлении для типа long
void printLongBinary(long A) 
{
    for (int i = sizeof(A) * 8 - 1; i >= 0; i--)
    {
        printf("%ld", (A >> i) & 1);
        if (i % 8 == 0)
        {
            printf("%c", ' ');
        }        
    }
}

// Вывод числа в бинарном представлении для типа long long
void printLongLongBinary(long long A)
{
    for (int i = sizeof(A) * 8 - 1; i >= 0; i--)
    {
        printf("%lli", (A >> i) & 1);
        if (i % 8 == 0)
        {
            printf("%c", ' ');
        }       
    }
}

int main()
{   
    // Выбор Long/Double
    int answer; 
    // Выбор правого/левого сдвига, величину сдвига, границ сдвига
    int right, shift, numberOfDigits, seniorId;
    // Переменные для битовых масок
    unsigned long long mask, maskLeft, maskRight, numberPart, maskReverted, numberPartReverted;

    printf("If you want use long enter 0, if double - 1:\n");
    scanf("%i", &answer);
    if (answer == 0)
    {   
        // Число, с которым мы работаем
        long A;
        // То, каким число было - для сравнения
        long Before;

        printf("You are working with long\nEnter the number:\n");
        scanf("%ld", &A);
        printf("%ld\n", A);
        Before = A;
        printLongBinary(A);

        // Будет выполнен циклический сдвиг, выберите право/лево
        printf("\nA cyclic shift will be performed\nYou should choose side, range of shift, power of shift\nSelect a side (0 - left, 1 - right):\n");
        scanf("%i", &right);
        // Номер старшего сдвигаемого элемента
        printf("The number of the senior digit? From 0 to %i\n", sizeof(A) * 8 - 1);
        scanf("%i", &seniorId);
        // Если старший разряд вне вскяих границ
        if (seniorId < 0 || seniorId > (sizeof(A) * 8 - 1))
        {
            // Максимальный разряд
            seniorId =  sizeof(A) * 8 - 1;
        }
        // Сколько цифр будет сдвинуто
        printf("By what number of digits will the shift be made? From 0 to %i\n", seniorId + 1);
        scanf("%i", &numberOfDigits);
        // Если диапозон вне всяких границ
        if (numberOfDigits < 0 || numberOfDigits > seniorId + 1)
        {
            // Максимальный сдвиг
            numberOfDigits = seniorId + 1;
        }
        // Какой величины будет сдвиг
        printf("How much will a shift?\n");
        scanf("%i", &shift);
        
        // Смещение 3 цифр на 4 и на 1 - одно и то же
        shift = shift % numberOfDigits; 
        // Маска из одних единиц
        mask = -1; 
        maskLeft = -1;
        maskRight = -1;

        // Маска, где нули слева
        maskLeft = mask >> (sizeof(mask) * 8 - 1 - seniorId);
        // Маска, где нули справа
        maskRight = mask << seniorId + 1 - numberOfDigits;

        // Нули справа и слева. Маска вида 00011100
        mask = maskLeft & maskRight;
        // Часть числа для сдвига (остальное - нули) вида 000XXX00, где XX - цифры из исходного числа A
        numberPart = mask & A;

        // left shift
        if (right == 0) 
        {
            // Циклический сдвиг влево
            numberPart = (numberPart << shift) | (numberPart >> numberOfDigits - shift);
        }
        // right shift
        else 
        {    
            // Циклический сдвиг вправо
            numberPart = (numberPart >> shift) | (numberPart << numberOfDigits - shift);
        }

        numberPart = numberPart & mask; // Убираем единицы за границами сдвига
        // Маска вида 11100011
        maskReverted = ~mask;
        // Часть числа вида XXX000XX
        numberPartReverted = A & maskReverted;
            
        // 000XXX00 | XXX000XX = XXXXXXXX
        A = numberPart | numberPartReverted;

        printf("Parameters:\n\tRight: %12.i\n\tSenior Digit: %6.i\n\tNumber Of Digits: %2.i\n\tShift: %12.i\n", right, seniorId, numberOfDigits, shift);
        printf("Before: ");
        printLongBinary(Before);
        printf("\n   Now: ");
        printLongBinary(A); 

    }
    else
    {
        proDouble A;
        long long Before;

        printf("You are working with double\n");
        scanf("%le", &A.number);
        printf("%le\n", A.number);
        printLongLongBinary(A.bytes);

        Before = A.bytes;

        // Будет выполнен циклический сдвиг, выберите право/лево
        printf("\nA cyclic shift will be performed\nYou should choose side, range of shift, power of shift\nSelect a side (0 - left, 1 - right):\n");
        scanf("%i", &right);
        // Номер старшего сдвигаемого элемента
        printf("The number of the senior digit? From 0 to %i\n", sizeof(A.bytes) * 8 - 1);
        scanf("%i", &seniorId);
        // Если старший разряд вне вскяих границ
        if (seniorId < 0 || seniorId > (sizeof(A.bytes) * 8 - 1))
        {
            // Максимальный разряд
            seniorId =  sizeof(A.bytes) * 8 - 1;
        }
        // Сколько цифр будет сдвинуто
        printf("By what number of digits will the shift be made? From 0 to %i\n", seniorId + 1);
        scanf("%i", &numberOfDigits);
        // Если диапозон вне всяких границ
        if (numberOfDigits < 0 || numberOfDigits > seniorId + 1)
        {
            // Максимальный сдвиг
            numberOfDigits = seniorId + 1;
        }
        // Какой величины будет сдвиг
        printf("How much will a shift?\n");
        scanf("%i", &shift);
        
        // Смещение 3 цифр на 4 и на 1 - одно и то же
        shift = shift % numberOfDigits; 
        // Маска из одних единиц
        mask = -1; 
        maskLeft = -1;
        maskRight = -1;

        // Маска, где нули слева
        maskLeft = mask >> (sizeof(mask) * 8 - 1 - seniorId);
        // Маска, где нули справа
        maskRight = mask << seniorId + 1 - numberOfDigits;

        // Нули справа и слева. Маска вида 00011100
        mask = maskLeft & maskRight;
        // Часть числа для сдвига (остальное - нули) вида 000XXX00, где XX - цифры из исходного числа A
        numberPart = mask & A.bytes;

        // left shift
        if (right == 0) 
        {
            // Циклический сдвиг влево
            numberPart = (numberPart << shift) | (numberPart >> numberOfDigits - shift);
        }
        // right shift
        else 
        {    
            // Циклический сдвиг вправо
            numberPart = (numberPart >> shift) | (numberPart << numberOfDigits - shift);
        }

        numberPart = numberPart & mask; // Убираем единицы за границами сдвига
        // Маска вида 11100011
        maskReverted = ~mask;
        // Часть числа вида XXX000XX
        numberPartReverted = A.bytes & maskReverted;
            
        // 000XXX00 | XXX000XX = XXXXXXXX
        A.bytes = numberPart | numberPartReverted;

        printf("Parameters:\n\tRight: %12.i\n\tSenior Digit: %6.i\n\tNumber Of Digits: %2.i\n\tShift: %12.i\n", right, seniorId, numberOfDigits, shift);
        printf("Before: ");
        printLongLongBinary(Before);
        printf("\n   Now: ");
        printLongLongBinary(A.bytes);
        printf("\n%le\n", A.number);

    }

    return 0;
}