#include <iostream>

using namespace std;

union proDouble
{
    double number;
    // ������� double � long long ��������� - 8 ����
    long long bytes; 
};

// ����� ����� � �������� ������������� ��� ���� long
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

// ����� ����� � �������� ������������� ��� ���� long long
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
    // ����� Long/Double
    int answer; 
    // ����� �������/������ ������, �������� ������, ������ ������
    int right, shift, numberOfDigits, seniorId;
    // ���������� ��� ������� �����
    unsigned long long mask, maskLeft, maskRight, numberPart, maskReverted, numberPartReverted;

    printf("If you want use long enter 0, if double - 1:\n");
    scanf("%i", &answer);
    if (answer == 0)
    {   
        // �����, � ������� �� ��������
        long A;
        // ��, ����� ����� ���� - ��� ���������
        long Before;

        printf("You are working with long\nEnter the number:\n");
        scanf("%ld", &A);
        printf("%ld\n", A);
        Before = A;
        printLongBinary(A);

        // ����� �������� ����������� �����, �������� �����/����
        printf("\nA cyclic shift will be performed\nYou should choose side, range of shift, power of shift\nSelect a side (0 - left, 1 - right):\n");
        scanf("%i", &right);
        // ����� �������� ����������� ��������
        printf("The number of the senior digit? From 0 to %i\n", sizeof(A) * 8 - 1);
        scanf("%i", &seniorId);
        // ���� ������� ������ ��� ������ ������
        if (seniorId < 0 || seniorId > (sizeof(A) * 8 - 1))
        {
            // ������������ ������
            seniorId =  sizeof(A) * 8 - 1;
        }
        // ������� ���� ����� ��������
        printf("By what number of digits will the shift be made? From 0 to %i\n", seniorId + 1);
        scanf("%i", &numberOfDigits);
        // ���� �������� ��� ������ ������
        if (numberOfDigits < 0 || numberOfDigits > seniorId + 1)
        {
            // ������������ �����
            numberOfDigits = seniorId + 1;
        }
        // ����� �������� ����� �����
        printf("How much will a shift?\n");
        scanf("%i", &shift);
        
        // �������� 3 ���� �� 4 � �� 1 - ���� � �� ��
        shift = shift % numberOfDigits; 
        // ����� �� ����� ������
        mask = -1; 
        maskLeft = -1;
        maskRight = -1;

        // �����, ��� ���� �����
        maskLeft = mask >> (sizeof(mask) * 8 - 1 - seniorId);
        // �����, ��� ���� ������
        maskRight = mask << seniorId + 1 - numberOfDigits;

        // ���� ������ � �����. ����� ���� 00011100
        mask = maskLeft & maskRight;
        // ����� ����� ��� ������ (��������� - ����) ���� 000XXX00, ��� XX - ����� �� ��������� ����� A
        numberPart = mask & A;

        // left shift
        if (right == 0) 
        {
            // ����������� ����� �����
            numberPart = (numberPart << shift) | (numberPart >> numberOfDigits - shift);
        }
        // right shift
        else 
        {    
            // ����������� ����� ������
            numberPart = (numberPart >> shift) | (numberPart << numberOfDigits - shift);
        }

        numberPart = numberPart & mask; // ������� ������� �� ��������� ������
        // ����� ���� 11100011
        maskReverted = ~mask;
        // ����� ����� ���� XXX000XX
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

        // ����� �������� ����������� �����, �������� �����/����
        printf("\nA cyclic shift will be performed\nYou should choose side, range of shift, power of shift\nSelect a side (0 - left, 1 - right):\n");
        scanf("%i", &right);
        // ����� �������� ����������� ��������
        printf("The number of the senior digit? From 0 to %i\n", sizeof(A.bytes) * 8 - 1);
        scanf("%i", &seniorId);
        // ���� ������� ������ ��� ������ ������
        if (seniorId < 0 || seniorId > (sizeof(A.bytes) * 8 - 1))
        {
            // ������������ ������
            seniorId =  sizeof(A.bytes) * 8 - 1;
        }
        // ������� ���� ����� ��������
        printf("By what number of digits will the shift be made? From 0 to %i\n", seniorId + 1);
        scanf("%i", &numberOfDigits);
        // ���� �������� ��� ������ ������
        if (numberOfDigits < 0 || numberOfDigits > seniorId + 1)
        {
            // ������������ �����
            numberOfDigits = seniorId + 1;
        }
        // ����� �������� ����� �����
        printf("How much will a shift?\n");
        scanf("%i", &shift);
        
        // �������� 3 ���� �� 4 � �� 1 - ���� � �� ��
        shift = shift % numberOfDigits; 
        // ����� �� ����� ������
        mask = -1; 
        maskLeft = -1;
        maskRight = -1;

        // �����, ��� ���� �����
        maskLeft = mask >> (sizeof(mask) * 8 - 1 - seniorId);
        // �����, ��� ���� ������
        maskRight = mask << seniorId + 1 - numberOfDigits;

        // ���� ������ � �����. ����� ���� 00011100
        mask = maskLeft & maskRight;
        // ����� ����� ��� ������ (��������� - ����) ���� 000XXX00, ��� XX - ����� �� ��������� ����� A
        numberPart = mask & A.bytes;

        // left shift
        if (right == 0) 
        {
            // ����������� ����� �����
            numberPart = (numberPart << shift) | (numberPart >> numberOfDigits - shift);
        }
        // right shift
        else 
        {    
            // ����������� ����� ������
            numberPart = (numberPart >> shift) | (numberPart << numberOfDigits - shift);
        }

        numberPart = numberPart & mask; // ������� ������� �� ��������� ������
        // ����� ���� 11100011
        maskReverted = ~mask;
        // ����� ����� ���� XXX000XX
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