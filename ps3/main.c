#include <stdio.h>
#include <ctype.h>

int main() 
{
    char num[101];
    if (scanf("%100s", num) != 1)
     {
        return 1; 
    }

    unsigned long long sum = 0;
    for (int i = 0; num[i] != '\0'; i++) 
    {
        if (!isdigit((unsigned char)num[i]))
         {
            return 1; 
        }
        sum += num[i] - '0';
    }

    unsigned long long result = sum;
    while (result > 9)
    {
        unsigned long long temp_sum = 0;
        while (result > 0) 
        {
            temp_sum += result % 10;
            result /= 10;
        }
        result = temp_sum;
    }

    printf("%llu\n", result);
    return 0;
}