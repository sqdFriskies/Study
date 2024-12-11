#include <stdbool.h>
#include <stdio.h>
#include <string.h>
void encode_char(const char character, bool bits[8]);
void encode_string(const char string[], bool bytes[strlen(string) + 1][8]);
void bytes_to_blocks(const int cols, const int offset, bool blocks[offset * 8][cols], const int rows, bool bytes[rows][8]);
char decode_byte(const bool bits[8]);

