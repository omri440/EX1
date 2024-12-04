#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50
#define MIN_SIZE 1

// Function Prototypes
int getValidatedInput(const char *prompt, int min, int max, const char *errorMessage);
int getValidatedColumns(const char *prompt, int min, int max, const char *errorMessage);
void displayMenu();
long** allocateMatrix(int rows, int cols);
void freeMatrix(long** matrix, int rows);
void PrintMat(long** matrix, int rows, int cols);
void SetMatrix(long** matrix, int rows, int cols);
void SetInitalMatrix(long** matrix, int rows, int cols);
void TransposeMatrix(long*** matrix, int* rows, int* cols);
void SortMatrixByRowSum(long** matrix, int rows, int cols);
void SortMatrix(long** matrix, int rows, int cols);
void PrintMatrixVal(long** matrix, int rows, int cols);
void PowerMatrix(long*** matrix, int* rows, int* cols, int* power);
void SubMatrix(long*** matrix, int* rows, int* cols);
void MatMul(long*** Mat1, long** Mat2, int* dim1, int* dim2, int* dim3);
void PowerMatrixWithDefault(long*** matrix, int* rows, int* cols, bool* shouldClearBuffer);
void ValidateSubMatrixInputs(int rows, int cols, int* subRows, int* subCols, int* start_row, int* start_col);
void CalculateSubMatrix(long*** matrix, int* rows, int* cols, int subRows, int subCols, int start_row, int start_col);

int main(void) {
    int numberOfRows = 0;
    int numberOfColsForMat2 = 0;
    int numberOfColumns = 0;
    int userChoice = -1;
    long **matrix;
    long **mat2;
    bool shouldClearBuffer = false;
    // Get number of rows
    numberOfRows = getValidatedColumns("Insert number of rows", MIN_SIZE, MAX_SIZE, "Wrong number of rows, please try again.\n");

    // Get number of columns
    numberOfColumns = getValidatedColumns("Insert number of columns", MIN_SIZE, MAX_SIZE, "Wrong number of cols, please try again.\n");
    matrix = allocateMatrix(numberOfRows, numberOfColumns);
    SetInitalMatrix(matrix, numberOfRows, numberOfColumns);
    // Display the menu and get user choice
    while (userChoice != 0) {

        userChoice = getValidatedInput("Please enter your choice:", 0, 9, "Invalid choice. Try again.\n");


        // Process the choice (placeholders for now)
        switch (userChoice) {
            case 1:
                PrintMat(matrix, numberOfRows, numberOfColumns);
                break;
            case 2:
                SetMatrix(matrix, numberOfRows, numberOfColumns);
                while (getchar() != '\n');
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
                PowerMatrixWithDefault(&matrix, &numberOfRows, &numberOfColumns, &shouldClearBuffer);
            if (shouldClearBuffer) {
                while (getchar() != '\n'); // Clear buffer only if operation succeeded
            }

                break;
            case 8:
                 SubMatrix(&matrix,&numberOfRows,&numberOfColumns);
                while (getchar() != '\n');
                break;
            case 9:
                printf("Enter columns for the second matrix: ");
            scanf("%d", &numberOfColsForMat2);

            // הקצאת זיכרון למטריצה השנייה
            mat2 = allocateMatrix(numberOfColumns, numberOfColsForMat2);

            // אתחול המטריצה השנייה
            SetInitalMatrix(mat2, numberOfColumns, numberOfColsForMat2);

            // קלט ערכים למטריצה השנייה
            SetMatrix(mat2, numberOfColumns, numberOfColsForMat2);

            // כפל המטריצות
            MatMul(&matrix, mat2, &numberOfRows, &numberOfColumns, &numberOfColsForMat2);

            // שחרור זיכרון של המטריצה השנייה
            freeMatrix(mat2, numberOfColumns);

            // עדכון גדלי המטריצה הראשית לאחר הכפל
            numberOfColumns = numberOfColsForMat2;
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
                break;
            case 0:
                break;
            default:
                break;
        }
    }

    return 0;
}

// Function to get validated input
int getValidatedInput(const char *prompt, int min, int max, const char *errorMessage) {
    int value;
    char buffer[100];
    char extra;

    while (1) {
        // Print the prompt
        displayMenu();

        // Read input from the user
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Manually find and remove the trailing newline
            int i = 0;
            while (buffer[i] != '\0' && buffer[i] != '\n') {
                i++;
            }
            if (buffer[i] == '\n') {
                buffer[i] = '\0'; // Replace newline with null terminator
            }

            // Check for empty input (user just pressed Enter or backspaces)
            if (buffer[0] == '\0') {
                printf("%s", errorMessage);
                continue;
            }

            // Check if the input contains only one valid integer
            if (sscanf(buffer, "%d %c", &value, &extra) == 1) {
                // Check if the value is within the specified range
                if (value >= min && value <= max) {
                    return value; // Valid input, return the value
                }
            }

            // Invalid input
            printf("%s", errorMessage);
        }
    }
}


// Function to display the menu
void displayMenu() {
    printf("1. Display the matrix.\n");
    printf("2. Insert values to the matrix.\n");
    printf("3. Transpose matrix.\n");
    printf("4. Sort the matrix by rows sum.\n");
    printf("5. Sort the whole matrix.\n");
    printf("6. Print matrix value.\n");
    printf("7. i-th power of matrix.\n");
    printf("8. Find sub matrix.\n");
    printf("9. Multiply with another matrix.\n");
    printf("0. Exit.\n");
    printf("Please enter your choice: ");
}

long** allocateMatrix(int rows, int columns) {
    long** matrix = malloc(rows * sizeof(long*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(columns * sizeof(long));
    }
    return matrix;
}

// Function to free a matrix
void freeMatrix(long** matrix, int rows) {
    if (matrix != NULL) {
        for (int i = 0; i < rows; i++) {
            free(matrix[i]); // Free each row
        }
        free(matrix); // Free the row pointers
    }
}

void SetInitalMatrix(long** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }
}

void PrintMat(long** matrix, int rows, int cols) {
    printf("\nMatrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j == cols-1) {
                printf("%ld", matrix[i][j]);
            }
            else {
                printf("%ld ", matrix[i][j]);
            }
        }
        printf("\n");
    }
}

void SetMatrix(long** matrix, int rows, int cols) {
    printf("Enter values for the matrix (%d x %d):\n", rows, cols);

    int count = 0;
    while (count < rows * cols) {
        long value;
        if (scanf("%ld", &value) == 1) {
            int row = count / cols;
            int col = count % cols;
            matrix[row][col] = value;
            count++;
        } else {
            printf("Invalid input, please try again.\n");
            while (getchar() != '\n');  // Clear the input buffer
        }
    }
}

void TransposeMatrix(long*** matrix, int* rows, int* cols) {
    // Allocate a new transposed matrix
    long** transposed = malloc((*cols) * sizeof(long*));
    for (int i = 0; i < *cols; i++) {
        transposed[i] = malloc((*rows) * sizeof(long));
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



void SortMatrixByRowSum(long** matrix, int rows, int cols) {
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - i - 1; j++) {
            // Calculate the sum of the current row and the next row
            long long currentRowSum = 0, nextRowSum = 0; // Use long long for larger range
            for (int k = 0; k < cols; k++) {
                currentRowSum += matrix[j][k];
                nextRowSum += matrix[j + 1][k];
            }

            // Swap rows if the current row sum is greater than the next row sum
            if (currentRowSum > nextRowSum) {
                long* temp = matrix[j];
                matrix[j] = matrix[j + 1];
                matrix[j + 1] = temp;
            }
        }
    }
}

void SortMatrix(long** matrix, int rows, int cols) {
    int totalElements = rows * cols;
    long* tempArray = (long*)malloc(totalElements * sizeof(long));

    // Flatten the matrix into a 1D array
    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tempArray[k++] = matrix[i][j];
        }
    }

    // Sort the 1D array
    for (int i = 0; i < totalElements - 1; i++) {
        for (int j = 0; j < totalElements - i - 1; j++) {
            if (tempArray[j] > tempArray[j + 1]) {
                 long temp = tempArray[j];
                tempArray[j] = tempArray[j + 1];
                tempArray[j + 1] = temp;
            }
        }
    }

    // Reshape the sorted array back into the matrix
    k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = tempArray[k++];
        }
    }

    free(tempArray);
}

void PrintMatrixVal(long** matrix, int rows, int cols) {
    long long sumProduct = 0 ;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sumProduct += matrix[i][j]*(i+1)*(j+1);
        }

    }
    printf("Matrix value: %lld\n",sumProduct);
}

void PowerMatrixWithDefault(long*** matrix, int* rows, int* cols, bool* shouldClearBuffer) {
    if (*rows != *cols) {
        printf("Matrix must be square for this operation.\n");
        *shouldClearBuffer = false; // Do not clear the buffer since the operation failed
        return;
    }

    int defaultPower = 0; // Start with default value 0 to trigger user input in PowerMatrix
    PowerMatrix(matrix, rows, cols, &defaultPower);
    *shouldClearBuffer = true; // Operation succeeded, clear the buffer
}


void PowerMatrix(long*** matrix, int* rows, int* cols, int* power) {
    // Check if the matrix is square
    // If power is 0, set a default value
    if (*power == 0) {
        *power = 1; // Default value
    }

    // If power was set to the default value, ask for user input
    do {
        printf(" Enter power: ");
        scanf("%d", power); // Take input directly into the power pointer
        if (*power <= 0) {
            printf(" The power need to Integer Greater Then 0 \n");
        }
    } while (*power <= 0);

    // Temporary matrices to store results
     long** tempMatrix = allocateMatrix(*rows, *cols);  // Temporary result
     long** originalMatrix = allocateMatrix(*rows, *cols);  // Copy of the original matrix

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


void SubMatrix(long*** matrix, int* rows, int* cols) {
    int subRows, subCols, start_row, start_col;

    // Validate inputs
    ValidateSubMatrixInputs(*rows, *cols, &subRows, &subCols, &start_row, &start_col);

    // Calculate and extract the submatrix
    CalculateSubMatrix(matrix, rows, cols, subRows, subCols, start_row, start_col);
}



void ValidateSubMatrixInputs(int rows, int cols, int* subRows, int* subCols, int* start_row, int* start_col) {
    do {
        printf("Enter submatrix rows: ");
        scanf("%d", subRows);

        printf("Enter base row: ");
        scanf("%d", start_row);
        printf("Enter submatrix columns: ");
        scanf("%d", subCols);

        printf("Enter base col: ");
        scanf("%d", start_col);




        if (*subRows <= 0 || *subCols <= 0 || *start_row < 0 || *start_col < 0 ||
            *start_row + *subRows > rows || *start_col + *subCols > cols) {
            printf("Submatrix size exceeds original matrix dimensions.\n");
            }
    } while (*subRows <= 0 || *subCols <= 0 || *start_row < 0 || *start_col < 0 ||
             *start_row + *subRows > rows || *start_col + *subCols > cols);
}


void CalculateSubMatrix(long*** matrix, int* rows, int* cols, int subRows, int subCols, int start_row, int start_col) {
    // Allocate space for the submatrix
    long** tempMatrix = allocateMatrix(subRows, subCols);

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

void MatMul(long*** Mat1, long** Mat2, int* dim1, int* dim2, int* dim3) {
    long** tempMatrix = allocateMatrix(*dim1, *dim3);

    for (int i = 0; i < *dim1; i++) {
        for (int j = 0; j < *dim3; j++) {
            tempMatrix[i][j] = 0;
            for (int k = 0; k < *dim2; k++) {
                tempMatrix[i][j] += (*Mat1)[i][k] * Mat2[k][j];
            }
        }
    }

    freeMatrix(*Mat1, *dim1);
    *Mat1 = tempMatrix;
}

int getValidatedColumns(const char *prompt, int min, int max, const char *errorMessage) {
    int value;
    char buffer[100];
    char extra;

    while (1) {
        printf("%s (%d-%d): ", prompt, min, max);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Check if the input contains only one valid integer
            if (sscanf(buffer, "%d %c", &value, &extra) == 1) {
                // Check if the value is within range
                if (value >= min && value <= max) {
                    return value;
                }
            }
            // Print error message if validation fails
            printf("%s", errorMessage);
        }
    }
}