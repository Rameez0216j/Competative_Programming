// ************************** My Solution (Recursion) **************************
/*
class Solution {
    public:
    pair<int,int> dfs(int row,int col,vector<string>& board){
        int n=board.size();
        int m=board[0].size();

        if(row>=n || col>=m || board[row][col]=='X') return {-1,0}; // -1 =>  for not reachable tracking and 0 ==> no valid path
        if(row==n-1 && col==m-1) return {0,1}; // reached 'S' => val at s=0 and count to reach as 1 ==> {0,1}

        pair<int,int> right=dfs(row,col+1,board);
        pair<int,int> down=dfs(row+1,col,board);
        pair<int,int> diagonalDown=dfs(row+1,col+1,board);

        pair<int,int> ans={-1,0}; // Keep it as invalid
        vector<pair<int,int>> options={right,down,diagonalDown};
        for(auto opt : options){
            if(ans.first < opt.first){
                ans.first=opt.first;
                ans.second=opt.second;
            }else if(ans.first == opt.first){
                ans.second=ans.second+opt.second;
            }
        }

        if(ans.first==-1) return {-1,0};
        ans.first += (board[row][col]-'0');
        return ans;
    }

    vector<int> pathsWithMaxScore(vector<string>& board) {
        board[0][0]='0';
        pair<int,int> ans=dfs(0,0,board);
        if(ans.first==-1) return {0,0};
        return {ans.first,ans.second};
    }
};
*/
// ************************** My Solution (Recursion) **************************




// ************************** My Solution 1 (Memoization => MLE) **************************
/*
class Solution {
    public:
    const int Mod = 1e9 + 7;

    pair<int,int> dfs(int row,int col,vector<string>& board,vector<vector<pair<int,int>>> &dp){
        int n=board.size();
        int m=board[0].size();

        if(row>=n || col>=m || board[row][col]=='X') return {-1,0};
        if(row==n-1 && col==m-1) return dp[row][col]={0,1};

        if(dp[row][col]!=make_pair(-1,-1)) return dp[row][col];

        pair<int,int> right=dfs(row,col+1,board,dp);
        pair<int,int> down=dfs(row+1,col,board,dp);
        pair<int,int> diagonalDown=dfs(row+1,col+1,board,dp);

        pair<int,int> ans={-1,0};
        vector<pair<int,int>> options={right,down,diagonalDown};
        for(auto opt : options){
            if(ans.first < opt.first){
                ans.first=opt.first;
                ans.second=opt.second;
            }else if(ans.first == opt.first){
                ans.second = (ans.second + opt.second) % Mod;  // ✅ MOD HERE
            }
        }

        if(ans.first==-1) return dp[row][col] = {-1,0};
        ans.first = (ans.first + (board[row][col]-'0')) % Mod;  // ✅ MOD HERE
        return dp[row][col]=ans;
    }

    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n=board.size();
        int m=board[0].size();
        vector<vector<pair<int,int>>> dp(n,vector<pair<int,int>>(m,{-1,-1}));

        board[0][0]='0';
        board[n-1][m-1]='0';
        pair<int,int> ans=dfs(0,0,board,dp);

        if(ans.first==-1) return {0,0};
        return {ans.first,ans.second};
    }
};
*/
// ************************** My Solution 1 (Memoization => MLE) **************************





// ************************** My Solution 2 (Memoization) **************************
class Solution {
    public:
    const int MOD = 1e9 + 7;

    pair<int, int> dfs(int row, int col, vector<string>& board, vector<vector<pair<int, int>>>& dp) {
        int n = board.size();
        int m = board[0].size();

        // Out of bounds or wall
        if (row >= n || col >= m || board[row][col] == 'X') return {-1, 0};

        // Goal cell
        if (row == n - 1 && col == m - 1) return {0, 1};

        // Already computed
        if (dp[row][col] != make_pair(-1, -1)) return dp[row][col];

        // Recurse in 3 directions
        auto right = dfs(row, col + 1, board, dp);
        auto down = dfs(row + 1, col, board, dp);
        auto diag = dfs(row + 1, col + 1, board, dp);

        int maxScore = max({right.first, down.first, diag.first});
        int ways = 0;

        if (right.first == maxScore) ways = (ways + right.second) % MOD;
        if (down.first == maxScore) ways = (ways + down.second) % MOD;
        if (diag.first == maxScore) ways = (ways + diag.second) % MOD;

        if (maxScore == -1) return dp[row][col] = {-1, 0};

        int val = (board[row][col] == 'E') ? 0 : (board[row][col] - '0');
        return dp[row][col] = {maxScore + val, ways};
    }

    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        int m = board[0].size();

        // Convert 'E' to '0' for consistent numeric handling
        board[n - 1][m - 1] = '0';

        // Initialize memo table
        vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(m, {-1, -1}));

        auto ans = dfs(0, 0, board, dp);
        if (ans.first == -1) return {0, 0};
        return {ans.first, ans.second};
    }
};
// ************************** My Solution 2 (Memoization) **************************