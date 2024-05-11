#include <iostream>
using namespace std;
string char2bin(char C)
{
    switch (C)
    {
    case 'A':
        return "0000";
        break;
    case 'B':
        return "0001";
        break;
    case 'C':
        return "0010";
        break;
    case 'D':
        return "0011";
        break;
    case 'E':
        return "0100";
        break;
    case 'G':
        return "0101";
        break;
    case 'H':
        return "0110";
        break;
    case 'I':
        return "0111";
        break;
    case 'L':
        return "1000";
        break;
    case 'N':
        return "1001";
        break;
    case 'O':
        return "1010";
        break;
    case 'P':
        return "1011";
        break;
    case 'T':
        return "1100";
        break;
    case 'U':
        return "1101";
        break;
    case 'V':
        return "1110";
        break;
    case 'Y':
        return "1111";
        break;
    default:
        break;
    }
    return 0;
}

string encodeLBC(string names)
{
    string s = "";
    for (char c : names)
    {
        s += char2bin(c);
    }
    return s;
}