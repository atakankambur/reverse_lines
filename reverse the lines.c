#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
	char line[100];
	struct listnode* nextptr;
};

struct StackNode {
	char line[100];
	struct stacknode* nextptr;
};

void push(struct StackNode** tPtr, char str[]);
char pop(struct StackNode** tPtr);
void insert(struct ListNode** sPtr, char lin[]);
char delete_node(struct ListNode** sPtr);
void file_to_list(FILE* fileread_ptr,struct ListNode** linkPtr);
void list_to_stack(struct ListNode** listPtr,struct StackNode** stackPtr);
void stack_to_list(struct StackNode** stackPtr,struct ListNode** listPtr);
void list_to_file(FILE* filewrite_ptr,struct ListNode** listPtr);



int main() {

	FILE* fileread_ptr, * filewrite_ptr;

  struct ListNode* startptr = NULL;
	struct StackNode* topptr = NULL;

	char fileread_name[20], filewrite_name[20];

	printf("Please enter name of the file to be read:");
	fgets(fileread_name, 20, stdin);
	printf("Please enter name of the file to be written:");
	fgets(filewrite_name, 20, stdin);

	if ((fileread_ptr = fopen(fileread_name, "r")) == NULL)
		printf("Error.\n");
	if ((filewrite_ptr = fopen(filewrite_name, "w")) == NULL)
		printf("Error.\n");
	else {

		file_to_list(fileread_ptr, &startptr);
		list_to_stack(&startptr, &topptr);
		stack_to_list(&topptr, &startptr);
		list_to_file(filewrite_ptr, &startptr);
		printf("Complete.");

	}

	return 0;
}

void push(struct StackNode** tPtr, char str[]) {
	struct StackNode* newPtr = (struct StackNode*)malloc(sizeof(struct StackNode));

	if (newPtr != NULL) {
		strcpy(newPtr->line, str);
		newPtr->nextptr = *tPtr;
		*tPtr = newPtr;
	}
	else {
		printf("Allocation error.");
	}
}

char pop(struct StackNode** tPtr) {
	struct StackNode* tempPtr = *tPtr;
	char ln[100];
	strcpy(ln, (*tPtr)->line);
	*tPtr = (*tPtr)->nextptr;

	free(tempPtr);
	return *ln;
}

void insert(struct ListNode** sPtr, char lin[]) {
	struct ListNode* newPtr = (struct ListNode*)malloc(sizeof(struct ListNode));
	struct ListNode* lastptr = *sPtr;

	strcpy(newPtr->line, lin);
	newPtr->nextptr = NULL;

	if (*sPtr == NULL) {
		*sPtr = newPtr;
		return;
	}

	while (lastptr->nextptr != NULL) {
		lastptr = lastptr->nextptr;
	}
	lastptr->nextptr = newPtr;

}

char delete_node(struct ListNode** sPtr) {
	struct ListNode* tempPtr = *sPtr;
	char ln[100];
	strcpy(ln, (*sPtr)->line);
	*sPtr = (*sPtr)->nextptr;

	free(tempPtr);
	return *ln;
}

void file_to_list(FILE* fileread_ptr,struct ListNode** linkPtr) {
	char line_from_file[100];
	while (1) {
		if (feof(fileread_ptr))
			break;
		fgets(line_from_file, 100, fileread_ptr);
		insert(linkPtr, line_from_file);
	}
}

void list_to_stack(struct ListNode** listPtr,struct StackNode** stackPtr) {
	while (listPtr != NULL) {
		push(stackPtr, (*listPtr)->line);
		delete_node(listPtr);
	}
}

void stack_to_list(struct StackNode** stackPtr,struct ListNode** listPtr) {
	while (stackPtr != NULL) {
		insert(listPtr, (*stackPtr)->line);
		pop(stackPtr);
	}
}
void list_to_file(FILE* filewrite_ptr,struct ListNode** listPtr) {
	char str[100];
	while (1) {
		if (listPtr == NULL)
			break;
		fprintf(filewrite_ptr, "%s", delete_node(listPtr));
	}
}