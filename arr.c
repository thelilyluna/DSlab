/* Write a program to create an array of integers and perform the following operations 
by writing function for each operation which takes pointer to array as parameter.
i) READ : To read the array elements ii) WRITE: To Display the array elements
iii) CHECK: To check whether all values in the array are positive or not and to return 1 if all are positive and 0
otherwise.
iv) SEARCHINSERT: To Search for a key value and insert to the beginning of the array 
if searching value does not exist in the array and a suitable message if already exists. 
(Create a pointer to this function and call this function using pointer). 
Assume each value exists only once. */

#include <stdio.h>

#define MAX 10

void READ(int *arr, int *n);
void WRITE(int *arr, int n);
int CHECK(int *arr, int n);
void SEARCHINSERT(int *arr, int *n, int key);

int main() 
{
    int arr[MAX];
    int n;
    int key;
    int *ptr = arr; // Pointer to the array
    READ(ptr, &n);
    printf("Array elements: ");
    WRITE(ptr, n);
    if (CHECK(ptr, n))
        printf("All elements are positive.\n");
    else
        printf("Not all elements are positive.\n");

    // Search and insert using function pointer
    void (*searchInsertPtr)(int *, int *, int) = SEARCHINSERT;
    printf("Enter a key to search/insert: ");
    scanf("%d", &key);
    searchInsertPtr(ptr, &n, key);

    printf("Array after operation: ");
    WRITE(ptr, n);
    return 0;
}

void READ(int *arr, int *n) 
{
    printf("Enter number of elements: ");
    scanf("%d", n);
    printf("Enter %d elements: ", *n);
    for (int i = 0; i < *n; i++) 
        scanf("%d", arr + i);
}

void WRITE(int *arr, int n) 
{
    for (int i = 0; i < n; i++) 
        printf("%d ", *(arr + i));
    printf("\n");
}

int CHECK(int *arr, int n) 
{
    for (int i = 0; i < n; i++) 
    {
        if (*(arr + i) <= 0) //0 is neither negative nor positive
            return 0;
    }
    return 1;  
}

void SEARCHINSERT(int *arr, int *n, int key) 
{
    for (int i = 0; i < *n; i++) 
    {
        if (*(arr + i) == key) 
        {
            printf("Key %d already exists in the array.\n", key);
            return;
        }
    }
    for (int i = *n; i > 0; i--) 
        *(arr + i) = *(arr + i - 1);
    *(arr) = key;
    (*n)++;  
    printf("Key %d inserted at the beginning.\n", key);
}
