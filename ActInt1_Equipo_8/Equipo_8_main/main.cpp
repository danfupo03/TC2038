#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void isSuffix(string s1, string s2)
{
    int n1 = s1.length(), n2 = s2.length();
    bool isSuffix = true;
    int startIndex = -1;

    if (n1 > n2)
    {
        isSuffix = false;
    }
    else
    {
        for (int i = 0; i < n1; i++)
        {
            if (s1[n1 - i - 1] != s2[n2 - i - 1])
            {
                isSuffix = false;
                break;
            }
            startIndex = n2 - i - 1;
        }
    }

    if (isSuffix)
    {
        cout << "Yes, substring found at index: " << startIndex << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}

int main(int argc, char *argv[])
{
    ifstream inputFile;

    string s1, s2;

    if (argc < 2)
    {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    inputFile.open(argv[1]);

    if (!inputFile)
    {
        cout << "Error opening file" << endl;
        return 1;
    }

    inputFile >> s1;

    cout << "s1: " << s1 << endl;

    // isSuffix(s1, s2);

    return 0;
}
