// ************************************* My Solution *************************************
class Solution {
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
// ************************************* My Solution *************************************