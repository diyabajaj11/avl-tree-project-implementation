#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char name[50];
    struct Node *left, *right;
    int height;
};

struct Node *create(char name[])
{
    struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
    strcpy(newnode->name, name);
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->height = 1;
    return newnode;
}

void inorder(struct Node *root)
{
    if (root != NULL)
    {

        inorder(root->left);
        printf(" %s", root->name);
        inorder(root->right);
    }
}

int get_height(struct Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return root->height;
}

int balance_factor(struct Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return get_height(root->left) - get_height(root->right);
}

struct Node *left_rotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = 1 + (get_height(x->left) > get_height(x->right) ? get_height(x->left) : get_height(x->right));
    y->height = 1 + (get_height(y->left) > get_height(y->right) ? get_height(y->left) : get_height(y->right));
    return y;
}

struct Node *right_rotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *t2 = x->right;

    x->right = y;
    y->left = t2;

    x->height = 1 + (get_height(x->left) > get_height(x->right) ? get_height(x->left) : get_height(x->right));
    y->height = 1 + (get_height(y->left) > get_height(y->right) ? get_height(y->left) : get_height(y->right));
    return x;
}

struct Node *insert(struct Node *root, char key[])
{
    if (root == NULL)
    {
        return create(key);
    }

    if (strcmp(key, root->name) < 0)
    {
        root->left = insert(root->left, key);
    }

    else if (strcmp(key, root->name) > 0)
    {
        root->right = insert(root->right, key);
    }
    else
    {
        printf("File already exists");
        return root;
    }

    root->height = 1 + (get_height(root->left) > get_height(root->right) ? get_height(root->left) : get_height(root->right));
    int bf = balance_factor(root);

    // LL
    if (bf > 1 && strcmp(key, root->left->name) < 0)
    {
        return right_rotate(root);
    }

    // RR
    if (bf < -1 && strcmp(key, root->right->name) > 0)
    {
        return left_rotate(root);
    }

    //  LR
    if (bf > 1 && strcmp(key, root->name) > 0)
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // RL
    if (bf < -1 && strcmp(key, root->name) < 0)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    return root;
}

void search(struct Node *root, char name[])
{
    if (root == NULL)
    {
        printf("not found");
        return;
    }
    if (strcmp(root->name, name) == 0)
    {
        printf("found");
        return;
    }
    else if (strcmp(root->name, name) < 0)
    {
        search(root->left, name);
    }
    else
    {
        search(root->right, name);
    }
}

int main()
{
    struct Node *root = NULL;
    int choice;
    char name[100];

    do
    {
        printf("\n--Menu--");
        printf("\n1.Insert file");
        printf("\n2.List all files");
        printf("\n3.Search a file");
        printf("\n4.Exit");

        printf("\nenter your choice:");
        scanf("%i", &choice);

        switch (choice)
        {
        case 1:
            printf("\nInsertion:");
            printf("\nenter name of file:");
            scanf("%s", name);
            root = insert(root, name);
            break;

        case 2:
            printf("\nList all files:");
            inorder(root);
            break;

        case 3:
            printf("\nSearch a file:");
            printf("enter file name to be searched:");
            scanf("%s", name);
            search(root, name);
            break;

        case 4:
            printf("exit");
            break;

        default:
            printf("\nenter valid choice");
        }
    } while (choice != 4);

    return 0;
}
