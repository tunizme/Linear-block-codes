#include <iostream>
#include <bitset>
#include <vector>
#include <cmath>
using namespace std;

string fakeError(vector<int> &arr)
{
    string s = "";

    for (int i = 0; i < s.length(); i++)
    {
        if (i % 7 == 0)
            cout << endl;
    }
    return s;
}

string encodeAscii(string names, vector<int> &arr)
{
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

int main()
{
    vector<int> arr;
    string names = "VU TAN DANH PHUOC HUY";
    encodeAscii(names, arr);
    string binaryString = fakeError(arr);

    if (binaryString.length() % 7 != 0)
    {
        cerr << "Error: Binary string length must be a multiple of 7." << endl;
        return 1;
    }

    int arraySize = binaryString.length() / 7;
    int binaryArray[arraySize][7];

    // Convert binary string to integer and store in the array
    for (int i = 0; i < arraySize; i++)
    {
        string subString = binaryString.substr(i * 7, 7);
        for (int j = 0; j < 7; j++)
        {
            binaryArray[i][j] = (subString[j] - '0'); // Convert character to integer
        }
    }

    // Print the array (optional)
    for (int i = 0; i < arraySize; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            cout << binaryArray[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}