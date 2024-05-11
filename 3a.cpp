#include <iostream>
#include <bitset>
#include <vector>
#include <cmath>
using namespace std;

string fakeError(vector<int> &arr)
{
    string s = "";
    int index_err1 = 0;
    int index_err2 = 7 * 3;
    int index_err3 = 7 * 7;
    int index_err4 = 7 * 12;
    int index_err5 = 7 * 18;
    arr[index_err1] = !arr[index_err1];
    arr[index_err2] = !arr[index_err2];
    arr[index_err3] = !arr[index_err3];
    arr[index_err4] = !arr[index_err4];
    arr[index_err5] = !arr[index_err5];
    for (auto it = arr.begin(); it != arr.end(); ++it)
    {
        s += to_string(*it);
    }
    for (int i = 0; i < s.length(); i++)
    {
        cout << s[i];
        if (i % 7 == 0)
            cout << endl;
    }
    return s;
}

void encodeAscii(string names, vector<int> &arr)
{
    for (char c : names)
    {
        cout << bitset<7>(static_cast<int>(c)) << endl;
        for (int i = 6; i >= 0; i--)
        {
            arr.push_back(bitset<7>(static_cast<int>(c))[i]);
        }
    }
}

string decodeAscii(string binaryString)
{
    string decodedString;
    for (int i = 0; i < (int)binaryString.length(); i += 7)
    {
        string binaryChar = binaryString.substr(i, 7);
        int asciiValue = 0;
        for (int j = 0; j < 7; j++)
        {
            if (binaryChar[j] == '1')
            {
                asciiValue += pow(2, 6 - j);
            }
        }
        if (asciiValue < 32 || asciiValue > 126)
        {
            cout << "\nWarning: Encountered invalid ASCII value (" << asciiValue << ") at position " << i << endl;
            decodedString += "-";
        }
        else
        {
            decodedString += static_cast<char>(asciiValue);
        }
    }
    return decodedString;
}

int main()
{
    vector<int> arr;
    string names = "VU TAN DANH PHUOC HUY";
    encodeAscii(names, arr);
    string s = fakeError(arr);
    cout << s;
    string decodedString = decodeAscii(s);
    cout << "\nDecoded Character: " << decodedString << endl;
    return 0;
}