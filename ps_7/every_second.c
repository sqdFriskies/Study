#include <stdio.h>
#include <stdbool.h>

bool is_start(const char *word)
{
    return word[0] == 'S' && word[1] == 'T' && word[2] == 'A' && word[3] == 'R' && word[4] == 'T' && word[5] == '\0';
}

bool is_stop(const char *word)
{
    return word[0] == 'S' && word[1] == 'T' && word[2] == 'O' && word[3] == 'P' && word[4] == '\0';
}

void write_space(FILE *output_file)
{
    fputc(' ', output_file);
}

void write_word(const char *word, FILE *output_file)
{
    while (*word != '\0')
    {
        fputc(*word, output_file);
        word++;
    }
}



int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        perror("Error.\n");
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file)
    {
        perror("Error opening input file.\n");
        return 1;
    }

    FILE *output_file = fopen(argv[2], "w");
    if (!output_file)
    {
        perror("Error opening output file.\n");
        fclose(input_file);
        return 1;
    }

    char word[256];
    int index = 0;
    bool start_found = false;
    bool write_next = false;
    bool is_file_empty = true;
    int ch;
    while ((ch = fgetc(input_file)) != -1)
    {
        if (ch == ' ' || ch == '\n')
        {
            if (index > 0)
            {
                word[index] = '\0';

                if (!start_found)
                {
                    if (is_start(word))
                    {
                        start_found = true;
                    }
                }
                else
                {
                    
                    if (is_stop(word))
                    {
                        break;
                    }
                     
                    if (write_next)
                    {
                        if (!is_file_empty)
                        {
                            write_space(output_file);
                        }
                        write_word(word, output_file);
                        is_file_empty = false;
                    }
                   
                    write_next = !write_next;
                }

                index = 0;
            }
        }
        else
        {

            if (index < 254)
            {
                word[index++] = (char)ch;
            }
        }
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}
