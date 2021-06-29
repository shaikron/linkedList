
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

struct listnode
{
  struct listnode *next;
  struct listnode *prev;
  int data;
};

struct list
{
  struct listnode *head;
  struct listnode *tail;
  uint32_t count;
};

struct list *list_l;

int put (char *input) {
    struct listnode *node;

    if ( (!list_l) || (!input) )
      return -1;

    node = malloc(sizeof (struct listnode));
    if ( !node )
      return -1;

    node->prev = list_l->tail;
    node->data = atoi(input);

    if (list_l->head == NULL)
        list_l->head = node;
    else
        list_l->tail->next = node;
    list_l->tail = node;

    list_l->count++;

    return 0;
}

int get (char *input) {
    struct listnode *node = NULL;
    uint32_t count = 1, i;

    if (!list_l)
        return -1;

    i = atoi(input);

    for (node = list_l->head; node; node = node->next) {
        if (i == count) {
            printf("%d\n", node->data);
            return 0;
        }
        count++;
    }

    return -1;
}

int list () {
    struct listnode *node = NULL;

    if (!list_l)
        return -1;

    for (node = list_l->head; node; node = node->next) {
        printf("%d", node->data);
        if (node->next != NULL)
            printf(" ");
    }
    printf("\n");

    return 0;
}

int remove_entry (char *input) {
    struct listnode *node = NULL;
    uint32_t count = 1, i;

    if (!list_l)
        return -1;

    i = atoi(input);

    for (node = list_l->head; node; node = node->next) {
        if (i == count) {
            printf("%d\n", node->data);
            if (node->prev)
              node->prev->next = node->next;
            else
                list_l->head = node->next;

            if (node->next)
              node->next->prev = node->prev;
            else
                list_l->tail = node->prev;

            list_l->count--;

            free(node);
            list();
            return 0;
        }
        count++;
    }

    return -1;
}

int clear () {
    struct listnode *node = NULL;

    if (!list_l)
        return -1;

    for (node = list_l->head; node; node = node->next) {
            if (node->prev)
              node->prev->next = node->next;
            else
                list_l->head = node->next;

            if (node->next)
              node->next->prev = node->prev;
            else
                list_l->tail = node->prev;

            list_l->count--;

            free(node);
    }

    return 0;
}

int first () {
    if ((!list_l) || (!list_l->head))
        return -1;

    printf("%d\n", list_l->head->data);

    return 0;
}

int last () {
    if ((!list_l) || (!list_l->tail))
        return -1;

    printf("%d\n", list_l->tail->data);

    return 0;
}

int sort () {
    int swapped, temp;
    struct listnode *node1 = NULL;
    struct listnode *node2 = NULL;

    if (!list_l)
        return -1;

    do {
        swapped = 0;
        node1 = list_l->head;

        while (node1->next != node2)
        {
            if (node1->data > node1->next->data)
            {
                temp = node1->data;
                node1->data = node1->next->data;
                node1->next->data = temp;
                swapped = 1;
            }
            node1 = node1->next;
        }
        node2 = node1;
    }
    while (swapped);

    return 0;
}

void inputClean(char *input, size_t n)
{
    memmove(input, input+n, strlen(input));
    input[strlen(input)-1] = '\0';
}

int main(int argc, char *argv[]) {
    char input[201];
    uint8_t ret;

    list_l = malloc(sizeof (struct list));

    while(1) {
        printf("prompt> ");
        if (fgets(input, 200, stdin) == NULL) {
            printf("An error ocurred.\n");
            break;
        }

        if (strncmp(input, "put ", 4) == 0) {
            inputClean(input, 4);
            ret = put(input);
            if (ret != 0)
                printf("put FAIL\n");
        }

        if (strncmp(input, "get ", 4) == 0) {
            inputClean(input, 4);
            ret = get(input);
            if (ret != 0)
                printf("get FAIL\n");
        }

        if (strncmp(input, "list", 4) == 0) {
            ret = list();
            if (ret != 0)
                printf("list FAIL\n");
        }

        if (strncmp(input, "remove ", 7) == 0) {
            inputClean(input, 7);
            ret = remove_entry(input);
            if (ret != 0)
                printf("remove FAIL\n");
        }

        if (strncmp(input, "clear", 5) == 0) {
            ret = clear();
            if (ret != 0)
                printf("clear FAIL\n");
        }

        if (strncmp(input, "first", 5) == 0) {
            ret = first();
            if (ret != 0)
                printf("first FAIL\n");
        }

        if (strncmp(input, "last", 4) == 0) {
            ret = last();
            if (ret != 0)
                printf("last FAIL\n");
        }

        if (strncmp(input, "sort", 4) == 0) {
            ret = sort();
            if (ret != 0)
                printf("sort FAIL\n");
        }

        if (strncmp(input, "exit\n", 5) == 0) {
            printf("Leaving. Good bye.\n");
            break;
        }

    }


    return EXIT_SUCCESS;
}
