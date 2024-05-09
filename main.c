#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char *data;
    struct Node *prev;
    struct Node *next;
} Node;

Node *create_node(const char *data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));

    if (new_node)
    {
        new_node->data = strdup(data);
        new_node->prev = NULL;
        new_node->next = NULL;
    }

    return new_node;
}

void insert_node(Node **head, const char *data)
{
    Node *new_node = create_node(data);

    if (!(*head))
    {
        *head = new_node;
    }
    else
    {
        Node *current = *head;

        while (current->next)
        {
            current = current->next;
        }

        current->next = new_node;
        new_node->prev = current;
    }
}

Node *find_node(Node *head, const char *data)
{
    Node *current = head;

    while (current)
    {
        if (strcmp(current->data, data) == 0)
        {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void delete_node(Node **head, const char *data)
{
    Node *to_delete = find_node(*head, data);

    if (to_delete)
    {
        if (to_delete->prev)
        {
            to_delete->prev->next = to_delete->next;
        }
        else
        {
            *head = to_delete->next;
        }
        if (to_delete->next)
        {
            to_delete->next->prev = to_delete->prev;
        }

        free(to_delete->data);
        free(to_delete);
    }
}

void print_list(Node *head)
{
    Node *current = head;

    while (current)
    {
        printf("%s\n", current->data);

        current = current->next;
    }
}

void free_list(Node **head)
{
    Node *current = *head;

    while (current)
    {
        Node *next = current->next;

        free(current->data);
        free(current);

        current = next;
    }

    *head = NULL;
}

int main()
{
    Node *head = NULL;

    insert_node(&head, "Hello");
    insert_node(&head, "World");
    insert_node(&head, "Test");
    print_list(head);
    delete_node(&head, "World");
    printf("After deletion\n");
    print_list(head);
    free_list(&head);

    return 0;
}
