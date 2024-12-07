#include <stdio.h>
#include "c4.h"
#include <curses.h>
void initialize_board(int rows, int cols, char board[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            board[i][j] = '.';
        }
    }
}

void print_board(int rows, int cols, const char board[rows][cols])
{
    // Print the top border line
    for (int i = 0; i < cols; i++)
    {
        printf("+---");
    }
    printf("+\n");

    // Print the game board
    for (int i = 0; i < rows; i++)
    {
        printf("|");
        for (int j = 0; j < cols; j++)
        {
            printf(" %c |", board[i][j]);
        }
        printf("\n");
    }

    // Print the border line
    for (int i = 0; i < cols; i++)
    {
        printf("+---");
    }
    printf("+\n");

    // Print column numbers
    for (int i = 0; i < cols; i++)
    {
        printf("  %d ", i + 1);
    }
    printf("\n");
}
int is_valid_move(int rows, int cols, const char board[rows][cols], int col)
{
    if (col - 1 < 0 || col - 1 > cols)
    {
        return false;
    }

    bool switcher = false;

    for (int i = rows - 1; i >= 0; i--)
    {
        if (board[i][col - 1] == '.')
        {
            switcher = true;
            break;
        }
    }
    return switcher;
}

int drop_piece(int rows, int cols, char board[rows][cols], int col, char player_piece)
{

    for (int i = rows - 1; i >= 0; i--)
    {
        if (board[i][col - 1] == '.')
        {
            board[i][col - 1] = player_piece;
            return i;
        }
    }
    return -1;
}

int count_diagonal(int rows, int cols, const char board[rows][cols], int row, int col, char player_piece, int delta_r, int delta_c)
{
    int count = 0;
    {
        int r = row - 1;
        int c = col - 1;

        for (; ((delta_r >= 0) ? r < rows : r >= 0) &&
               ((delta_c >= 0) ? c < cols : c >= 0) &&
               (board[r][c] == player_piece);
             r += delta_r, c += delta_c)
        {
            count++;
        }
    }
    return count;
}

int check_win(int rows, int cols, const char board[rows][cols], int row, int col, char player_piece)
{
    int count = 0;
    // up/down vertical
    count += count_diagonal(rows, cols, board, row, col, player_piece, +1, 0); 
    count += count_diagonal(rows, cols, board, row, col, player_piece, -1, 0);
    if (count - 1 >= rows)
    {
        return 1;
    }
    count = 0;
    // right/left gorizontal
    count += count_diagonal(rows, cols, board, row, col, player_piece, 0, -1);
    count += count_diagonal(rows, cols, board, row, col, player_piece, 0, +1);
    if (count - 1 >= cols)
    {
        return 1;
    }

    count = 0;
    // right/up diagonal
    count += count_diagonal(rows, cols, board, row, col, player_piece, -1, +1);
    count += count_diagonal(rows, cols, board, row, col, player_piece, +1, -1);
    if (count - 1 >= rows)
    {
        return 1;
    }
    // left/down diagonal
    count = 0;
    count += count_diagonal(rows, cols, board, row, col, player_piece, -1, -1);
    count += count_diagonal(rows, cols, board, row, col, player_piece, +1, +1);
    if (count - 1 >= rows)
    {
        return 1;
    }

    return 0;
}

int is_board_full(int rows, int cols, const char board[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (board[i][j] == '.')
            {
                return 0;
            }
        }
    }
    return 1;
}

void run_c4()
{
    const int rows = 4;
    const int cols = 6;
    char board[4][6] = {
        {'O', '.', 'X', 'X', 'X', 'X'},
        {'O', 'X', 'X', 'O', 'X', 'O'},
        {'O', 'O', 'X', 'X', 'O', 'O'},
        {'X', 'X', 'O', 'X', 'O', 'O'}
        }; 
    bool is_player_x = true;
    // initialize_board(rows, cols, board);

    while (!is_board_full(rows, cols, board))
    {

        const char player_piece = is_player_x ? 'X' : 'O';
        is_player_x = !is_player_x;
        int player_choice = -1;
        // system("clear");
        print_board(rows, cols, board);
        printf("\n");
        printf("\nPlayer %c: ", player_piece);
        scanf("%d", &player_choice);

        if (player_choice >= 0 && is_valid_move(rows, cols, board, player_choice))
        {
            const int row = drop_piece(rows, cols, board, player_choice, player_piece);
            if (row >=0 )
            {
                if (check_win(rows, cols, board, row+1, player_choice, player_piece))
                {
                    printf("\nYou win!\n");
                    break;
                }
            }
        }
        else
        {
            printf("\nError: move is not valid. \nYou skip your turn.\n\n");
        }
    }
    print_board(rows, cols, board);
}