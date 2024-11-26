#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
int main()
{

    start_color();
    //printf("%.4f\n", lift_a_car(4, 90, 1650)); // uloha 1

    //printf("%.4f\n", unit_price(4.79, 16, 150)); // uloha 2

    //printf("%d\n", bank_notes(50)); // uloha 3
    //printf("%d\n", bank_notes(5));

    //printf("%d\n", euler(10)); // uloha 4 now full

    //int input_array[] = { 3,0,1 };
    //printf("%d\n", find_missing_number(3, input_array)); // uloha 5

    //printf("%lu\n", sum_squared(4));
 initscr();
 use_default_colors();
 printw("line 1\n");
 printw("line 2\n");
 start_color();
 init_pair(1, COLOR_RED, COLOR_BLACK);
 printw("line 3");
 getch();
 endwin();

 return 0;
}
