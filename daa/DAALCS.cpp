#include <iostream>
#include <vector>
#include <chrono>
#include <string>

using namespace std;
using namespace chrono;

void lcsAlgo(const string &S1, const string &S2, int m, int n) {
    vector<vector<int>> LCS_table(m + 1, vector<int>(n + 1));

    // Building the matrix in bottom-up way
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                LCS_table[i][j] = 0;
            else if (S1[i - 1] == S2[j - 1])
                LCS_table[i][j] = LCS_table[i - 1][j - 1] + 1;
            else
                LCS_table[i][j] = max(LCS_table[i - 1][j], LCS_table[i][j - 1]);
        }
    }

    int index = LCS_table[m][n];
    string lcsString(index, '\0'); // Preallocate string with size index

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (S1[i - 1] == S2[j - 1]) {
            lcsString[index - 1] = S1[i - 1];
            i--;
            j--;
            index--;
        } else if (LCS_table[i - 1][j] > LCS_table[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // Printing the subsequences
    cout << "S1 : " << S1 << "\nS2 : " << S2 << "\nLCS: " << lcsString << "\n";
}

int main() {
    string S1, S2;
    
    // Taking input from user
    cout << "Enter first string: ";
    cin >> S1;
    cout << "Enter second string: ";
    cin >> S2;

    int m = S1.length();
    int n = S2.length();

    auto start = high_resolution_clock::now();
    lcsAlgo(S1, S2, m, n);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Execution Time: " << duration << " microseconds" << endl;

    return 0;
}
