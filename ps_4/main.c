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
int power(int base, int exp);
int main()
{
    int length = 4 + 1, cols = 3, offset = 2;
    bool bytes1[4 + 1][8] = {
        {0, 1, 0, 0, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 1, 1, 1},
        {0, 1, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}};
    bool blocks1[offset * 8][cols];
    bytes_to_blocks(cols, offset, blocks1, length, bytes1);
    for (int j = 0; j < offset * 8; j++)
    {
        for (int i = 0; i < cols; i++)
        {
            printf("%d ", (blocks1[j][i] == true) ? 1 : 0);
        }
        printf("\n");
        if (j % 8 == 7)
        {
            printf("\n");
        }
    }
    // prints:
    // 0 0 0
    // 1 1 1
    // 0 1 1
    // 0 0 0
    // 0 1 1
    // 0 0 1
    // 0 0 1
    // 1 0 1
    //
    // 0 0 0
    // 1 0 0
    // 1 0 0
    // 0 0 0
    // 1 0 0
    // 0 0 0
    // 1 0 0
    // 0 0 0

    bool blocks2[2 * 8][3] = {
        {0, 0, 0},
        {1, 1, 1},
        {0, 1, 1},
        {0, 0, 0},
        {0, 1, 1},
        {0, 0, 1},
        {0, 0, 1},
        {1, 0, 1},
        {0, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
        {0, 0, 0},
        {1, 0, 0},
        {0, 0, 0},
        {1, 0, 0},
        {0, 0, 0}};
    bool bytes2[length][8];
    blocks_to_bytes(3, 2, blocks2, length, bytes2);
    for (int j = 0; j < length; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            printf("%d", bytes2[j][i]);
        }
        printf("\n");
    }
    // prints:
    // 01000001
    // 01101000
    // 01101111
    // 01101010
    // 00000000
}

int power(int base, int exp)
{
    if (base == 0 && exp <= 0)
    {
        return 0;
    }

    if (exp < 0)
    {
        return 0;
    }

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
    char character = '\0';
    bool temp_bits[8];

    for (char c = 0; c < 128; c++)
    {
        encode_char(c, temp_bits);

        bool match = true;
        for (int i = 0; i < 8; i++)
        {
            if (temp_bits[i] != bits[i])
            {
                match = false;
                break;
            }
        }

        if (match)
        {
            character = c;
            break;
        }
    }

    return character;
}

void encode_string(const char string[], bool bytes[strlen(string) + 1][8])
{
    for (int i = 0; i < (strlen(string) + 1); i++)
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

void fill_column(const int cols, const int offset, bool blocks[offset * 8][cols], int number_of_column, const int number_of_offset, char symbol)
{
    bool bits[8];
    encode_char(symbol, bits);
    for (int row = number_of_offset * 8; row < (number_of_offset * 8) + 8; row++)
    {
        blocks[row][number_of_column] = bits[row - number_of_offset * 8];
    }
}

void bytes_to_blocks(const int cols, const int offset, bool blocks[offset * 8][cols], const int rows, bool bytes[rows][8])
{
    int row = 0;
    for (int number_of_offset = 0; number_of_offset < offset; number_of_offset++)
    {
        for (int number_of_column = 0; number_of_column < cols;number_of_column++)
        {
            char symbol = 0;
            if(row < rows)
            {
                symbol = decode_byte(bytes[row]);
            }
            fill_column(cols, offset, blocks, number_of_column, number_of_offset, symbol);
            row++;
        }
    }
}

char get_column(const int cols, const int offset, bool blocks[offset * 8][cols], int number_of_column, const int number_of_offset)
{
    bool bits[8];
    int bit_index = 0;
    for (int row = number_of_offset * 8; row < (number_of_offset * 8) + 8; row++)
    {
        bits[bit_index++] = blocks[row][number_of_column];
    }
    return decode_byte(bits);
}

void blocks_to_bytes(const int cols, const int offset, bool blocks[offset * 8][cols], const int rows, bool bytes[rows][8])
{
    int row = 0;
    for (int number_of_offset = 0; number_of_offset < offset; number_of_offset++)
    {
        for (int number_of_column = 0; number_of_column < cols; number_of_column++)
        {
            char symbol = get_column(cols, offset, blocks, number_of_column, number_of_offset);
            if (row < rows)
            {
                encode_char(symbol, bytes[row]);
            }
            else
            {
                return;
            }
            row++;
        }
    }
}