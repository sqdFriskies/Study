#include <stdio.h>
#include <stdbool.h>
struct Tree
{
    int value; 
    struct Tree *left;
    struct Tree *right;
};

struct Tree *create_root_tree(int value)
{
 struct Tree *tree = malloc();

 tree->value = value;
 tree->left = NULL;
 tree->right = NULL;

 return tree;
}

void insert(struct Tree *tree, int value)
{
    const bool add_to_left = tree->value > value;
    struct Tree *tree_to_add = add_to_left ? tree->left : tree->right;
    if(tree_to_add == NULL)
    {
        tree_to_add = create_root_tree(value);
        if(add_to_left)
        {
            tree->left=tree_to_add;
        }
        else
        {
            tree->right=tree_to_add;
        }
    }
    else
    {
        insert(tree_to_add,value);
    }
    
}
// cout the tree, create a function create_tree(full tree) like the fn insert
int main()
{
    
    return 0;
}