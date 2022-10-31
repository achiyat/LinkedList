#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#pragma warning(disable:4996)
struct Item {
	int id;
	int val;
	struct Item* next;
};

struct Item* head = NULL;

void freeLinkedList()
{
	struct Item* currentItem = head;
	struct Item* releaseItem = head;
	while (currentItem != NULL)
	{
		releaseItem = currentItem;
		currentItem = currentItem->next;
		free(releaseItem);
	}
}

int main()
{

	int userResponse;

	printf("Click 1 for Add \nClick 3 for Exit\n");
	scanf("%d", &userResponse);

	struct Item* currentItem;
	struct Item* prevItem = NULL;

	while (userResponse == 1)
	{
		currentItem = (struct Item*)malloc(sizeof(struct Item));

		printf("\nid = ");
		scanf("%d", &currentItem->id);

		printf("val = ");
		scanf("%d", &currentItem->val);

		currentItem->next = NULL;

		if (head == NULL)
		{
			head = currentItem;
		}
		else
		{
			prevItem->next = currentItem;
		}

		printf("\nClick 1 for Add \nClick 3 for Exit\n");
		scanf("%d", &userResponse);

		prevItem = currentItem;
	}

	freeLinkedList();


}
