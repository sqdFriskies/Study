#include <math.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ballsortpuzzle.h"
#include "c4.h"
#include <stdbool.h>

void print_line(const int rows, const int columns, char field[rows][columns], int row);
void print_field(const int rows, const int columns, char field[rows][columns]);
void generator(const int rows, const int columns, char field[rows][columns]);
void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y);
void run_c4();

int main()
{
    {
        // const int rows = 3;
        // const int columns = 4;

        // char field[rows][columns];

        // generator(rows, columns, field); // ПРОВЕРКА ДЛЯ 1-ГО ЗАДАНИЯ

        // const int rows = 8, columns = 6;
        // char field[rows][columns];

        // // Инициализация массива вручную
        // char init_data[4][6] = {
        //     {' ', ' ', '^', '@', '@', ' '},
        //     {'+', ' ', '^', '@', '^', ' '},
        //     {'+', ' ', '*', '+', '+', ' '},
        //     {'*', '+', '*', '@', '^', ' '}   // ПРОВЕРКА ДЛЯ 2 ЗАДАНИЯ
        // };

        // for (int i = 0; i < rows; i++) {
        //     for (int j = 0; j < columns; j++) {
        //         field[i][j] = init_data[i][j];
        //     }
        // }

        // char init_data[8][6] = {
        //     {' ', ' ', ' ', ' ', ' ', ' '},
        //     {' ', '^', ' ', '^', ' ', '@'},
        //     {' ', '*', '+', '*', ' ', '^'},
        //     {' ', '+', '@', '*', ' ', '*'},
        //     {' ', '@', '^', '^', ' ', '+'},
        //     {' ', '@', '*', '+', ' ', '+'},
        //     {' ', '+', '^', '@', ' ', '^'},
        //     {' ', '@', '+', '@', ' ', '@'}}; // ПРОВЕРКА ДЛЯ 2 ЗАДАНИЯ

        // for (int i = 0; i < rows; i++)
        // {
        //     for (int j = 0; j < columns; j++)
        //     {
        //         field[i][j] = init_data[i][j];
        //     }
        // }
        // game_field(rows, columns, field);
        // down_possible(rows, columns, field, 4, 5);
        // print_field(rows, columns, field);

        // const int rows = 4;
        // const int columns = 6;

        //
        // char field[4][6] = {
        //     {'@', '+', ' ', ' ', ' ', ' '},
        //     {'@', '+', ' ', ' ', ' ', ' '},
        //     {'@', '+', ' ', ' ', ' ', ' '},
        //     {'@', '+', ' ', ' ', ' ', ' '}
        // };                                   // ПРОВЕРКА ДЛЯ 3 ЗАДАНИЯ

        //
        // printf("Game field:\n");
        // for (int i = 0; i < rows; i++) {
        //     printf("%d |", i + 1);
        //     for (int j = 0; j < columns; j++) {
        //         printf(" %c |", field[i][j]);
        //     }
        //     printf("\n");
        // }

        //
        // printf("---");
        // for (int j = 0; j < columns; j++)
        //{
        //     printf("----");
        // }
        // printf("\n   ");

        // // Print the column numbers
        // for (int j = 0; j < columns; j++)
        //{
        //     printf(" %d  ", j + 1);
        // }
        // printf("\n");

        // // Call the check function and display the result
        // if (check(rows, columns, field))
        //{
        //     printf("All columns are fully collected (true).\n");
        // } else {
        //     printf("Some columns are incomplete or have mixed symbols (false).\n");
        // }
    }
    // system("clear");
    run_c4();

    return 0;
}
