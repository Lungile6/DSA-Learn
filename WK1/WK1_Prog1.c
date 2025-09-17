#include <stdio.h>

#define SIZE 100

// Function declarations
void insertItem(int arr[], int *length, int value, int position);
void deleteItem(int arr[], int *length, int position);
void updateItem(int arr[], int length, int position, int newValue);
int searchItem(int arr[], int length, int value);
void displayArray(int arr[], int length);

// Function definitions
void insertItem(int arr[], int *length, int value, int position) {
    if (*length >= SIZE) {
        printf("Array is full. Cannot insert new item.\n");
        return;
    }
    if (position < 0 || position > *length) {
        printf("Invalid position. Must be between 0 and %d.\n", *length);
        return;
    }

    // Shift elements to the right
    for (int i = *length; i > position; i--) {
        arr[i] = arr[i - 1];
    }

    // Insert the new value
    arr[position] = value;
    (*length)++;

    printf("Item %d inserted at position %d.\n", value, position);
    displayArray(arr, *length);
}

void deleteItem(int arr[], int *length, int position) {
    if (*length <= 0) {
        printf("Array is empty. Nothing to delete.\n");
        return;
    }
    if (position < 0 || position >= *length) {
        printf("Invalid position. Must be between 0 and %d.\n", *length - 1);
        return;
    }

    // Shift elements to the left
    for (int i = position; i < *length - 1; i++) {
        arr[i] = arr[i + 1];
    }

    (*length)--;

    printf("Item at position %d deleted.\n", position);
    displayArray(arr, *length);
}

void updateItem(int arr[], int length, int position, int newValue) {
    if (position < 0 || position >= length) {
        printf("Invalid position. Must be between 0 and %d.\n", length - 1);
        return;
    }
    arr[position] = newValue;
    printf("Item at position %d updated to %d.\n", position, newValue);
    displayArray(arr, length);
}

int searchItem(int arr[], int length, int value) {
    for (int i = 0; i < length; i++) {
        if (arr[i] == value)
            return i;
    }
    return -1; // not found
}

void displayArray(int arr[], int length) {
    if (length == 0) {
        printf("Array is empty.\n");
        return;
    }
    printf("Current Array: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[SIZE];
    int length = 0; // current number of elements
    int choice, value, position, newValue;

    while (1) {
        printf("\nArray Operations Menu:\n");
        printf("1. Insert (multiple)\n");
        printf("2. Delete\n");
        printf("3. Update\n");
        printf("4. Search\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int count;
                printf("How many items do you want to insert? ");
                scanf("%d", &count);

                for (int i = 0; i < count; i++) {
                    printf("Enter value to insert: ");
                    scanf("%d", &value);
                    printf("Enter position (0 to %d): ", length);
                    scanf("%d", &position);
                    insertItem(arr, &length, value, position);
                }
                break;
            }

            case 2:
                printf("Enter position to delete (0 to %d): ", length - 1);
                scanf("%d", &position);
                deleteItem(arr, &length, position);
                break;

            case 3:
                printf("Enter position to update (0 to %d): ", length - 1);
                scanf("%d", &position);
                printf("Enter new value: ");
                scanf("%d", &newValue);
                updateItem(arr, length, position, newValue);
                break;

            case 4:
                printf("Enter value to search: ");
                scanf("%d", &value);
                position = searchItem(arr, length, value);
                if (position != -1)
                    printf("Item found at position %d.\n", position);
                else
                    printf("Item not found.\n");
                break;

            case 0:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
