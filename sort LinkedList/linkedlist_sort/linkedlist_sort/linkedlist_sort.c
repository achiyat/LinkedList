#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

struct item
{
    int val;
    struct item* next;
    struct item* prev;
};

int num, val, oldVal, newVal, ranNum;
int countlist = 0;

void GenerateXList(num);
void PrintList();
void FreeList();
void FindVal(val);
void ChangeVal(oldVal, newVal);
void random();
void NotDyugihuplicate();
void sort();
void midel();


struct item* head = NULL;
struct item* tail;
struct item* current;
struct item* old;


int main()
{
    //  מריץ את הפונקציה של המספרים  הרנדומליים 
    time_t t = time();
    srand(t);


    /* תרגיל 3 */
    printf("\nhow many lists do you want to open? \nyour answer:");
    scanf("%d", &num);
    sort();


    /* תרגיל 3 */
    FreeList();

    return 0;
}

void sort()
{
    for (int i = 1; i <= num; i++)
    {
        current = (struct item*)malloc(sizeof(struct item));
        random();
        countlist++;
        current->val = ranNum;
        
        //printf("\n\nprint a numbers\n");
        printf("%d,", current->val);

        if (head == NULL)
        {
            head = current;
            tail = current;
            current->next = NULL;
            current->prev = NULL;
        }
        else if (ranNum < head->val) // אם זה נמוך
        {
            current->next = head;
            current->prev = NULL;
            current->val = ranNum;
            head->prev = current;
            head = current;
        }
        else if (ranNum > tail->val)
        {
            current->next = NULL;
            current->prev = tail;
            current->val = ranNum;
            tail->next = current;
            tail = current;
        }
        else
        {
            midel();
        }
    }

    printf("\nprint a numbers\n");
    PrintList();

    return;

}

void midel()
{
    struct item* midel=head;

    while (midel != NULL)
    {
        if (ranNum < midel->val)
        {
            current->val = ranNum;
            current->next = midel;  // נקסט מחפש כתובת
            current->prev = midel->prev;
            midel->prev = current;
            current->prev->next = current;
            return;
        }
        midel = midel->next;
    }

}

void random()
{
    struct item* ran = head;

    ranNum = (rand() % 100) + 1;
    int b = ranNum;
    int a = 1;
    
    if (ran == NULL)
    {
        return ranNum;
    }
    else
    {
        while (a == 1)
        {
            ran = head;
            a = 0;
            while (ran->val != ranNum && ran->next != NULL)
            {
                ran = ran->next;
            }

            if (ran->val == ranNum)
            {
                a = 1;
                ranNum = (rand() % 100) + 1;
                b = ranNum;
            }
        }
        return ranNum;
    }
}

void PrintList()
{
    struct item* print = head;
    while (print != NULL)
    {
        printf("%d\n", print->val);
        print = print->next;
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
    }
    printf("\ncongratulations, the memory is free");
    return;
}