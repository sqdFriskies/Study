#include <stdio.h>

int last_digit(unsigned long int number)
{
    int result = number % 10;
    printf("last digit = %d\n", result);
    return result;
}

int main()
{
    unsigned long int number;
    scanf("%lu", &number);
    
    printf("number = %lu\n", number);
    unsigned long int result = number;
    while (result > 9)
    {
        int sum = 0;
        while (result > 0)
        {
            sum = sum + (last_digit(result));
            result = result / 10;
            printf("sum = %d; result = %lu\n",sum, result);
        }
        result = sum;
    }

    printf("%lu\n", result);
    return 0;
}