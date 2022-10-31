#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable : 4996)


struct item
{
    int id;
    int val;
    struct item* prev;
    struct item* next;
};

struct item* head = NULL;
struct item* tail = NULL;
struct item* current;

int num;

void addXList(num);
void freeLinkedList();

int main()
{
    printf("\nhow many lists do you want to open? \nyour answer:");
    scanf("%d", &num);

    addXList(num);

    FILE* f = fopen("samples.data", "w");
    if (!f)
    {
        printf("error in Save_in_File - The file did not open");
        exit(1);
    }

    current = head;
    while (!current)
    {
        fwrite(current, sizeof(struct item), 1, f);
        current = current->next;
    }
    
    fclose(f);
    freeLinkedList();
    return 0;
}

void addXList(num)
{
    for (int i = 1; i <= num; i++)
    {
        current = (struct item*)malloc(sizeof(struct item));

        current->id = i;
        current->val = (rand() % 100) + 1;
        current->next = NULL;
        current->prev = NULL;

        if (head == NULL)
        {
            head = current;
            tail = current;
        }
        else
        {
            tail->next = current;
            current->prev = tail;
            tail = current;
        }
    }

    return;
}

void freeLinkedList()
{
    struct item* currentItem = head;
    struct item* releaseItem = head;
    while (currentItem != NULL)
    {
        releaseItem = currentItem;
        currentItem = currentItem->next;
        free(releaseItem);
        head = currentItem;
    }
}