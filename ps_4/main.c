#include <math.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include "ballsortpuzzle.h"
#include "c4.h"

int main()
{
    const int rows = 8;
    const int columns = 10;
    char field[rows][columns];

    generator(rows, columns, field);
    return 0;
}
