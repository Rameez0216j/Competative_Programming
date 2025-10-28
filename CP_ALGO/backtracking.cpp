#include<bits/stdc++.h>
using namespace std;

class NQUEENS_ALL_Solutions{
    vector<vector<string>> ans;
    public:
    bool isSafe(int row,int col,int n,vector<string> &board){
        // Check vertically Up
        for(int i=row-1;i>=0;i--){
            if(board[i][col]=='Q') return false;
        }


        // Check diagonally left
        int next_row=row-1;
        int next_col=col-1;
        while(next_row>=0 && next_col>=0){
            if(board[next_row][next_col]=='Q') return false;
            next_row--;
            next_col--;
        }


        // Check diagonally right
        next_row=row-1;
        next_col=col+1;
        while(next_row>=0 && next_col<n){
            if(board[next_row][next_col]=='Q') return false;
            next_row--;
            next_col++;
        }

        return true;
    }


    void solve(int curr,int n,vector<string> &board){
        if(curr>=n){
            ans.push_back(board);
            return;
        }

        for(int i=0;i<n;i++){
            if(isSafe(curr,i,n,board)){
                board[curr][i]='Q';
                solve(curr+1,n,board);
                board[curr][i]='.';
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<string> board;
        for(int i=0;i<n;i++) board.push_back(string(n,'.'));
        solve(0,n,board);
        return ans;
    }
};







class NQUEENS_Solutions_count {
    public:
    bool isSafe(int row,int col,int n,vector<string> &board){
        // Check vertically Up
        for(int i=row-1;i>=0;i--){
            if(board[i][col]=='Q') return false;
        }


        // Check diagonally left
        int next_row=row-1;
        int next_col=col-1;
        while(next_row>=0 && next_col>=0){
            if(board[next_row][next_col]=='Q') return false;
            next_row--;
            next_col--;
        }


        // Check diagonally right
        next_row=row-1;
        next_col=col+1;
        while(next_row>=0 && next_col<n){
            if(board[next_row][next_col]=='Q') return false;
            next_row--;
            next_col++;
        }

        return true;
    }


    int solve(int curr,int n,vector<string> &board){
        if(curr>=n) return 1;

        int ans=0;
        for(int i=0;i<n;i++){
            if(isSafe(curr,i,n,board)){
                board[curr][i]='Q';
                ans+=solve(curr+1,n,board);
                board[curr][i]='.';
            }
        }

        return ans;
    }

    int totalNQueens(int n) {
        vector<string> board;
        for(int i=0;i<n;i++) board.push_back(string(n,'.'));
        return solve(0,n,board);
    }
};







class SudokuSolver {
    public:
    bool isValid(vector<vector<char>>& board, int row, int col, char c) {
        for (int i = 0; i < 9; i++) {
            // Row check
            if (board[row][i] == c) return false;
            // Column check
            if (board[i][col] == c) return false;
            // 3x3 subgrid check
            int subRow = 3 * (row / 3) + i / 3;
            int subCol = 3 * (col / 3) + i % 3;
            if (board[subRow][subCol] == c) return false;
        }
        return true;
    }

    bool solve(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    for (char c = '1'; c <= '9'; c++) {
                        if (isValid(board, i, j, c)) {
                            board[i][j] = c;
                            if (solve(board)) return true; // go deeper
                            else board[i][j] = '.';        // backtrack
                        }
                    }
                    return false; // no valid number found
                }
            }
        }
        return true; // solved [No values are . now]
    }

    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
};







class SudokuValidator {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        return isValid(0,0,board);
    }
    bool isValid(int r,int c,vector<vector<char>>& board){
        if(r>=board.size()) return true;
        if(c>=board[0].size()) return true;

        // Row check
        for(int i=r+1;i<board.size();i++){
            if(board[r][c]==board[i][c] && board[i][c]!='.') return false;
        }

        // col check
        for(int i=c+1;i<board[0].size();i++){
            if(board[r][c]==board[r][i] && board[r][i]!='.') return false;
        }

        // Checking corresponding 3*3 grid
        for(int i=(r/3)*3;i<((r/3)*3+3);i++){
            for(int j=(c/3)*3;j<((c/3)*3+3);j++){
                if(board[r][c]==board[i][j] && board[i][j]!='.' && (r!=i && c!=j)) return false;
            }
        }
        if(!isValid(r,c+1,board)) return false;
        if(!isValid(r+1,c,board)) return false;
        return true;
    }
};









// Graph coloring 
/*
   color[node] --> stores the color assigned to each vertex.
                   0 means "uncolored"
                   1..k represent available colors.

   adj[v]       --> adjacency list for the graph.
   n            --> number of vertices
   k            --> number of colors we are allowed to use
*/
bool isSafe(int node, int chosenColor, vector<vector<int>> &adj, vector<int> &color) {
    // Check if any neighbor already has this color
    for (int neighbor : adj[node]) {
        if (color[neighbor] == chosenColor)
            return false;
    }
    return true;
}

// Recursive function to color each node
bool colorGraph(int node, int n, int k, vector<vector<int>> &adj, vector<int> &color) {
    // Base case: if all nodes are colored, return true
    if (node == n)
        return true;

    // Try assigning each color from 1 to k
    for (int chosenColor = 1; chosenColor <= k; ++chosenColor) {
        if (isSafe(node, chosenColor, adj, color)) {
            color[node] = chosenColor;

            // Recur for the next vertex
            if (colorGraph(node + 1, n, k, adj, color))
                return true;

            // Backtrack (remove the color if it doesn't lead to a solution)
            color[node] = 0;
        }
    }

    // If no color works, return false
    return false;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k; // vertices, edges, and number of colors

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        // Assuming 0-based indexing
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> color(n, 0);

    if (colorGraph(0, n, k, adj, color)) {
        cout << "Graph can be colored with " << k << " colors:\n";
        for (int i = 0; i < n; ++i)
            cout << "Node " << i << " --> Color " << color[i] << "\n";
    } else {
        cout << "Graph cannot be colored with " << k << " colors.\n";
    }

    return 0;
}

/*
🧩 Explanation:
---------------
1️⃣ Try assigning each of the k colors to node 0.
2️⃣ For each color, check if no neighbor has that color (isSafe()).
3️⃣ Move to the next node recursively.
4️⃣ If at any point no color can be assigned, backtrack.
5️⃣ When all nodes are colored successfully, graph is k-colorable.
*/
