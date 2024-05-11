#include <iostream>

using namespace std;

const int M1_ROWS = 1; // Number of rows in matrix 1
const int M1_COLS = 4; // Number of columns in matrix 1
const int M2_ROWS = 4; // Number of rows in matrix 2
const int M2_COLS = 7; // Number of columns in matrix 2

// Function to check compatibility for matrix multiplication

int main()
{
    int matrix1[M1_ROWS][M1_COLS] = {{1, 0, 1, 1}};
    int matrix2[M2_ROWS][M2_COLS] = {
        {1, 0, 0, 0, 1, 1, 1},
        {0, 1, 0, 0, 0, 1, 1},
        {0, 0, 1, 0, 1, 0, 1},
        {0, 0, 0, 1, 1, 1, 0}};

    // Check compatibility before proceeding
    int result[M1_ROWS][M2_COLS]; // Resultant matrix

    // Perform matrix multiplication
    for (int i = 0; i < M1_ROWS; i++)
    {
        for (int j = 0; j < M2_COLS; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < M1_COLS; k++)
            {
                result[i][j] += (matrix1[i][k] * matrix2[k][j]);
            }
            result[i][j] %= 2;
        }
    }

    // Print the resulting matrix
    cout << "Resultant matrix:" << endl;
    for (int i = 0; i < M1_ROWS; i++)
    {
        for (int j = 0; j < M2_COLS; j++)
        {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}