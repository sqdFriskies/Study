#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
void encode_char(const char character, bool bits[8]);
char decode_byte(const bool bits[8]);
void encode_string(const char string[], bool bytes[strlen(string) + 1][8]);
void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]);
void bytes_to_blocks(const int cols, const int offset, bool blocks[offset * 8][cols], const int rows, bool bytes[rows][8]);
void blocks_to_bytes(const int cols, const int offset, bool blocks[offset * 8][cols], const int rows, bool bytes[rows][8]);
int main()
{
    bool bits1[8];
    encode_char('A', bits1);
    for (int i = 0; i < 8; i++)
    {
        printf("%d", bits1[i]);
    }
    printf("\n");
    // prints: 01000001

    bool bits2[8] = {0, 1, 0, 0, 0, 0, 0, 1};
    printf("%c\n", decode_byte(bits2));
    // prints: A
}

int power(int base, int exp)
{
    int result = 1;
    for (int i = 0; i < exp; i++)
    {
        result *= base;
    }
    return result;
}
void encode_char(const char character, bool bits[8])
{
    for (int i = 0; i < 8; i++)
    {
        const bool bit = (character >> (i)) & 0x1;
        bits[7 - i] = bit;
    }
}

char decode_byte(const bool bits[8])
{
    char result = 0;
    for (int i = 0; i < 8; i++)
    {
        const char bit = bits[i] ? 1 : 0;
        result = result | (bit << (7-i));
    }
    return result;
}

void encode_string(const char string[], bool bytes[strlen(string) + 1][8])
{
    int len = strlen(string) + 1;
    for (int i = 0; i < len; i++)
    {
        int ascii_value = (int)string[i];
        for (int j = 7; j >= 0; j--)
        {
            int divisor = power(2, j);
            bytes[i][7 - j] = ascii_value / divisor;
            ascii_value %= divisor;
        }
    }
}
void decode_bytes(const int rows, bool bytes[rows][8], char string[rows])
{
    for (int i = 0; i < rows; i++)
    {
        int ascii_value = 0;
        for (int j = 0; j < 8; j++)
        {
            if (bytes[i][j])
            {
                ascii_value += power(2, 7 - j);
            }
        }
        string[i] = (char)ascii_value;
    }
}
void bytes_to_blocks(const int cols, const int offset, bool blocks[offset * 8][cols], const int rows, bool bytes[rows][8])
{
    int block_row, block_col;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            block_row = (i / cols) * 8 + j;
            block_col = i % cols;
            blocks[block_row][block_col] = bytes[i][j];
        }
    }
}

void blocks_to_bytes(const int cols, const int offset, bool blocks[offset * 8][cols], const int rows, bool bytes[rows][8])
{
    int block_row, block_col;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            block_row = (i / cols) * 8 + j;
            block_col = i % cols;
            bytes[i][j] = blocks[block_row][block_col];
        }
    }
}