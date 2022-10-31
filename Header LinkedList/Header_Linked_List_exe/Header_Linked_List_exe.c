#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

#define file_name "data.bin"
#define Version 1;

struct item
{
    int key;
    int val;
    struct item* next;
    struct item* prev;
};

struct headerFile
{
    int version;
    //int serialNum;
    int itemCount;
    char reserve[1000];
};

struct item* head;
struct item* tail;
struct item* current;
//struct item* ret;
struct item* find;

struct headerFile headFILE;

void AddItem(int val, int key);
void PrintList();
void findItem(int key);
void deleteItem(int key);
void FreeList();
void countItem();
void save();
void read();

int ran1, id, num, num2, countOFitem;
int userResponse = 0;

int main()
{
    time_t t = time();
    srand(t);

    char userResponse = '0';
    while (userResponse != 'e')
    {
        printf("Click 'a' for Add\n");
        printf("Click 'f' for find\n");
        printf("Click 'u' for update\n");
        printf("Click 'd' for delete\n");
        printf("Click 's' for save\n");
        printf("Click 'p' for Print list\n");
        printf("Click 'e' for free all and exit\n");

        userResponse = getch();

        switch (userResponse)
        {
        case 'a':
            ran1 = (rand() % 100) + 1;
            id++;

            AddItem(ran1, id);
            break;

        case 'f':
            printf("\nwhich list do you want to find?\n");
            scanf("%d", &num);
            findItem(num);
            //PrintList();
            break;

        case 'u':
            printf("\nwhich list do you want to find?\n");
            scanf("%d", &num);
            findItem(num);
            ///  אני יכול לעשות בהמשך איף אין מספר
            printf("\nwhat value do you want to update for?\n");
            scanf("%d", &num);
            find->val = num;
            printf("%d (key %d)\n", find->val, find->key);
            break;

        case 'd':
            printf("\nwhich list do you want to delete?\n");
            scanf("%d", &num);
            deleteItem(num);
            break;

        case 's':
            countItem();
            save();
            read();
            break;

        case 'p':
            PrintList();
            break;

        case 'e':
            FreeList();
            printf("\nend\n");
            break;
        }
    }


    return 0;
}

void AddItem(int val, int key)
{
    current = (struct item*)malloc(sizeof(struct item));

    current->key = key;
    current->val = val;
    current->next = NULL;
    current->prev = NULL;

    printf("\nval=%d,key=%d\n\n", current->val, current->key);

    if (head==NULL)
    {
        head = current;
        tail = current;
    }
    else
    {
        current->prev = tail;
        tail->next = current;
        tail = current;
    }

    return current;

}

void findItem(int key)
{
    find = head;

    while (find != NULL && find->key != key)
    {
        find = find->next;
    }
    
    if (find == NULL)
    {
        printf("\n***\n\n");
    }
    else if (find->key == key && userResponse == 2)
    {
        printf("\n%d (%d)\n\n", find->val, find->key);
    }
    /*
    else
    {
        find = head;
        while (find->key != key)
        {
            find = find->next;
        }

        return;
    }
    */
    
    return;
}

void PrintList()
{
    struct item* print = head;

    if (print == NULL)
    {
        printf("\n***\n\n");
    }
    else
    {
        printf("\n");
        while (print != NULL)
        {
            printf("%d (key %d)\n", print->val, print->key);
            print = print->next;
        }
        printf("\n");
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
    //head = current;
    //iD_COUNTER = 0;
    printf("\ncongratulations, the memory of all list is free\n");
    return;
}

void deleteItem(int key)
{
    struct item* del = head;

    while (del != NULL && del->key != key)
    {
        del = del->next;
    }

    //del = head;
    if (del->prev == NULL && del->key == key) // המספר הראשון
    {
        head = del->next;
        head->prev = NULL;
        free(del);

        /*
        current = del;
        current = current->next;
        current->prev = NULL;
        free(del);
        del = current;
        head = current;
        */

    }
    else if (del->next == NULL && del->key == key)  // המספר האחרון
    {
        tail = del->prev;
        tail->next = NULL;
        free(del);

        /*
        tail = del;
        tail = del->prev;
        tail->next = NULL;
        free(del);
        del = tail;
        */
    }
    else 
    {
        del->prev->next = del->next;
        del->next->prev = del->prev;
        free(del);

        /*
        current = del;
        current->next = tail;
        current = head;
        del = del->next;
        free(del);
        del = current;
        */
    }

    // מסדר את המפתח
    del = head;
    id = 0;
    
    while (del != NULL)
    {
        id++;
        del->key = id;
        del = del->next;
    }

    //current = tail;

    //PrintList();

}

void countItem()
{
    struct item* count = head;

    countOFitem = 0;

    while (count != NULL)
    {
        countOFitem++;
        count = count->next;
    }
}

void save()
{
    headFILE.version = Version;
    headFILE.itemCount = countOFitem;

    FILE* f = fopen(file_name, "wb");
    if (!f)
    {
        printf("The file did not open");
        exit(1);
    }
    else
    {
        fwrite(&headFILE, sizeof(struct headerFile), 1, f);

        struct item* currentOFsave = head;
        while (currentOFsave != NULL)
        {
            fwrite(currentOFsave, sizeof(struct item), 1, f);
            currentOFsave = currentOFsave->next;
        }

        fclose(f);
    }
    
}

void read()
{
    FILE* f1 = fopen(file_name, "rb");
    if (!f1)
    {
        printf("The file did not open");
        exit(1);
    }
    else
    {
        FreeList();
        head = NULL;
        tail = NULL;
        struct item* currentOFread;
        struct headerFile headOFfile;

        currentOFread = (struct item*)malloc(sizeof(struct item));

        int read = fread(&headOFfile, sizeof(struct headerFile), 1, f1);

        for (int i = 0; i < headOFfile.itemCount; i++)
        {
            read = fread(currentOFread, sizeof(struct item), 1, f1);

            AddItem(currentOFread->val, currentOFread->key);
            //printf("%d,%d", currentOFread->val, currentOFread->key);
        }

        free(currentOFread);
        fclose(f1);
    }
    
}
