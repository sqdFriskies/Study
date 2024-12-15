#include <stdio.h>
    
char get_small_letter(char letter)
{
    if(letter>='A' && letter<='Z')
    {
        return letter + ('a' - 'A');
    }
    return letter;
}

int main()
    {
        const int line_len = 255;
        char line[line_len];
        FILE *file = fopen("bananas1.txt", "r");

        if (file == NULL)
        {
            fgets(line, line_len, file);
            for (int i = 0; i < )
        }

        fclose(file);
        return 0;
    }
