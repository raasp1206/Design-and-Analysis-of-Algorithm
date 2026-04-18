#include <stdio.h>
#include <stdbool.h>
#define MAX 20

int board[MAX][MAX];

void printSolution(int N) {
    static int count = 1;
    int i,j;
    printf("\nSolution %d:\n", count++);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (board[i][j])
                printf(" Q ");
            else
                printf(" . ");
        }
        printf("\n");
    }
}

bool isSafe(int row, int col, int N) {
    int i, j;

    // Check this row on left side
    for (i = 0; i < col; i++)
        if (board[row][i]) return false;

    // Check upper diagonal on left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;

    // Check lower diagonal on left side
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j]) return false;

    return true;
}

// Recursive function to solve N-Queens
bool solveNQUtil(int col, int N) {
    int i;
// Base case: If all queens are placed
    if (col >= N) {
        printSolution(N);
        return true; // Return true to find at least one solution
    }

    bool res = false;
    for (i = 0; i < N; i++) {
        if (isSafe(i, col, N)) {
            board[i][col] = 1; // Place queen

            // Recur to place rest of the queens
            res = solveNQUtil(col + 1, N) || res;

            board[i][col] = 0; // BACKTRACK
        }
    }
    return res;
}

int main() {
    int N,i,j;
    printf("Enter the number of Queens (N): ");
    scanf("%d", &N);

    if (N <= 0 || N > MAX) {
        printf("Invalid input. Please enter a number between 1 and %d.\n", MAX);
        return 0;
    }

    // Initialize board with 0
    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            board[i][j] = 0;

    if (!solveNQUtil(0, N)) {
        printf("Solution does not exist for N = %d\n", N);
    }

    return 0;
}
