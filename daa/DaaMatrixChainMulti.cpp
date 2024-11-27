#include <iostream>
#include <climits>
using namespace std;

int MatrixChainMultiplication(int dimensions[], int n) {

    int dp[n][n];

    // cost is zero when multiplying one matrix
    for (int i = 1; i < n; i++)
        dp[i][i] = 0;

    // L is the chain length
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                // q = cost/scalar multiplications
                int q = dp[i][k] + dp[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];
                if (q < dp[i][j])
                    dp[i][j] = q;
            }
        }
    }

    // The minimum cost is found at dp[1][n-1]
    return dp[1][n - 1];
}

int main() {
    // Array dimensions
    int dimensions[] = {3,2,4,2,5};
    int n = sizeof(dimensions) / sizeof(dimensions[0]);

    cout << "Minimum number of multiplications is: " 
         << MatrixChainMultiplication(dimensions, n) << endl;

    
    return 0;
}
