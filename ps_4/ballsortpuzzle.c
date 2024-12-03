#include <stdio.h>
#include <stdlib.h>
#include "ballsortpuzzle.h"
#include <time.h>

// bool check(const int rows, const int columns, char field[rows][columns])
// {

// }

int validate_columns(int columns, int x, int y)
{
    if (x < 1 || x > columns || y < 1 || y > columns || x == y)
    {
        printf("Error: Invalid columns for movement.\n");
        return 0; // Ошибка
    }
    return 1; // Успех
}

int find_topmost_symbol(int rows, int x, char field[rows][x])
{
    for (int i = 0; i < rows; i++)
    {
        if (field[i][x] != ' ')
        {
            return i; // Найден символ
        }
    }
    return -1; // Символ не найден
}

int find_lowest_empty_position(int rows, int y, char field[rows][y])
{
    for (int i = rows - 1; i >= 0; i--)
    {
        if (field[i][y] == ' ')
        {
            return i; // Найдено место
        }
    }
    return -1; // Места нет
}

void move_symbol(int rows, char field[rows][rows], int source_row, int x, int target_row, int y)
{
    field[target_row][y] = field[source_row][x];
    field[source_row][x] = ' ';
}

void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y)
{
    // Convert 1-based column indices to 0-based indices
    x -= 1;
    y -= 1;

    // Validate column numbers and ensure they are not the same
    if (x < 0 || x > columns || y < 0 || y > columns || x == y)
    {
        printf("Error: Invalid columns for movement.\n");
        return;
    }

    // Find the topmost symbol in column x
    char first_char = ' ';
    int first_idx = -1;
    for (int i = rows - 1; i >= 0; i--)
    {
        if (field[i][x] != ' ')
        {
            first_char = field[i][x];
            first_idx = i;
        }
    }

    if (first_char == ' ')
    {
        printf("Error: empty column!\n");
        return;
    }

    char second_char = ' ';
    int second_idx = -1;

    for (int i = 0; i < rows; i++)
    {
        if (field[i][y] == ' ')
        {
            second_idx = i;
            second_char = field[i == rows - 1 ? i : i + 1][y];
        }
    }
    if (second_idx == -1)
    {
        printf("Error: second column is full!\n");
        return;
    }
    if (first_char != second_char)
    {
        if (second_char != ' ')
        {
            printf("ERROR: symbols are not the same!\n");
            return;
        }
    }
    // Move the symbol from the source column to the target column
    field[second_idx][y] = field[first_idx][x];
    field[first_idx][x] = ' ';
}

void print_line(const int rows, const int columns, char field[rows][columns], int row)
{
    // 1 | @ | * |   |   | + | + |
    printf("%d |", row + 1);

    for (int j = 0; j < columns; j++) // Iterate over the columns
    {
        printf(" %c |", field[row][j]);
    }
    printf("\n");
}

void game_field(const int rows, const int columns, char field[rows][columns])
{
    printf("\n");
    // Print each row
    for (int i = 0; i < rows; i++)
    {
        print_line(rows, columns, field, i);
    }

    // Print the bottom line ---
    printf("  ");
    for (int j = 0; j < columns; j++)
    {
        printf("+---");
    }
    printf("+\n   ");

    // Print column numbering
    for (int j = 0; j < columns; j++)
    {
        printf(" %d  ", j + 1);
    }
    printf("\n");
}

void generator(const int rows, const int columns, char field[rows][columns])
{
    srand(time(0));
    const char symbols[] = {'@', '+', '^', '*', '$', '.', '%', '!', '#', '&', '(', ')', ',', '/', '?', '=', '>', '<', '[', ']', '-'}; // need to add some symbols
    char symbols_using_count[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    const int symbols_count = sizeof(symbols) / sizeof(symbols[0]);
    const int symbols_variants = columns - 2;
    const int max_symbols_count = rows;
    if (symbols_count >= rows)
    {
        // Initialize the field with spaces
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                field[i][j] = ' ';
            }
        }

        // Generate two random empty columns
        int empty_1 = rand() % columns;
        int empty_2 = rand() % columns;

        for (; empty_2 == empty_1;) // Examination of second empty column is different
        {
            empty_2 = rand() % columns;
        }
        for (int i = 0; i < columns; i++)
        {
            if (i != empty_1 && i != empty_2)
            {
                for (int j = 0; j < rows; j++)
                {
                    int idx_symbols = rand() % symbols_variants;
                    if (symbols_using_count[idx_symbols] == max_symbols_count)
                    {
                        for (int count_idx = 0; count_idx < symbols_variants; count_idx++)
                        {
                            idx_symbols = (idx_symbols + 1) % symbols_variants;
                            if (symbols_using_count[idx_symbols] < max_symbols_count)
                            {
                                // printf("idx_symbols = %d[%c], %d\n", idx_symbols, symbols[idx_symbols], symbols_using_count[idx_symbols]);
                                break;
                            }
                        }
                    }

                    field[j][i] = symbols[idx_symbols];
                    symbols_using_count[idx_symbols]++;
                }
            }
        }

        // print_field(rows, columns, field);
    }
}

bool check(const int rows, const int columns, char field[rows][columns])
{
    for (int col = 0; col < columns; col++)
    {
        char first_symbol = ' ';
        bool is_valid_column = true;

        for (int row = 0; row < rows; row++)
        {
            // Skip empty cells
            if (field[row][col] == ' ')
            {
                continue;
            }

            // Set the first non-empty symbol for this column
            if (first_symbol == ' ')
            {
                first_symbol = field[row][col];
            }
            // Check if the current symbol matches the first one
            else if (field[row][col] != first_symbol)
            {
                is_valid_column = false;
                break;
            }
        }

        // If any column is invalid, return false
        if (!is_valid_column)
        {
            return false;
        }

        // Check if the column is incomplete (contains spaces between symbols)
        for (int row = 0; row < rows; row++)
        {
            if (field[row][col] == ' ' && first_symbol != ' ')
            {
                return false;
            }
        }
    }

    // All columns are valid
    return true;
}

void ball_sort_puzzle()
{
    system("clear");
    int rows = 3;
    int cols = 4;
    char field[rows][cols];
    generator(rows, cols, field);

    int pos1, pos2;
    while (!check(rows, cols, field))
    {
        game_field(rows, cols, field);
        printf("\nPosition 1: ");
        scanf("%d", &pos1);
        printf("\nPosition 2: ");
        scanf("%d", &pos2);
        system("clear");
        down_possible(rows, cols, field, pos1, pos2);
    }
    game_field(rows, cols, field);
    printf("\nYou win!\n");
}
