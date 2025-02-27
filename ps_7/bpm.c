#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *reverse(const char *text)
{
    if (text == NULL)
    {
        return NULL;
    }

    size_t len = strlen(text);
    char *reversed = malloc(len + 1);
    if (reversed == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < len; i++)
    {
        reversed[i] = toupper(text[len - 1 - i]);
    }

    reversed[len] = '\0';
    return reversed;
}

int main()
{

    char *reversed = reverse("Hello world!");
    printf("%s\n", reversed);
    // "!DLROW OLLEH"
    return 0;
}