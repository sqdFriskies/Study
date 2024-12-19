#include <stdio.h>
#include <stdbool.h>
void write_word(const char *word, FILE *file)
{
    while (*word != '\0') 
    {
        fputc(*word, file);
        word++;
    }
    fputc(' ', file);
}

char get_small_letter(char letter)
{
    if (letter >= 'A' && letter <= 'Z')
    {
        return letter + ('a' - 'A');
    }
    return letter;
}

bool is_equal(const char *line, const char *found_line)
{
    for (int i = 0; found_line[i] != '\0'; i++)
    {
        if (line[i] == '\0' || get_small_letter(line[i]) != found_line[i])
        {
            return false;
        }
    }
    return true;
}

char *custom_fgets(char *str, int n, FILE *file)
{
    int i = 0;

    while (i < n - 1)
    {
        int ch = fgetc(file);

        if (ch == '\n')
        {
            str[i++] = (char)ch;
            break;
        }

        if (ch == -1)
        {
            if (i == 0)
                return 0;
            break;
        }

        str[i++] = (char)ch;
    }

    str[i] = '\0';
    return str;
}

void write_number(int number, FILE *file)
{
    char buffer[20]; 
    int index = 0;

    if (number == 0)
    {
        buffer[index++] = '0';
    }
    else
    {
        while (number > 0)
        {
            buffer[index++] = '0' + (number % 10);
            number /= 10;
        }
    }

    for (int i = index - 1; i >= 0; i--)
    {
        
        fputc(buffer[i], file);
    }
}

int main(int argc, char *argv[])
{
    if(argc < 2) {
        perror("Error opening file.");
        return 1;
    }
    const int line_len = 255;
    char line[line_len];
    line[0] = '\0';
    const char found_line[] = "ananas";
    FILE *file = fopen(argv[1], "r");
    int count = 0;

    if (file != NULL)
    {
        while (custom_fgets(line, line_len, file) != NULL)
        {
            for (int i = 0; line[i] != '\0'; i++)
            {
                if (is_equal(line + i, found_line))
                {
                    count++;
                }
            }
        }
        fclose(file);
    }

    file = fopen(argv[1], "w");
    if (file != NULL)
    {
        write_number(count,file);
        fclose(file);
    }

    return 0;
}