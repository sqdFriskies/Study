#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "playfair.h"
void build_matrix(const char *key, char matrix[5][5])
{
    int used[26] = {0};
    int r = 0, c = 0;
    // Сначала буквы из ключа (пробелы игнорируются, W заменяется на V)
    for (int i = 0; key[i] != '\0'; i++)
    {
        if (isspace(key[i]))
            continue;
        if (!isalpha(key[i]))
            continue; // если встречается недопустимый символ
        char ch = toupper(key[i]);
        if (ch == 'W')
            ch = 'V';
        int idx = ch - 'A';
        if (!used[idx])
        {
            used[idx] = 1;
            matrix[r][c] = ch;
            c++;
            if (c == 5)
            {
                r++;
                c = 0;
            }
            if (r == 5)
                break;
        }
    }
    // Заполняем оставшиеся клетки оставшимися буквами (W пропускаем)
    for (char ch = 'A'; ch <= 'Z'; ch++)
    {
        if (ch == 'W')
            continue;
        int idx = ch - 'A';
        if (!used[idx])
        {
            used[idx] = 1;
            matrix[r][c] = ch;
            c++;
            if (c == 5)
            {
                r++;
                c = 0;
            }
            if (r == 5)
                break;
        }
    }
}

// Функция для поиска позиции буквы в матрице
void find_position(char matrix[5][5], char letter, int *row, int *col)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (matrix[i][j] == letter)
            {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Функция для предварительной обработки текста при шифровании:
// - удаляет пробелы, приводит к верхнему регистру,
// - заменяет 'W' на 'V',
// - вставляет 'X' между двумя подряд одинаковыми буквами (если они не равны 'X'),
// - добавляет 'X' в конец, если длина нечётная.
char *preprocess_text(const char *text)
{
    int len = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (!isspace(text[i]))
            len++;
    }
    // Выделяем память, предполагая в худшем случае удвоение символов
    char *temp = malloc(2 * len + 1);
    if (!temp)
        return NULL;
    int j = 0;
    char prev = '\0';
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isspace(text[i]))
            continue;
        char ch = toupper(text[i]);
        if (!isalpha(ch))
        { // если встречается недопустимый символ
            free(temp);
            return NULL;
        }
        if (ch == 'W')
            ch = 'V';
        // Если предыдущая буква равна текущей, вставляем 'X', если предыдущая не 'X'
        if (prev == ch && ch != 'X')
        {
            temp[j++] = 'X';
        }
        temp[j++] = ch;
        prev = ch;
    }
    // Если длина полученной строки нечётная, добавляем 'X'
    if (j % 2 != 0)
    {
        temp[j++] = 'X';
    }
    temp[j] = '\0';
    char *result = malloc(j + 1);
    if (!result)
    {
        free(temp);
        return NULL;
    }
    strcpy(result, temp);
    free(temp);
    return result;
}

// Функция шифрования по Playfair
char *playfair_encrypt(const char *key, const char *text)
{
    if (!key || !text)
        return NULL;
    // Проверка: текст может содержать только буквы и пробелы
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (!isspace(text[i]) && !isalpha(text[i]))
            return NULL;
    }

    char matrix[5][5];
    build_matrix(key, matrix);

    char *prep = preprocess_text(text);
    if (!prep)
        return NULL;
    int len = strlen(prep);
    int pair_count = len / 2;
    // Для каждой пары: 2 буквы и пробел между парами (последняя пара без пробела)
    int out_len = pair_count * 3;
    char *output = malloc(out_len + 1);
    if (!output)
    {
        free(prep);
        return NULL;
    }
    int pos = 0;
    for (int i = 0; i < len; i += 2)
    {
        char a = prep[i];
        char b = prep[i + 1];
        int row1, col1, row2, col2;
        find_position(matrix, a, &row1, &col1);
        find_position(matrix, b, &row2, &col2);
        char enc_a, enc_b;
        if (row1 == row2)
        {
            // Если обе буквы в одной строке – сдвигаем вправо (циклически)
            enc_a = matrix[row1][(col1 + 1) % 5];
            enc_b = matrix[row2][(col2 + 1) % 5];
        }
        else if (col1 == col2)
        {
            // Если в одном столбце – сдвигаем вниз
            enc_a = matrix[(row1 + 1) % 5][col1];
            enc_b = matrix[(row2 + 1) % 5][col2];
        }
        else
        {
            // Если буквы на разных строках и столбцах – берем буквы на пересечениях
            enc_a = matrix[row1][col2];
            enc_b = matrix[row2][col1];
        }
        output[pos++] = enc_a;
        output[pos++] = enc_b;
        if (i + 2 < len)
        {
            output[pos++] = ' ';
        }
    }
    output[pos] = '\0';
    free(prep);
    return output;
}

// Функция дешифрования по Playfair
char *playfair_decrypt(const char *key, const char *text)
{
    if (!key || !text)
        return NULL;
    // Проверка: текст должен состоять только из букв и пробелов
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (!isspace(text[i]) && !isalpha(text[i]))
            return NULL;
    }
    // В примерах зашифрованный текст содержит буквы 'X', поэтому дополнительная проверка не делается.

    char matrix[5][5];
    build_matrix(key, matrix);

    // Убираем пробелы из зашифрованного текста
    int len = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (!isspace(text[i]))
            len++;
    }
    if (len % 2 != 0)
        return NULL; // длина должна быть четной
    char *prep = malloc(len + 1);
    if (!prep)
        return NULL;
    int j = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (!isspace(text[i]))
        {
            prep[j++] = toupper(text[i]);
        }
    }
    prep[j] = '\0';

    char *output = malloc(len + 1); // в расшифрованном тексте не будет пробелов
    if (!output)
    {
        free(prep);
        return NULL;
    }
    int pos = 0;
    for (int i = 0; i < len; i += 2)
    {
        char a = prep[i];
        char b = prep[i + 1];
        int row1, col1, row2, col2;
        find_position(matrix, a, &row1, &col1);
        find_position(matrix, b, &row2, &col2);
        char dec_a, dec_b;
        if (row1 == row2)
        {
            // Если буквы в одной строке – сдвигаем влево
            dec_a = matrix[row1][(col1 + 4) % 5];
            dec_b = matrix[row2][(col2 + 4) % 5];
        }
        else if (col1 == col2)
        {
            // Если в одном столбце – сдвигаем вверх
            dec_a = matrix[(row1 + 4) % 5][col1];
            dec_b = matrix[(row2 + 4) % 5][col2];
        }
        else
        {
            // Если буквы на разных строках и столбцах – меняем столбцы
            dec_a = matrix[row1][col2];
            dec_b = matrix[row2][col1];
        }
        output[pos++] = dec_a;
        output[pos++] = dec_b;
    }
    output[pos] = '\0';
    free(prep);
    return output;
}

int main()
{
    char *encrypted, *decrypted;

    // even length of string
    encrypted = playfair_encrypt("SeCReT", "Hello world");

    decrypted = playfair_decrypt("SeCReT", encrypted);

    free(encrypted);
    free(decrypted);

    // odd length of string
    encrypted = playfair_encrypt("world", "Hello");
    printf("%s", encrypted);
    // "Hello" --> "HELXLO"
    return 0;
}