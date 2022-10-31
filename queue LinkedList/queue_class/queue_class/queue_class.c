#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

/*
fifo - first in frist out

    2 8 9 5
enQueue -> inserting node to the queue
deQueue -> poping node out of the queue

we have an empty queue!
enQueue(2); //2
enQueue(8); //2 8
enQueue(9); //2 8 9
deQueue(); // getting 2 back // 8 9
deQueue(); // getting 8 back // 9
enQueue(1); //9 1
    
*/

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


int iD_COUNTER = 0;

int num, ran1, ran2;

void Push(int val1, int val2);
void PrintList();
void pop();
void FreeList();

int main()
{
    time_t t = time();
    srand(t);

    int userResponse = 0;
    while (userResponse != 4)
    {
        printf("Click 1 for Add\nClick 2 for Print all List\nClick 3 for free head\nClick 4 for free all and exit\n");
        scanf("%d", &userResponse);

        if (userResponse == 1)
        {
            ran1 = (rand() % 100) + 1;
            ran2 = (rand() % 100) + 1;

            Push(ran1, ran2);
        }
        else if (userResponse == 2)
        {
            PrintList();
        }
        else if (userResponse == 3)
        {
            pop();
        }
        else if (userResponse == 4)
        {
            FreeList();
            printf("\nend\n");
        }
        else
        {
            printf("\nerror - Click number 1-4\n\n");
        }
        /*
        while (userResponse > 0 && userResponse < 6)
        {
            
        } */
    }
    

    return 0;
}

void Push(int val1, int val2)
{
    current = (struct item*)malloc(sizeof(struct item));
    // למחוק
    //int ran1 = (rand() % 100) + 1;
    //int ran2 = (rand() % 100) + 1;
    //
    iD_COUNTER++;

    current->val1 = ran1;
    current->val2 = ran2;
    current->id = iD_COUNTER;

    printf("\nval1=%d,val2=%d,id=%d\n\n", current->val1, current->val2, current->id);

    if (head==NULL)
    {
        head = current;
        tail = current;
        current->next = NULL;
        current->prev = NULL;
    }
    else
    {
        /* דוחף מספרים חדשים לזנב */
        tail = current;
        current->prev = old;
        current->next = NULL;
        old->next = current;
    }
    old = current;


}

void PrintList()
{
    struct item* print=head;

    if (print == NULL)
    {
        printf("\nthe memory is empty\n\n");
    }
    else
    {
        printf("\n");
        while (print != NULL)
        {
            printf("%d (%d,%d) \n", print->id, print->val1, print->val2);
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

    if (iD_COUNTER == 0)
    {
        printf("\nthe memory is empty\n\n");
    }
    else if (iD_COUNTER == 1)
    {
        pop = current;
        current = current->next;
        free(pop);
        pop = current;
    }
    else
    {
        pop = current;
        current = current->next;
        free(pop);
        current->prev = NULL;
        pop = current;
    }



    iD_COUNTER = 0;
    while (current != NULL)
    {
        iD_COUNTER++;
        current->id = iD_COUNTER;
        current = current->next;
    }

    head = pop;
    printf("\ncongratulations, the memory of head list is free\n\n");
    PrintList();
    return;
}

void FreeList()
{
    struct item* current = head;
    struct item* freeitem = head;
    while (current != NULL)
    {
        current = current->next;
        free(freeitem);
        head = current;
        PrintList();
        freeitem = current;
    }
    //head = current;
    iD_COUNTER = 0;
    printf("\ncongratulations, the memory of all list is free\n");
    return;
}