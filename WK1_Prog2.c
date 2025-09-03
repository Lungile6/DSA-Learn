#include<stdio.h>
#include<stdlib.h> // Required for malloc and free
struct Node{
int data;
struct Node* next;
};

// Function to insert at the end
void insertEnd(struct Node** head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to delete first occurrence of a value
void deleteNode(struct Node** head, int value) {
    struct Node* temp = *head, *prev = NULL;
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return; // Not found
    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
}

// Function to print the list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Function to update the first occurrence of oldValue to newValue
void updateItem(struct Node* head, int oldValue, int newValue) {
    while (head != NULL) {
        if (head->data == oldValue) {
            head->data = newValue;
            printf("Updated value %d to %d.\n", oldValue, newValue);
            return;
        }
        head = head->next;
    }
    printf("Value %d not found.\n", oldValue);
}

// Function to search for a value and return its position (0-based)
int searchItem(struct Node* head, int value) {
    int pos = 0;
    while (head != NULL) {
        if (head->data == value) {
            return pos;
        }
        head = head->next;
        pos++;
    }
    return -1;
}

int main(){
    struct Node* head = NULL;
    // Insert 10 elements
    for (int i = 1; i <= 10; i++) {
        insertEnd(&head, i);
    }
    printf("List after inserting 10 elements: ");
    printList(head);
    // Delete 1 element (e.g., value 5)
    deleteNode(&head, 5);
    printf("List after deleting value 5: ");
    printList(head);
    // Update value 6 to 60
    updateItem(head, 6, 60);
    printf("List after updating value 6 to 60: ");
    printList(head);
    // Search for value 7
    int pos = searchItem(head, 7);
    if (pos != -1)
        printf("Value 7 found at position %d.\n", pos);
    else
        printf("Value 7 not found.\n");
    return 0;
}