#include <stdio.h>
#include <stdlib.h> 
#include "ballsortpuzzle.h"
#include <time.h>
#include <stdbool.h>
#include <curses.h>


void game_field(const int rows, const int columns, char field[rows][columns]) 
{
 
}


void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y) 
{
    // Validate column numbers and ensure they are not the same
    if (x < 1 || x > columns || y < 1 || y > columns || x == y) 
    {
        printf("Error: Invalid columns for movement.\n");
        return;
    }

    // Convert 1-based column indices to 0-based indices
    x -= 1; 
    y -= 1;

    // Find the topmost symbol in column x
    int source_row = -1;
    for (int i = 0; i < rows; i++) 
    {
        if (field[i][x] != ' ') 
        {
            source_row = i;
            break;
        }
    }

    // If no symbol is found in the source column, exit
    if (source_row == -1) 
    {
        printf("Error: Column %d is empty.\n", x + 1);
        return;
    }

    // Find the lowest available position in column y
    int target_row = -1;
    for (int i = rows - 1; i >= 0; i--) 
    {
        if (field[i][y] == ' ') 
        {
            target_row = i;
            break;
        }
    }

    // If no space is available in the target column, exit
    if (target_row == -1)
     {
        printf("Error: Column %d has no space for movement.\n", y + 1);
        return;
    }
    if ((target_row < rows - 1) && (field[target_row + 1][y] != field[source_row][x]))
    {
        printf("Symbol in row %d isn't equal the symbol in row %d", x + 1, y + 1);
    }
        // Move the symbol from the source column to the target column
        field[target_row][y] = field[source_row][x];
        field[source_row][x] = ' ';
        y = 0;
        x = 0;

        printf("Symbol successfully moved from column %d to column %d, to row %d.\n", x + 1, y + 1, target_row + 1);
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

void print_field(const int rows, const int columns, char field[rows][columns])
{
     // Print each row
    for (int i = 0; i < rows; i++)
    {
        print_line(rows, columns, field, i); 
    }

    // Print the bottom line ---
    printf("---");
    for (int j = 0; j < columns; j++)
    {
        printf("----");
    }
    printf("\n   ");

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
    const char symbols[]       = {'@', '+', '^', '*', '$', '.', '%', '!', '#', '&', '(', ')', ',', '/', '?', '=', '>', '<', '[', ']', '-'};  // need to add some symbols
    char symbols_using_count[] = { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}; 
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
                        if(symbols_using_count[idx_symbols] < max_symbols_count)
                        {
                            printf("idx_symbols = %d[%c], %d\n", idx_symbols,symbols[idx_symbols],symbols_using_count[idx_symbols]);
                            break;
                        }
                    }
                }
                if (symbols_using_count[idx_symbols] == max_symbols_count)
                {
                    for (int z = 0; z < columns - 2;z++)
                    {
                        printf("%d ", symbols_using_count[z]);
                    }
                        printf("\nError\n");
                }

                field[j][i] = symbols[idx_symbols];
                symbols_using_count[idx_symbols]++;
            }
        }
        
    }
    for (int z = 0; z < columns - 2;z++)
    {
        printf("%d ", symbols_using_count[z]);
    }
    printf("\n");
    print_field(rows, columns, field);
    }
}
void ball_sort_puzzle()
{

}

bool check(const int rows, const int columns, char field[rows][columns]) 
{
    for (int col = 0; col < columns; col++) {
        char first_symbol = ' ';
        bool is_valid_column = true;

        for (int row = 0; row < rows; row++) {
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
        // for (int row = 0; row < rows; row++) 
        // {
            // if (field[row][col] == ' ' && first_symbol != ' ')
            // {
            //     return false;
            // }
        // }
    }

    // All columns are valid
    return true;
}

