#include <iostream>
#include "encodeLBC.h"
#include "decodeLBC.h"
#include "printMatrix.h"
#include <bitset>
#include <vector>
using namespace std;

string encodeAscii(string names)
{
    vector<int> arr;
    string s = "";
    for (char c : names)
    {

        for (int i = 6; i >= 0; i--)
        {
            arr.push_back(bitset<7>(static_cast<int>(c))[i]);
        }
    }
    for (auto it = arr.begin(); it != arr.end(); ++it)
    {
        s += to_string(*it);
    }
    return s;
}

void convertMatrix(string inputString, int matrix[][7])
{
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            int index = i * 7 + j;
            matrix[i][j] = inputString[index] - '0';
        }
    }
}

void calCodewords(int matrix1[][7], int res[][11])
{
    int G[7][11] = {
        {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
        {0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1},
        {0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1},
    };
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < 7; k++)
            {
                res[i][j] += (matrix1[i][k] * G[k][j]);
            }
            res[i][j] %= 2;
        }
    }
}

void fakeError(int matrix[][11])
{
    matrix[0][4] = !matrix[0][4];
    matrix[3][4] = !matrix[3][4];
    matrix[7][4] = !matrix[7][4];
    matrix[12][4] = !matrix[12][4];
    matrix[16][4] = !matrix[16][4];
    matrix[0][0] = !matrix[0][0];
    matrix[3][0] = !matrix[3][0];
    matrix[7][0] = !matrix[7][0];
    matrix[12][0] = !matrix[12][0];
    matrix[16][0] = !matrix[16][0];
}

void findSyndrome(int codewords[][11], int res[][4])
{
    int arr[16][4];
    int HT[11][4] = {
        {1, 1, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 1},
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    };
    int e[16][11] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    };
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            arr[i][j] = 0;
            for (int k = 0; k < 11; k++)
            {
                arr[i][j] += (e[i][k] * HT[k][j]);
            }
            arr[i][j] %= 2;
        }
    };
    cout << "\n\tBang syn" << endl;
    for (int i = 0; i < 16; i++)
    {
        cout << "\n\t";
        for (int j = 0; j < 4; j++)
        {
            cout << arr[i][j];
        }
        cout << endl;
    }
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < 11; k++)
            {
                res[i][j] += (codewords[i][k] * HT[k][j]);
            }
            res[i][j] %= 2;
        }
    }
}

void fixError(int errorMatrix[][4], int matrix[][11])
{
    int e[16][11] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    };

    for (int i = 0; i < 21; i++)
    {
        string s = "";
        s = to_string(errorMatrix[i][0]) + to_string(errorMatrix[i][1]) + to_string(errorMatrix[i][2]) + to_string(errorMatrix[i][3]);

        if (s == "0000")
        {
            for (int j = 0; j < 11; j++)
            {
                matrix[i][j] += e[0][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "0001")
        {
            for (int j = 0; j < 11; j++)
            {
                matrix[i][j] += e[1][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "0010")
        {
            for (int j = 0; j < 11; j++)
            {
                matrix[i][j] += e[2][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "0100")
        {
            for (int j = 0; j < 11; j++)
            {
                matrix[i][j] += e[3][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "1000")
        {
            for (int j = 0; j < 11; j++)
            {
                matrix[i][j] += e[4][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "0011")
        {
            for (int j = 0; j < 11; j++)
            {
                matrix[i][j] += e[5][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "0101")
        {
            for (int j = 0; j < 11; j++)
            {
                matrix[i][j] += e[6][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "0010")
        {
            for (int j = 0; j < 11; j++)
            {
                matrix[i][j] += e[7][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "0100")
        {
            for (int j = 0; j < 11; j++)
            {
                matrix[i][j] += e[8][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "1101")
        {
            for (int j = 0; j < 11; j++)
            {
                matrix[i][j] += e[9][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "1101")
        {
            for (int j = 0; j < 11; j++)
            {
                matrix[i][j] += e[10][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "1100")
        {
            for (int j = 0; j < 11; j++)
            {
                matrix[i][j] += e[11][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "1001")
        {
            for (int j = 0; j < 11; j++)
            {
                matrix[i][j] += e[12][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "1000")
        {
            for (int j = 0; j < 11; j++)
            {
                matrix[i][j] += e[13][j];
                matrix[i][j] %= 2;
            }
        }
        else if (s == "1110")
        {
            for (int j = 0; j < 11; j++)
            {
                matrix[i][j] += e[14][j];
                matrix[i][j] %= 2;
            }
        }
        else
        {
            for (int j = 0; j < 11; j++)
            {
                matrix[i][j] += e[15][j];
                matrix[i][j] %= 2;
            }
        }
    }
}
int main()
{
    string names = "VU TAN DANH HUY PHUOC";
    string s;
    s = encodeAscii(names);
    cout << s << endl;
    int arr[21][7];
    convertMatrix(s, arr);
    cout << "\n\tKet qua ma hoa" << endl;
    for (int i = 0; i < 21; i++)
    {
        cout << "\n\t";
        for (int j = 0; j < 7; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    int codewords[21][11];
    calCodewords(arr, codewords);
    cout << "\n\tTu ma khoi tuyen tinh (7,11)" << endl;
    for (int i = 0; i < 21; i++)
    {
        cout << "\n\t";
        for (int j = 0; j < 11; j++)
        {
            cout << codewords[i][j] << " ";
        }
        cout << endl;
    }
    fakeError(codewords);
    cout << "\n\tTao loi" << endl;
    for (int i = 0; i < 21; i++)
    {
        cout << "\n\t";
        for (int j = 0; j < 11; j++)
        {
            cout << codewords[i][j] << " ";
        }
        cout << endl;
    }
    int syndrome[21][4];
    findSyndrome(codewords, syndrome);
    cout << "\n\tBang vi tri loi" << endl;
    for (int i = 0; i < 21; i++)
    {
        cout << "\n\t";
        for (int j = 0; j < 4; j++)
        {
            cout << syndrome[i][j] << " ";
        }
        cout << endl;
    }
    fixError(syndrome, codewords);
    cout << "\n\tTu ma sau khi sua loi" << endl;
    for (int i = 0; i < 21; i++)
    {
        cout << "\n\t";
        for (int j = 0; j < 11; j++)
        {
            cout << codewords[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}