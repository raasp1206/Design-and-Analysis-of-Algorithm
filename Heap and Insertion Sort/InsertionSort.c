#include <stdio.h>
void insertionSort(int A[], int n) {
    int i, j, v;
    for (i = 1; i < n; i++) {
        v = A[i];
        j = i - 1;
        while (j >= 0 && A[j] > v) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = v;
    }
}
int main() {
    int n, i;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int A[n];
    printf("Enter elements:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    insertionSort(A, n);
    printf("Sorted array:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    return 0;
}
