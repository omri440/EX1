#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50
#define MIN_SIZE 1

// Function Prototypes
int getValidatedInput(const char *prompt, int min, int max);
void displayMenu();
int** allocateMatrix(int rows, int cols) ;
void freeMatrix(int** matrix, int rows) ;
void PrintMat(int** matrix, int rows, int cols) ;
void SetMatrix(int** matrix, int rows, int cols);
void SetInitalMatrix(int** matrix, int rows, int cols);
void TransposeMatrix(int*** matrix, int* rows, int* cols);
void SortMatrixByRowSum(int** matrix, int rows, int cols);
void SortMatrix(int** matrix, int rows, int cols) ;
void PrintMatrixVal(int** matrix, int rows, int cols) ;
void PowerMatrix(int*** matrix, int* rows, int* cols, int power) ;
int SubMatrix(int*** matrix, int* rows, int* cols, int subRows, int subCols,int start_row,int start_col) ;
void MatMul(int*** Mat1, int** Mat2, int dim1, int* dim2, int dim3) ;

int main(void) {
    int numberOfRows = 0;
    int numberOfColumns = 0;
    int userChoice = -1;
    int **matrix;

    // Get number of rows
    numberOfRows = getValidatedInput("Insert Number Of Rows: ", MIN_SIZE, MAX_SIZE);

    // Get number of columns
    numberOfColumns = getValidatedInput("Insert Number Of Columns: ", MIN_SIZE, MAX_SIZE);
    matrix = allocateMatrix(numberOfRows, numberOfColumns);
    SetInitalMatrix(matrix, numberOfRows, numberOfColumns);
    // Display the menu and get user choice
    while (userChoice != 0) {
        displayMenu();
        userChoice = getValidatedInput("Please enter your choice: ", 0, 9);


        // Process the choice (placeholders for now)
        switch (userChoice) {
            case 1:
                PrintMat(matrix, numberOfRows, numberOfColumns);
                break;
            case 2:
                SetMatrix(matrix, numberOfRows, numberOfColumns);
                break;
            case 3:
                TransposeMatrix(&matrix, &numberOfRows, &numberOfColumns);
                break;
            case 4:
                printf("Sorting the matrix by rows sum...\n");
                break;
            case 5:
                printf("Sorting the whole matrix...\n");
                break;
            case 6:
                printf("Printing matrix value...\n");
                break;
            case 7:
                printf("Calculating i-th power of the matrix...\n");
                break;
            case 8:
                printf("Finding a sub-matrix...\n");
                break;
            case 9:
                printf("Multiplying with another matrix...\n");
                break;
            case 0:
                printf("Exiting the program. Goodbye!\n");
                break;
        }
    }

    return 0;
}

// Function to get validated input
int getValidatedInput(const char *prompt, int min, int max) {
    int value;
    char buffer[100];

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &value) == 1 && value >= min && value <= max) {
                return value;
            }
        }
        printf("Wrong input, please enter a number between %d and %d.\n", min, max);
    }
}

// Function to display the menu
void displayMenu() {
    printf("\n1. Display the matrix.\n");
    printf("2. Insert values to the matrix.\n");
    printf("3. Transpose matrix.\n");
    printf("4. Sort the matrix by rows sum.\n");
    printf("5. Sort the whole matrix.\n");
    printf("6. Print matrix value.\n");
    printf("7. i-th power of matrix.\n");
    printf("8. Find sub matrix.\n");
    printf("9. Multiply with another matrix.\n");
    printf("0. Exit.\n\n");
}


int **allocateMatrix(int rows, int columns) {
    int **matrix = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(columns * sizeof(int));
    }
    return matrix;
}

// Function to free a matrix
void freeMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void SetInitalMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }
}

void PrintMat(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void SetMatrix(int** matrix, int rows, int cols) {
    printf("Enter %d integers (separated by spaces or newlines):\n", rows * cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void TransposeMatrix(int*** matrix, int* rows, int* cols) {
    // Allocate a new transposed matrix
    int** transposed = malloc((*cols) * sizeof(int*));
    for (int i = 0; i < *cols; i++) {
        transposed[i] = malloc((*rows) * sizeof(int));
    }

    // Fill the transposed matrix
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            transposed[j][i] = (*matrix)[i][j];
        }
    }

    // Free the old matrix
    for (int i = 0; i < *rows; i++) {
        free((*matrix)[i]);
    }
    free(*matrix);

    // Update the original matrix to point to the new one
    *matrix = transposed;

    // Swap rows and cols
    int temp = *rows;
    *rows = *cols;
    *cols = temp;
}

void SortMatrixByRowSum(int** matrix, int rows, int cols) {
    int arr[rows]{0};
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i] += matrix[i][j];
        }
    }

}
