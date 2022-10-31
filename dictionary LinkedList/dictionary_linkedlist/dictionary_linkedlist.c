#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable : 4996)


struct item
{
	int val;
	int key;
	struct item* prev;
	struct item* next;
};

struct item* head;
struct item* current;
struct item* tail;
struct item* find;

void additem(int key, int val);
void searchitem(int key);
void removeitem(int key);
void FreeList();
void PrintList();

int val, id, ran, num;

int main()
{
	time_t t = time();
	srand(t);

	char userResponse = '0';
	while (userResponse!='e')
	{
		printf("press 'a' to add\nclick 's' to search\nclick 'r' to remove\nclick 'p' to print the list\nclick 'e' to free all and exit\n");
		userResponse = getch();

		switch (userResponse)
		{
		case 'a':
			ran = (rand() % 100) + 1;
			id++;

			additem(id, ran);
			break;

		case 's':
			printf("\nwhich list do you want to find?\n");
			scanf("%d", &num);
			searchitem(num);

			if (find == NULL)
			{
				printf("\nNo key exists for this list!\n\n");
			}
			else //find->key == key
			{
				printf("\nkey %d -> val %d\n\n",find->key,find->val);
			}
			break; 

		case 'r': 
			printf("\nwhich list do you want to remove?\n");
			scanf("%d", &num);
			removeitem(num);
			
			break;

		case 'p':
			PrintList();
			break;

		case 'e':
			FreeList();
			userResponse = 'e';
			break;
		}
	}


    return 0;
}

void additem(int key, int val)
{
	current = (struct item*)malloc(sizeof(struct item));

	current->key = key;
	current->val = val;
	current->next = NULL;
	current->prev = NULL;

	printf("\nkey=%d,val=%d\n\n", current->key, current->val);

	if (head == NULL)
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

	return;
}

void searchitem(int key)
{
	find = head;

	while (find != NULL && find->key != key)
	{
		find = find->next;
	}
	return;
}

void removeitem(int key)
{
	searchitem(key);
	int k = find->key;
	int v = find->val;

	if (find->key == key && find->prev == NULL) // if frist list
	{
		if (find->next != NULL)
		{
			head = find->next;
			head->prev = NULL;
			free(find);
		}
		else
		{
			free(find);
			head = NULL;
		}

	}
	else if (find->key == key && find->next == NULL) // if latest list
	{
		tail = find->prev;
		tail->next = NULL;
		free(find);
	}
	else // between two numbers
	{
		//find->prve == 1
		//find->key == 2
		//find->next == 3
		find->prev->next = find->next;
		find->next->prev = find->prev;
		free(find);
	}

	printf("\nkey %d -> val %d removed from the list\n\n", k, v);

	find = head;
	id = 0;
	while (find != NULL)
	{
		id++;
		find->key = id;
		find = find->next;
	}

	return;
}

void FreeList()
{
	struct item* current = head;
	struct item* freeitem = head;

	while (current != NULL)
	{
		int k = freeitem->key;
		int v = freeitem->val;

		freeitem = current;
		current = current->next;
		free(freeitem);
		printf("\nkey %d -> val %d is free\n", k, v);
	}
	printf("\ncongratulations, all the memory is free\n\nend");
	return;
	return;
}

void PrintList()
{
	struct item* printItem = head;
	if (printItem == NULL)
	{
		printf("\nThe list is empty!\n\n");
	}
	else
	{
		printf("\nthe list:\n");
		while (printItem != NULL)
		{
			printf("key=%d,val=%d\n", printItem->key, printItem->val);
			printItem = printItem->next;
		}
		printf("\n");
	}

	return;
}