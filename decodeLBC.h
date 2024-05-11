#include <iostream>
using namespace std;
string bin2char(string s)
{
    if (s == "0000")
        return "A";
    else if (s == "0001")
        return "B";
    else if (s == "0010")
        return "C";
    else if (s == "0011")
        return "D";
    else if (s == "0100")
        return "E";
    else if (s == "0101")
        return "G";
    else if (s == "0110")
        return "H";
    else if (s == "0111")
        return "I";
    else if (s == "1000")
        return "L";
    else if (s == "1001")
        return "N";
    else if (s == "1010")
        return "O";
    else if (s == "1011")
        return "P";
    else if (s == "1100")
        return "T";
    else if (s == "1101")
        return "U";
    else if (s == "1110")
        return "V";
    else
        return "Y";
    return 0;
}
string decodeLBC(int matrix[][7])
{
    string s = "";
    for (int i = 0; i < 17; i++)
    {
        string z = "";
        for (int j = 0; j < 4; j++)
            z += to_string(matrix[i][j]);
        s += bin2char(z);
    }
    return s;
}