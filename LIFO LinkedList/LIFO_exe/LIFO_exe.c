#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)


struct item
{
    int val1;
    int val2;
    int id;
    struct item* next;
    struct item* prev;
};

struct item* head;
struct item* tail;
struct item* current;
struct item* old;

int num, ran1, ran2;
int iD_COUNTER = 0;
char userResponse = '0';

void Push(int val1, int val2);
void PrintList();
void pop();
void FreeList();
void Bulk_insert();
void Bulk_remove();

int main()
{
    time_t t = time();
    srand(t);

    while (userResponse != 'e')
    {
        printf("Click 'a' for Add\nClick 'p' for Print all List\nClick 'f' for free head\nClick 'b' for Bulk insert of 100\nClick 'r' for Bulk remove of 10\nClick 'e' for free all and exit\n");
        userResponse = getch();

        switch (userResponse)
        {
        case 'a':
            ran1 = (rand() % 100) + 1;
            ran2 = (rand() % 100) + 1;

            Push(ran1, ran2);
            break;

        case 'p':
            PrintList();
            break;

        case 'f':
            pop();
            break;

        case 'b':
            Bulk_insert();
            break;

        case 'r':
            Bulk_remove();
            break;

        case 'e':
            FreeList();
            printf("\nend\n");
            break;
        }
    }


    return 0;
}

void Push(int val1, int val2)
{
    current = (struct item*)malloc(sizeof(struct item));

    iD_COUNTER++;

    current->val1 = ran1;
    current->val2 = ran2;
    current->id = iD_COUNTER;

    if (userResponse == 'a')
    {
        printf("\nval1=%d,val2=%d,id=%d\n\n", current->val1, current->val2, current->id);
    }
    else
    {
        printf("\nid=%d (val1=%d,val2=%d)", current->id, current->val1, current->val2);
    }
    

    if (head == NULL)
    {
        head = current;
        tail = current;
        current->next = NULL;
        current->prev = NULL;
    }
    else
    {
        /* דוחף מספרים חדשים לראש */
        head = current;
        current->prev = NULL;
        current->next = old;
        old->prev = current;
    }
    old = current;

}

void PrintList()
{
    struct item* print = head;

    if (print == NULL)
    {
        printf("\nthe memory is empty\n\n");
    }
    else
    {
        printf("\n");
        while (print != NULL)
        {
            printf("%d (%d,%d)\n", print->id, print->val1, print->val2);
            print = print->next;
        }
        printf("\n");
    }
    return;
}

void pop()
{
    struct item* current = head;
    struct item* pop = head;

    int index;
    if (iD_COUNTER == 0)
    {
        printf("\nthe memory is empty\n\n");
    }
    else if (iD_COUNTER!=1)
    {
        pop = current;
        num = pop->val1 + pop->val2;
        index = pop->id;
        current = current->next;
        free(pop);
        current->prev = NULL;
        pop = current;
        iD_COUNTER--;
    }
    else // iD_COUNTER == 1
    {
        pop = current;
        num = pop->val1 + pop->val2;
        index = pop->id;
        current = current->next;
        free(pop);
        pop = current;
        iD_COUNTER--;
    }

    head = pop;

    if (userResponse == 'f')
    {
        printf("\ncongratulations, the memory of tail list is free\n\n");
        PrintList();
    }
    else if (iD_COUNTER != 0)
    {
        printf("\nthe memory of tail list is free (index: %d)\n", index);
    }
    
    return;
}

void FreeList()
{
    struct item* current = head;
    struct item* freeitem = head;
    while (current != NULL)
    {
        freeitem = current;
        current = current->next;
        free(freeitem);
        head = current;
        PrintList();
    }

    iD_COUNTER = 0;
    printf("\ncongratulations, the memory of all list is free\n");
    return;
}

void Bulk_insert()
{
    for (int i = 1; i <= 100; i++)
    {
        ran1 = (rand() % 100) + 1;
        ran2 = (rand() % 100) + 1;

        Push(ran1, ran2);
        
    }
    printf("\n\n");
}

void Bulk_remove()
{
    int sum = 0;

    for (int i = 1; i <= 10; i++)
    {
        if (iD_COUNTER != 0)
        {
            pop();
            sum = sum + num;
        }
    }

    printf("The sum of the values removed: %d\n\n", sum);
}