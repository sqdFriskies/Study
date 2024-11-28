#include <stdio.h>
#include <stdlib.h> 
#include "ballsortpuzzle.h"
#include <time.h>

void game_field(const int rows, const int columns, char field[rows][columns])
{

}

// bool check(const int rows, const int columns, char field[rows][columns])
// {

// }

void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y)
{

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
    const char symbols[] = {'@', '+', '^', '*', '$','.','%','!'}; // need to add some symbols
    const int symbols_count = sizeof(symbols) / sizeof(symbols[0]);
    if ( symbols_count >= rows )
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

    for (int i = 0; i < columns;i++)
    {
        if (i != empty_1 && i != empty_2)
        {
            for (int j = 0; j < rows; j++)
            {
                const int idx_symbols = rand() % rows;
                field[j][i] = symbols[idx_symbols];
            }
        }
    }
        // for (int s = 0; s < symbols_count; s++)
        // {
        //     for (int count = 0; count < rows; count++)
        //     {
        //         int col = 0;
        //         int row = 0;

        //         // Find a random empty position in a valid column
        //         for (int valid = 0; valid == 0;)
        //         {
        //             col = rand() % columns;
        //             row = rand() % rows;

        //             if (field[row][col] == ' ' && col != empty_1 && col != empty_2)
        //             {
        //                 valid = 1; // Found a valid position
        //             }
        //         }

        //         field[row][col] = symbols[s];
        //     }
        // }

    print_field(rows, columns, field);
    }
}
void ball_sort_puzzle()
{

}