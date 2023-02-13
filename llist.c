#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "llist.h"

struct node *node_alloc(int value)
{
    struct node *n = (struct node *)malloc(sizeof(struct node));
    n->value = value;
    n->next = NULL;
    return n;
}

void node_free(struct node *n)
{
    free(n);
}

void llist_insert_head(struct node **head, struct node *n)
{
    n->next = *head;
    *head = n;
}

struct node *llist_delete_head(struct node **head)
{
    if (*head == NULL) {
        return NULL;
    }
    struct node *temp = *head;
    *head = (*head)->next;
    return temp;
}

void llist_insert_tail(struct node **head, struct node *n)
{
    if (*head == NULL) {
        *head = n;
        return;
    }

    struct node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = n;
}

void llist_print(struct node *head)
{
    if (head == NULL) {
        printf("[empty]\n");
        return;
    }

    struct node *current = head;
    while (current != NULL) {
        printf("%d", current->value);
        current = current->next;
        if (current != NULL) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void llist_free(struct node **head)
{
    struct node *current = *head;
    struct node *temp;
    while (current != NULL) {
        temp = current->next;
        node_free(current);
        current = temp;
    }
    *head = NULL;
}

int main(int argc, char *argv[]) {
    struct node *head = NULL;
    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "ih") == 0) {
            int value = atoi(argv[++i]);
            struct node *n = node_alloc(value);
            llist_insert_head(&head, n);
        } else if (strcmp(argv[i], "it") == 0) {
            int value = atoi(argv[++i]);
            struct node *n = node_alloc(value);
            llist_insert_tail(&head, n);
        } else if (strcmp(argv[i], "dh") == 0) {
            struct node *n = llist_delete_head(&head);
            if (n) {
                node_free(n);
            }
        } else if (strcmp(argv[i], "p") == 0) {
            llist_print(head);
        } else if (strcmp(argv[i], "f") == 0) {
            llist_free(&head);
        }
    }
    return 0;
}
