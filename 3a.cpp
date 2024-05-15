#include <iostream>
#include <bitset>
#include <vector>
#include <cmath>
using namespace std;

string fakeError(vector<int> &arr)
{
    string s = "";
    arr[0] = !arr[0];
    arr[21] = !arr[21];
    arr[49] = !arr[49];
    arr[84] = !arr[84];
    arr[126] = !arr[126];
    for (auto it = arr.begin(); it != arr.end(); ++it)
    {
        s += to_string(*it);
    }
    return s;
}

void encodeAscii(string names, vector<int> &arr)
{
    cout << "Chuoi ma hoa: ";
    for (char c : names)
    {
        cout << bitset<7>(static_cast<int>(c));
        for (int i = 6; i >= 0; i--)
        {
            arr.push_back(bitset<7>(static_cast<int>(c))[i]);
        }
    }
    cout << endl;
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
        decodedString += static_cast<char>(asciiValue);
    }
    return decodedString;
}

int main()
{
    vector<int> arr;
    string names = "VU TAN DANH PHUOC HUY";
    encodeAscii(names, arr);
    cout << "Chuoi ma sau khi tao loi: ";
    string s = fakeError(arr);
    cout << s;
    string decodedString = decodeAscii(s);
    cout << "\nGiai ma: " << decodedString << endl;
    return 0;
}