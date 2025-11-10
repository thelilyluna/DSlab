#include <stdio.h>
#include <stdlib.h>

int capacity = 5;

int* readArray(int *arr, int *n);
int* insertByPosition(int *arr, int *n, int pos, int val);
int* insertByKey(int *arr, int *n, int key, int val);
int* insertByOrder(int *arr, int *n, int val);
void display(int *arr, int n);
void deleteByPosition(int *arr, int *n, int pos);
void deleteByKey(int *arr, int *n, int key);
int searchByKey(int *arr, int n, int key);
int searchByPosition(int *arr, int n, int pos);
void reverseArray(int *arr, int n);
int* ensureCapacity(int *arr, int n);

int main() 
{
    int n = 0, choice, pos, key, val, result;
    int *arr = (int *)malloc(capacity * sizeof(int));
    if (!arr) 
    {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    do 
    {
        printf("\n===== MENU =====\n");
        printf("1. Read Array\n2. Display Array\n3. Insert by Position\n4. Delete by Position\n");
        printf("5. Insert by Key\n6. Delete by Key\n7. Insert by Order (Ascending)\n");
        printf("8. Search by Key\n9. Search by Position\n10. Reverse Array\n0. Exit\n");
        printf("=================\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                arr = readArray(arr, &n);
                break;
            case 2:
                display(arr, n);
                break;
            case 3:
                printf("Enter position and value: ");
                scanf("%d %d", &pos, &val);
                arr = insertByPosition(arr, &n, pos, val);
                break;
            case 4:
                printf("Enter position to delete: ");
                scanf("%d", &pos);
                deleteByPosition(arr, &n, pos);
                break;
            case 5:
                printf("Enter key and value to insert after key: ");
                scanf("%d %d", &key, &val);
                arr = insertByKey(arr, &n, key, val);
                break;
            case 6:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteByKey(arr, &n, key);
                break;
            case 7:
                printf("Enter value to insert in ascending order: ");
                scanf("%d", &val);
                arr = insertByOrder(arr, &n, val);
                break;
            case 8:
                printf("Enter key to search: ");
                scanf("%d", &key);
                result = searchByKey(arr, n, key);
                if (result != -1)
                    printf("Key found at position %d\n", result);
                else
                    printf("Key not found.\n");
                break;
            case 9:
                printf("Enter position to search: ");
                scanf("%d", &pos);
                result = searchByPosition(arr, n, pos);
                if (result != -1)
                    printf("Element at position %d is %d\n", pos, result);
                break;
            case 10:
                reverseArray(arr, n);
                printf("Array reversed successfully.\n");
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);
    free(arr);
    return 0;
}


// Ensure capacity
int* ensureCapacity(int *arr, int n) 
{
    if (n >= capacity) 
    {
        capacity *= 2;
        int *temp = realloc(arr, capacity * sizeof(int));
        if (!temp) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
        arr = temp;
    }
    return arr;
}

int* readArray(int *arr, int *n) 
{
    int size, val;
    *n = 0;
    printf("Enter number of elements: ");
    scanf("%d", &size);

    for (int i = 0; i < size; i++) 
    {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &val);
        arr = insertByOrder(arr, n, val);
    }
    return arr;
}

void display(int *arr, int n) 
{
    if (n == 0) 
    {
        printf("Array is empty.\n");
        return;
    }
    printf("Array elements: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int* insertByPosition(int *arr, int *n, int pos, int val) 
{
    if (pos < 1 || pos > *n + 1) 
    {
        printf("Invalid position!\n");
        return arr;
    }
    arr = ensureCapacity(arr, *n);
    for (int i = *n; i >= pos; i--)
        arr[i] = arr[i - 1];
    arr[pos - 1] = val;
    (*n)++;
    printf("Inserted %d at position %d.\n", val, pos);
    return arr;
}

void deleteByPosition(int *arr, int *n, int pos) 
{
    if (*n == 0) 
    {
        printf("Array is empty.\n");
        return;
    }
    if (pos < 1 || pos > *n) 
    {
        printf("Invalid position!\n");
        return;
    }
    printf("Deleted element: %d\n", arr[pos - 1]);
    for (int i = pos - 1; i < *n - 1; i++)
        arr[i] = arr[i + 1];
    (*n)--;
}

int* insertByKey(int *arr, int *n, int key, int val) 
{
    int i, found = 0;
    for (i = 0; i < *n; i++) 
    {
        if (arr[i] == key) 
        {
            found = 1;
            break;
        }
    }
    if (!found) 
    {
        printf("Key %d not found!\n", key);
        return arr;
    }
    arr = ensureCapacity(arr, *n);
    for (int j = *n; j > i + 1; j--)
        arr[j] = arr[j - 1];
    arr[i + 1] = val;
    (*n)++;
    printf("Inserted %d after key %d.\n", val, key);
    return arr;
}

void deleteByKey(int *arr, int *n, int key) 
{
    int i, found = 0;
    for (i = 0; i < *n; i++) 
    {
        if (arr[i] == key) {
            found = 1;
            break;
        }
    }
    if (!found) 
    {
        printf("Key %d not found!\n", key);
        return;
    }
    for (int j = i; j < *n - 1; j++)
        arr[j] = arr[j + 1];
    (*n)--;
    printf("Deleted key %d.\n", key);
}

int* insertByOrder(int *arr, int *n, int val) 
{
    arr = ensureCapacity(arr, *n);
    int i = *n - 1;
    while (i >= 0 && arr[i] > val) 
    {
        arr[i + 1] = arr[i];
        i--;
    }
    arr[i + 1] = val;
    (*n)++;
    printf("Inserted %d in ascending order.\n", val);
    display(arr, *n);
    return arr;
}

int searchByKey(int *arr, int n, int key) 
{
    for (int i = 0; i < n; i++)
        if (arr[i] == key)
            return i + 1;
    return -1;
}

int searchByPosition(int *arr, int n, int pos) 
{
    if (pos < 1 || pos > n) 
    {
        printf("Invalid position!\n");
        return -1;
    }
    return arr[pos - 1];
}

void reverseArray(int *arr, int n) 
{
    int temp;
    for (int i = 0; i < n / 2; i++) 
    {
        temp = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = temp;
    }
}
