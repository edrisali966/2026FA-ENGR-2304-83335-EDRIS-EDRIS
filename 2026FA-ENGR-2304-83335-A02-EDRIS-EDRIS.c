/* 2026FA-ENGR-2304-83335-P02-EDRIS-EDRIS */

#include <stdio.h>
#include <string.h>

void decimalToBinary(int decimal)
{
    int binary[8];
    int magnitude;
    int i;

    magnitude = decimal;

    if (magnitude < 0)
    {
        magnitude = -magnitude;
    }

    for (i = 7; i >= 1; i--)
    {
        binary[i] = magnitude % 2;
        magnitude = magnitude / 2;
    }

    binary[0] = (decimal < 0) ? 1 : 0;

    printf("8-bit signed magnitude binary: ");

    for (i = 0; i < 8; i++)
    {
        printf("%d", binary[i]);
    }

    printf("\n");
}

void binaryToDecimal(char input[])
{
    int length;
    int i;
    int value;
    int sign;

    length = strlen(input);

    if (length != 8)
    {
        printf("Error: enter an 8-bit signed magnitude binary number.\n");
        return;
    }

    for (i = 0; i < 8; i++)
    {
        if (input[i] != '0' && input[i] != '1')
        {
            printf("Error: binary number can contain only 0 and 1.\n");
            return;
        }
    }

    value = 0;

    for (i = 1; i < 8; i++)
    {
        value = value * 2 + (input[i] - '0');
    }

    if (input[0] == '1')
    {
        sign = -1;
    }
    else
    {
        sign = 1;
    }

    printf("Decimal result: %d\n", sign * value);
}

int hexValue(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }

    if (c >= 'A' && c <= 'F')
    {
        return c - 'A' + 10;
    }

    if (c >= 'a' && c <= 'f')
    {
        return c - 'a' + 10;
    }

    return -1;
}

char hexDigit(int value)
{
    if (value < 10)
    {
        return '0' + value;
    }

    return 'A' + value - 10;
}

void binaryToHex(char input[])
{
    int length;
    int dot;
    int intBits;
    int fracBits;
    int i;
    int j;
    int value;
    int start;
    int resultIndex;
    int groupStart;
    int groups;
    char result[100];

    length = strlen(input);
    dot = -1;

    for (i = 0; i < length; i++)
    {
        if (input[i] == '.')
        {
            if (dot != -1)
            {
                printf("Error: only one decimal point is allowed.\n");
                return;
            }

            dot = i;
        }
    }

    if (dot == -1)
    {
        intBits = length;
        fracBits = 0;
    }
    else
    {
        intBits = dot;
        fracBits = length - dot - 1;
    }

    if (intBits > 32 || fracBits > 32)
    {
        printf("Error: maximum is 32 binary bits on either side of the decimal point.\n");
        return;
    }

    for (i = 0; i < length; i++)
    {
        if (input[i] != '.' &&
            input[i] != '0' &&
            input[i] != '1')
        {
            printf("Error: invalid binary number.\n");
            return;
        }
    }

    resultIndex = 0;

    if (intBits == 0)
    {
        result[resultIndex] = '0';
        resultIndex++;
    }
    else
    {
        groups = (intBits + 3) / 4;
        start = intBits - groups * 4;

        for (i = 0; i < groups; i++)
        {
            value = 0;

            for (j = 0; j < 4; j++)
            {
                groupStart = start + i * 4 + j;

                if (groupStart < 0)
                {
                    value = value * 2;
                }
                else
                {
                    value = value * 2 + (input[groupStart] - '0');
                }
            }

            result[resultIndex] = hexDigit(value);
            resultIndex++;
        }
    }

    if (fracBits > 0)
    {
        result[resultIndex] = '.';
        resultIndex++;

        groups = (fracBits + 3) / 4;

        for (i = 0; i < groups; i++)
        {
            value = 0;

            for (j = 0; j < 4; j++)
            {
                groupStart = dot + 1 + i * 4 + j;

                if (groupStart < length)
                {
                    value = value * 2 + (input[groupStart] - '0');
                }
                else
                {
                    value = value * 2;
                }
            }

            result[resultIndex] = hexDigit(value);
            resultIndex++;
        }
    }

    result[resultIndex] = '\0';

    printf("Hexadecimal result: 0x%s\n", result);
}

void hexToBinary(char input[])
{
    int length;
    int i;
    int j;
    int value;
    int dot;
    int integerDigits;
    int fractionDigits;
    int resultIndex;
    char result[200];

    if (input[0] != '0' ||
        (input[1] != 'x' && input[1] != 'X'))
    {
        printf("Error: hexadecimal numbers must start with 0x.\n");
        return;
    }

    length = strlen(input);
    dot = -1;

    for (i = 2; i < length; i++)
    {
        if (input[i] == '.')
        {
            if (dot != -1)
            {
                printf("Error: only one decimal point is allowed.\n");
                return;
            }

            dot = i;
        }
    }

    if (dot == -1)
    {
        integerDigits = length - 2;
        fractionDigits = 0;
    }
    else
    {
        integerDigits = dot - 2;
        fractionDigits = length - dot - 1;
    }

    if (integerDigits > 8 || fractionDigits > 8)
    {
        printf("Error: maximum is 8 hexadecimal digits on either side of the decimal point.\n");
        return;
    }

    if (integerDigits == 0)
    {
        printf("Error: hexadecimal number must contain digits.\n");
        return;
    }

    resultIndex = 0;

    for (i = 2; i < length; i++)
    {
        if (input[i] == '.')
        {
            result[resultIndex] = '.';
            resultIndex++;
        }
        else
        {
            value = hexValue(input[i]);

            if (value < 0)
            {
                printf("Error: invalid hexadecimal number.\n");
                return;
            }

            for (j = 3; j >= 0; j--)
            {
                result[resultIndex] =
                    ((value >> j) & 1) + '0';

                resultIndex++;
            }
        }
    }

    result[resultIndex] = '\0';

    printf("Binary result: %s\n", result);
}

int main(void)
{
    int choice;
    int subChoice;
    int decimal;
    char input[100];

    while (1)
    {
        printf("\n");
        printf("====================================\n");
        printf(" ENGR 2304 NUMBER CONVERSION MENU\n");
        printf("====================================\n");
        printf("1. Decimal/Binary Conversion\n");
        printf("2. Hex/Binary Conversion\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        if (choice == 3)
        {
            printf("Program exited.\n");
            break;
        }

        if (choice == 1)
        {
            printf("\n");
            printf("1. Decimal to Binary\n");
            printf("2. Binary to Decimal\n");
            printf("Enter your choice: ");

            scanf("%d", &subChoice);

            if (subChoice == 1)
            {
                printf("Enter a decimal number (-127 to 127): ");
                scanf("%d", &decimal);

                if (decimal >= -127 && decimal <= 127)
                {
                    decimalToBinary(decimal);
                }
                else
                {
                    printf("Error: number must be between -127 and 127.\n");
                }
            }
            else if (subChoice == 2)
            {
                printf("Enter an 8-bit signed magnitude binary number: ");
                scanf("%99s", input);

                binaryToDecimal(input);
            }
            else
            {
                printf("Invalid choice.\n");
            }
        }
        else if (choice == 2)
        {
            printf("\n");
            printf("Enter a positive binary number or hexadecimal number.\n");
            printf("Hexadecimal numbers must start with 0x.\n");
            printf("Enter number: ");

            scanf("%99s", input);

            if (input[0] == '0' &&
                (input[1] == 'x' || input[1] == 'X'))
            {
                hexToBinary(input);
            }
            else
            {
                binaryToHex(input);
            }
        }
        else
        {
            printf("Invalid choice. Please select 1, 2, or 3.\n");
        }
    }

    return 0;
}