#include <bits/stdc++.h>
using namespace std;

/*
Recursive Matrix Chain Multiplication
dimensions[] -> dimensions of matrices: matrix Ai has size dimensions[i-1] x dimensions[i]
i -> starting index of chain
j -> ending index of chain
*/

int matrixChainMultiplication(vector<int>& dimensions) {
    int n = dimensions.size() - 1; // number of matrices
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));

    // l = length of chain
    for (int len = 2; len <= n; len++) { // start from chain length 2
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k+1][j] + dimensions[i-1]*dimensions[k]*dimensions[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[1][n]; // minimum cost to multiply matrices A1..An
}


int mcmRecursive(vector<int>& dimensions, int i, int j) {
    // Base case: single matrix, no multiplication needed
    if (i == j) return 0;

    int minCost = INT_MAX;

    // Try every possible split position
    for (int k = i; k < j; k++) {
        int cost = mcmRecursive(dimensions, i, k)      // cost to multiply Ai..Ak
                 + mcmRecursive(dimensions, k+1, j)   // cost to multiply A(k+1)..Aj
                 + dimensions[i-1] * dimensions[k] * dimensions[j]; // cost to multiply resulting matrices
        minCost = min(minCost, cost);
    }

    return minCost;
}

int main() {
    vector<int> dimensions = {40, 20, 30, 10, 30}; 
    int n = dimensions.size() - 1; // number of matrices
    cout << "Minimum multiplication cost (recursive): " << mcmRecursive(dimensions, 1, n) << endl;
    cout << "Minimum multiplication cost: " << matrixChainMultiplication(dimensions) << endl;
}


