#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50
#define MIN_SIZE 1

// Function Prototypes
int getValidatedInput(const char *prompt, int min, int max, const char *errorMessage);
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
void PowerMatrix(int*** matrix, int* rows, int* cols, int* power) ;
void SubMatrix(int*** matrix, int* rows, int* cols);
void MatMul(int*** Mat1, int** Mat2, int* dim1, int* dim2, int* dim3) ;
void PowerMatrixWithDefault(int*** matrix, int* rows, int* cols) ;
void ValidateSubMatrixInputs(int rows, int cols, int* subRows, int* subCols, int* start_row, int* start_col) ;
void CalculateSubMatrix(int*** matrix, int* rows, int* cols, int subRows, int subCols, int start_row, int start_col);

int main(void) {
    int numberOfRows = 0;
    int numberOfColsForMat2 = 0;
    int numberOfColumns = 0;
    int userChoice = -1;
    int **matrix;
    int **mat2;

    // Get number of rows
    numberOfRows = getValidatedInput("Enter the number of rows: ", MIN_SIZE, MAX_SIZE, "Wrong number of rows, please try again.\n");

    // Get number of columns
    numberOfColumns = getValidatedInput("Enter the number of columns: ", MIN_SIZE, MAX_SIZE, "Wrong number of cols, please try again.\n");
    matrix = allocateMatrix(numberOfRows, numberOfColumns);
    SetInitalMatrix(matrix, numberOfRows, numberOfColumns);
    // Display the menu and get user choice
    while (userChoice != 0) {
        displayMenu();
        userChoice = getValidatedInput("Enter a valid value: ", 0, 9, "Wrong input, try again.\n");


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
                SortMatrixByRowSum(matrix, numberOfRows, numberOfColumns);
                break;
            case 5:
                SortMatrix(matrix, numberOfRows, numberOfColumns);
                break;
            case 6:
                PrintMatrixVal(matrix, numberOfRows, numberOfColumns);
                break;
            case 7:
                PowerMatrixWithDefault(&matrix, &numberOfRows, &numberOfColumns);
                break;
            case 8:
                 SubMatrix(&matrix,&numberOfRows,&numberOfColumns);
                break;
            case 9:
                printf("Enter columns for the second matrix: \n");
            scanf("%d", &numberOfColsForMat2);

            // הקצאת זיכרון למטריצה השנייה
            mat2 = allocateMatrix(numberOfColumns, numberOfColsForMat2);

            // אתחול המטריצה השנייה
            SetInitalMatrix(mat2, numberOfColumns, numberOfColsForMat2);

            // קלט ערכים למטריצה השנייה
            printf("Enter values for the matrix (%d * %d):\n", numberOfColumns, numberOfColsForMat2);
            SetMatrix(mat2, numberOfColumns, numberOfColsForMat2);

            // כפל המטריצות
            MatMul(&matrix, mat2, &numberOfRows, &numberOfColumns, &numberOfColsForMat2);

            // שחרור זיכרון של המטריצה השנייה
            freeMatrix(mat2, numberOfColumns);

            // עדכון גדלי המטריצה הראשית לאחר הכפל
            numberOfColumns = numberOfColsForMat2;
                break;
            case 0:
                break;
        }
    }

    return 0;
}

// Function to get validated input
int getValidatedInput(const char *prompt, int min, int max, const char *errorMessage) {
    int value;
    char buffer[100];

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &value) == 1 && value >= min && value <= max) {
                return value;
            }
        }
        printf("%s", errorMessage);
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
    for (int i = 1; i < rows; i++) {
        // חישוב סכום השורה הנוכחית
        int currentRowSum = 0;
        for (int j = 0; j < cols; j++) {
            currentRowSum += matrix[i][j];
        }

        // חישוב סכום השורה הקודמת
        int previousRowSum = 0;
        for (int j = 0; j < cols; j++) {
            previousRowSum += matrix[i - 1][j];
        }

        // השוואה והחלפה לפי הצורך
        if (currentRowSum < previousRowSum) {
            // החלפה בין השורות
            int* temp = matrix[i - 1];
            matrix[i - 1] = matrix[i];
            matrix[i] = temp;
        }
    }
}

void SortMatrix(int** matrix, int rows, int cols) {
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols - 1; j++) {
                if (matrix[i][j] > matrix[i][j + 1]) {
                    int temp = matrix[i][j];
                    matrix[i][j] = matrix[i][j + 1];
                    matrix[i][j + 1] = temp;
                    sorted = false;
                }
            }

            if (i < rows - 1 && matrix[i][cols - 1] > matrix[i + 1][0]) {
                int temp = matrix[i][cols - 1];
                matrix[i][cols - 1] = matrix[i + 1][0];
                matrix[i + 1][0] = temp;
                sorted = false;
            }
        }
    }
}

void PrintMatrixVal(int** matrix, int rows, int cols) {
    int sumProduct = 0 ;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sumProduct += matrix[i][j]*(i+1)*(j+1);
        }

    }
    printf("Matrix Value: %d\n",sumProduct);
}

void PowerMatrixWithDefault(int*** matrix, int* rows, int* cols) {
    int defaultPower = 0; // Start with default value 0 to trigger user input in PowerMatrix
    PowerMatrix(matrix, rows, cols, &defaultPower);
}


void PowerMatrix(int*** matrix, int* rows, int* cols, int* power) {
    // Check if the matrix is square
    if (*rows != *cols) {
        printf("Matrix must be square for this operation.\n");
        return;
    }

    // If power is 0, set a default value
    if (*power == 0) {
        printf("Default power set to 1.\n");
        *power = 1; // Default value
    }

    // If power was set to the default value, ask for user input
    do {
        printf("Enter the power of the matrix (current value: %d):\n", *power);
        scanf("%d", power); // Take input directly into the power pointer
        if (*power <= 0) {
            printf("The power needs to be an integer greater than 0.\n");
        }
    } while (*power <= 0);

    // Temporary matrices to store results
    int** tempMatrix = allocateMatrix(*rows, *cols);  // Temporary result
    int** originalMatrix = allocateMatrix(*rows, *cols);  // Copy of the original matrix

    // Copy the original matrix into originalMatrix
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            originalMatrix[i][j] = (*matrix)[i][j];
        }
    }

    // Compute the power
    for (int k = 1; k < *power; k++) { // Start from 1 because the original matrix is already M^1
        for (int i = 0; i < *rows; i++) {
            for (int j = 0; j < *cols; j++) {
                tempMatrix[i][j] = 0; // Initialize to 0 at each step
                for (int l = 0; l < *rows; l++) {
                    tempMatrix[i][j] += (*matrix)[i][l] * originalMatrix[l][j];
                }
            }
        }

        // Copy tempMatrix back into matrix
        for (int i = 0; i < *rows; i++) {
            for (int j = 0; j < *cols; j++) {
                (*matrix)[i][j] = tempMatrix[i][j];
            }
        }
    }

    // Free temporary matrices
    freeMatrix(tempMatrix, *rows);
    freeMatrix(originalMatrix, *rows);
}


void SubMatrix(int*** matrix, int* rows, int* cols) {
    int subRows, subCols, start_row, start_col;

    // Validate inputs
    ValidateSubMatrixInputs(*rows, *cols, &subRows, &subCols, &start_row, &start_col);

    // Calculate and extract the submatrix
    CalculateSubMatrix(matrix, rows, cols, subRows, subCols, start_row, start_col);
}



void ValidateSubMatrixInputs(int rows, int cols, int* subRows, int* subCols, int* start_row, int* start_col) {
    do {
        printf("Enter starting row index (0 to %d): \n", rows - 1);
        scanf("%d", start_row);
        printf("Enter starting column index (0 to %d): \n", cols - 1);
        scanf("%d", start_col);

        printf("Enter submatrix rows: \n");
        scanf("%d", subRows);
        printf("Enter submatrix cols: \n");
        scanf("%d", subCols);

        if (*subRows <= 0 || *subCols <= 0 || *start_row < 0 || *start_col < 0 ||
            *start_row + *subRows > rows || *start_col + *subCols > cols) {
            printf("Invalid submatrix dimensions or starting position. Try again.\n");
            }
    } while (*subRows <= 0 || *subCols <= 0 || *start_row < 0 || *start_col < 0 ||
             *start_row + *subRows > rows || *start_col + *subCols > cols);
}


void CalculateSubMatrix(int*** matrix, int* rows, int* cols, int subRows, int subCols, int start_row, int start_col) {
    // Allocate space for the submatrix
    int** tempMatrix = allocateMatrix(subRows, subCols);

    // Copy submatrix values
    for (int i = 0; i < subRows; i++) {
        for (int j = 0; j < subCols; j++) {
            tempMatrix[i][j] = (*matrix)[i + start_row][j + start_col];
        }
    }

    // Free the original matrix and update the pointer
    freeMatrix(*matrix, *rows);
    *matrix = tempMatrix;
    *rows = subRows;
    *cols = subCols;
}

void MatMul(int*** Mat1, int** Mat2, int* dim1, int* dim2, int* dim3) {
    int** tempMatrix = allocateMatrix(*dim1, *dim3);

    for (int i = 0; i < *dim1; i++) {
        for (int j = 0; j < *dim3; j++) {
            tempMatrix[i][j] = 0;
            for (int k = 0; k < *dim2; k++) {
                tempMatrix[i][j] += (*Mat1)[i][k] * Mat2[k][j];
            }
        }
    }

    // שחרור הזיכרון של המטריצה הישנה
    freeMatrix(*Mat1, *dim1);

    // עדכון Mat1 לתוצאה החדשה
    *Mat1 = tempMatrix;
}
