#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void genMatrix(const char *k, char m[5][5], int p[26][2])
{
    int u[26] = {0}, r = 0, c = 0;
    for (; *k; k++)
        if (!isspace(*k))
        {
            char ch = toupper(*k);
            if (ch >= 'A' && ch <= 'Z' && ch != 'W')
            {
                int i = ch - 'A';
                if (!u[i])
                {
                    u[i] = 1;
                    m[r][c] = ch;
                    p[i][0] = r;
                    p[i][1] = c;
                    c = (c + 1) % 5;
                    r += !c;
                }
            }
        }
    for (char ch = 'A'; ch <= 'Z'; ch++)
        if (ch != 'W')
        {
            int i = ch - 'A';
            if (!u[i])
            {
                m[r][c] = ch;
                p[i][0] = r;
                p[i][1] = c;
                c = (c + 1) % 5;
                r += !c;
            }
        }
}

char *prepText(const char *t)
{
    size_t l = 0;
    for (const char *p = t; *p; p++)
        if (!isspace(*p))
            l++;
    char *s = malloc(2 * l + 1), prv = 0;
    if (!s)
        return NULL;
    size_t j = 0;
    for (const char *p = t; *p; p++)
        if (!isspace(*p))
        {
            char ch = toupper(*p) == 'W' ? 'V' : toupper(*p);
            if (!isalpha(ch))
            {
                free(s);
                return NULL;
            }
            if (prv == ch && ch != 'X')
                s[j++] = 'X';
            s[j++] = ch;
            prv = ch;
        }
    if (j % 2)
        s[j++] = 'X';
    s[j] = 0;
    char *r = strdup(s);
    free(s);
    return r;
}

char *crypt(const char *k, const char *t, int d)
{
    if (!k || !t)
        return NULL;
    for (const char *p = t; *p; p++)
        if (!isspace(*p) && !isalpha(*p))
            return NULL;
    char m[5][5], *pt = prepText(t);
    int p[26][2];
    if (!pt)
        return NULL;
    genMatrix(k, m, p);
    size_t l = strlen(pt), n = l / 2, pos = 0;
    char *o = malloc(n * (d ? 2 : 3) + 1);
    if (!o)
    {
        free(pt);
        return NULL;
    }
    for (size_t i = 0; i < l; i += 2)
    {
        int a = pt[i] - 'A', b = pt[i + 1] - 'A';
        int r1 = p[a][0], c1 = p[a][1], r2 = p[b][0], c2 = p[b][1];
        char ca, cb;
        if (r1 == r2)
        {
            ca = m[r1][(c1 + (d ? 4 : 1)) % 5];
            cb = m[r2][(c2 + (d ? 4 : 1)) % 5];
        }
        else if (c1 == c2)
        {
            ca = m[(r1 + (d ? 4 : 1)) % 5][c1];
            cb = m[(r2 + (d ? 4 : 1)) % 5][c2];
        }
        else
        {
            ca = m[r1][c2];
            cb = m[r2][c1];
        }
        o[pos++] = ca;
        o[pos++] = cb;
        if (!d && i + 2 < l)
            o[pos++] = ' ';
    }
    o[pos] = 0;
    free(pt);
    return o;
}

char *playfair_encrypt(const char *k, const char *t) { return crypt(k, t, 0); }
char *playfair_decrypt(const char *k, const char *t) { return crypt(k, t, 1); }

int main()
{
    char *encrypted, *decrypted;

    // even length of string
    encrypted = playfair_encrypt("SeCReT", "Hello world");
    printf("%s", encrypted);
    // "Hello world" --> "HELXLOVORLDX"
    // IS JZ JQ XN TK JC
    decrypted = playfair_decrypt("SeCReT", encrypted);
    printf("%s", decrypted);
    // HELXLOVORLDX
    free(encrypted);
    free(decrypted);

    // odd length of string
    encrypted = playfair_encrypt("world", "Hello");
    printf("%s", encrypted);
    // "Hello" --> "HELXLO"
    // JB RY DR
    decrypted = playfair_decrypt("world", encrypted);
    printf("%s", decrypted);
    // HELXLO
    free(encrypted);
    free(decrypted);
    return 0;
}