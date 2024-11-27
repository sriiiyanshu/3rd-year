#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class NQueens {
private:
    int n; 
    vector<vector<int>> board; 

public:
    NQueens(int n) : n(n), board(n, vector<int>(n, 0)) {}

    void printBoard() {
        cout << "Board Representation:" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j]) {
                    cout << " Q "; // Mark the queen's position
                } else {
                    cout << " . ";
                }
            }
            cout << endl;
        }

        cout << "Column Indices: ";
        vector<int> solution; // To store the column positions of queens

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j]) {
                    solution.push_back(j); // Store the column index of the queen
                }
            }
        }

        for (size_t i = 0; i < solution.size(); ++i) {
            cout << solution[i];
            if (i < solution.size() - 1) {
                cout << ",";
            }
        }
        cout << endl << endl;
    }

    // Function to check if placing a queen is safe
    bool isSafe(int row, int col) {
        // Check the column
        for (int i = 0; i < row; i++) {
            if (board[i][col]) return false;
        }

        // Check the upper left diagonal
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j]) return false;
        }

        // Check the upper right diagonal
        for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
            if (board[i][j]) return false;
        }

        return true;
    }

    // Backtracking function to solve the n-Queens problem
    bool solveNQueensUtil(int row) {
        if (row == n) {
            printBoard();
            return true;
        }

        bool foundSolution = false; // To track if we found a solution

        for (int col = 0; col < n; col++) {
            if (isSafe(row, col)) {
                board[row][col] = 1;
                foundSolution = solveNQueensUtil(row + 1) || foundSolution;
                board[row][col] = 0; 
            }
        }

        return foundSolution;
    }

    void solveNQueens() {
        if (!solveNQueensUtil(0)) {
            cout << "No solution exists for n = " << n << endl;
        }
    }
};

int main() {
    int n;
    cout << "Enter the number of queens (n): ";
    cin >> n;

    NQueens nQueens(n);
    nQueens.solveNQueens();

    return 0;
}
