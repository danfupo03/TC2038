#include <iostream>
#include <string>

using namespace std;

void search(string pat, string txt)
{
    int M = pat.length();
    int N = txt.length();

    if (M > N)
    {
        cout << "Pattern length is greater than text length. Cannot find pattern." << endl;
        return;
    }

    for (int i = 0; i <= N - M; i++)
    {
        int j;

        for (j = 0; j < M ; j++)
        {
            if (txt[i + j] != pat[j])
                break;
        }
        if (j == M)
            cout << "Pattern found at index " << i << endl;
    }
}

int main()
{
    string txt = "70616e206465206e6172716e6a61";
    string pat = "17271";

    string txt2 = "AABAACAADAABAAABAA";
    string pat2 = "AABA";

    search(pat, txt);
    //search(pat2, txt2);

    return 0;
}

// <bits/stdc++.h>