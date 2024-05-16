#include <iostream>
#include "encodeLBC.h"
#include "decodeLBC.h"
using namespace std;

void convertMatrix(string inputString, int matrix[][4])
{
    for (int i = 0; i < 17; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int index = i * 4 + j;
            matrix[i][j] = inputString[index] - '0';
        }
    }
}

void calCodewords(int matrix1[][4], int res[][7])
{
    int G[4][7] = {
        {1, 0, 0, 0, 1, 1, 1},
        {0, 1, 0, 0, 0, 1, 1},
        {0, 0, 1, 0, 1, 0, 1},
        {0, 0, 0, 1, 1, 1, 0}};
    for (int i = 0; i < 17; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < 4; k++)
            {
                res[i][j] += (matrix1[i][k] * G[k][j]);
            }
            res[i][j] %= 2;
        }
    }
}

void fakeError(int matrix[][7])
{
    // matrix[0][4] = !matrix[0][4];
    // matrix[2][4] = !matrix[2][4];
    // matrix[5][4] = !matrix[5][4];
    // matrix[9][4] = !matrix[9][4];
    // matrix[12][4] = !matrix[12][4];
    matrix[0][0] = !matrix[0][0];
    matrix[2][0] = !matrix[2][0];
    matrix[5][0] = !matrix[5][0];
    matrix[9][0] = !matrix[9][0];
    matrix[12][0] = !matrix[12][0];
}

void findSyndrome(int codewords[][7], int res[][3])
{
    int HT[8][3] = {
        {1, 1, 1},
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0},
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}};
    for (int i = 0; i < 17; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < 7; k++)
            {
                res[i][j] += (codewords[i][k] * HT[k][j]);
            }
            res[i][j] %= 2;
        }
    }
}

void fixError(int errorMatrix[][3], int matrix[][7])
{
    int e[8][7] = {
        {0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 1},
    };
    for (int i = 0; i < 17; i++)
    {
        string s = "";
        s = to_string(errorMatrix[i][0]) + to_string(errorMatrix[i][1]) + to_string(errorMatrix[i][2]);
        if (s == "000")
        {
            for (int j = 0; j < 7; j++)
            {
                matrix[i][j] += e[0][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "111")
        {

            for (int j = 0; j < 7; j++)
            {
                matrix[i][j] += e[1][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "011")
        {
            for (int j = 0; j < 7; j++)
            {
                matrix[i][j] += e[2][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "101")
        {
            for (int j = 0; j < 7; j++)
            {
                matrix[i][j] += e[3][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "110")
        {
            for (int j = 0; j < 7; j++)
            {
                matrix[i][j] += e[4][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "100")
        {
            for (int j = 0; j < 7; j++)
            {
                matrix[i][j] += e[5][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "010")
        {
            for (int j = 0; j < 7; j++)
            {
                matrix[i][j] += e[6][j];
                matrix[i][j] %= 2;
            }
        }
        else
        {
            for (int j = 0; j < 7; j++)
            {
                matrix[i][j] += e[7][j];
                matrix[i][j] %= 2;
            }
        }
    }
}
void decodeCodewards(int codewards[][7], int matrixRes[][4])
{
    for (int i = 0; i < 17; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                matrixRes[i][j] = codewards[i][j];
            }
        }
    }
}
int main()
{
    string names = "VUTANDANHHUYPHUOC";
    string s;
    s = encodeLBC(names);
    int matrix[17][4];
    convertMatrix(s, matrix);
    cout << "\n\tKet qua ma hoa" << endl;
    for (int i = 0; i < 17; i++)
    {
        cout << "\n\t";
        for (int j = 0; j < 4; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    int codewords[17][7];
    calCodewords(matrix, codewords);
    cout << "\n\tTu ma khoi tuyen tinh (4,7)" << endl;
    for (int i = 0; i < 17; i++)
    {
        cout << "\n\t";
        for (int j = 0; j < 7; j++)
        {
            cout << codewords[i][j] << " ";
        }
        cout << endl;
    }
    fakeError(codewords);
    cout << "\n\tTao loi" << endl;
    for (int i = 0; i < 17; i++)
    {
        cout << "\n\t";
        for (int j = 0; j < 7; j++)
        {
            cout << codewords[i][j] << " ";
        }
        cout << endl;
    }
    int syndrome[17][3];
    findSyndrome(codewords, syndrome);
    cout << "\n\tBang Syndrome" << endl;
    for (int i = 0; i < 17; i++)
    {
        cout << "\n\t";
        for (int j = 0; j < 3; j++)
        {
            cout << syndrome[i][j] << " ";
        }
        cout << endl;
    }
    fixError(syndrome, codewords);
    cout << "\n\tTu ma sau khi sua loi" << endl;
    for (int i = 0; i < 17; i++)
    {
        cout << "\n\t";
        for (int j = 0; j < 7; j++)
        {
            cout << codewords[i][j] << " ";
        }
        cout << endl;
    }
    int decodeMatrix[17][4];
    decodeCodewards(codewords, decodeMatrix);
    cout << "\n\tKet qua giai ma: " << endl;
    for (int i = 0; i < 17; i++)
    {
        cout << "\n\t";
        for (int j = 0; j < 4; j++)
        {
            cout << decodeMatrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}