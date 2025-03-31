#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tree 
{
    int value;
    struct Tree *left;
    struct Tree *right;
};

struct Tree *create_tree(int value) 
{
    struct Tree *tree = malloc(sizeof(struct Tree));
    tree->value = value;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

void add_value(struct Tree *tree, int value) 
{
    if (tree->value > value)
    {
        if (tree->left == NULL)
        {
            tree->left = create_tree(value);
        }
        else
        {
            add_value(tree->left, value);
        }
    }
    else
    {
        if (tree->right == NULL)
        {
            tree->right = create_tree(value);
        }
        else
        {
            add_value(tree->right, value);
        }
    }
}

void make_string(struct Tree *tree, char *str, int *pos) 
{
    if (tree == NULL)
    {
        str[(*pos)++] = 'X';
        return;
    }
    str[(*pos)++] = 'N';
    make_string(tree->left, str, pos);
    make_string(tree->right, str, pos);
}

int main() 
{
    int n, k;
    scanf("%d %d", &n, &k);

    char **strings = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        strings[i] = malloc(1000 * sizeof(char));
    }
    int unique = 0;

    for (int i = 0; i < n; i++)
    {
        struct Tree *tree = NULL;
        for (int j = 0; j < k; j++)
        {
            int value;
            scanf("%d", &value);
            if (tree == NULL)
            {
                tree = create_tree(value);
            }
            else
            {
                add_value(tree, value);
            }
        }

        char str[1000];
        int pos = 0;
        make_string(tree, str, &pos);
        str[pos] = '\0';

        int is_new = 1;
        for (int j = 0; j < unique; j++)
        {
            if (strcmp(str, strings[j]) == 0)
            {
                is_new = 0;
                break;
            }
        }
        if (is_new == 1)
        {
            strcpy(strings[unique], str);
            unique++;
        }
    }

    printf("%d\n", unique);

    for (int i = 0; i < n; i++)
    {
        free(strings[i]);
    }
    free(strings);

    return 0;
}