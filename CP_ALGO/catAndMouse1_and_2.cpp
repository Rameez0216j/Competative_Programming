// can and mouse 2 

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int rows, cols;
    vector<vector<char>> grid;
    int catJump, mouseJump;
    pair<int,int> food;
    int dir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};

    // Generate all reachable positions for a player from (r,c) with maxJump
    vector<pair<int,int>> getNextPositions(pair<int,int> pos, int maxJump) {
        vector<pair<int,int>> nextPos;
        int r0 = pos.first, c0 = pos.second;
        nextPos.push_back(pos); // staying in place is allowed

        for (auto &d : dir) {
            for (int jump=1; jump <= maxJump; ++jump) {
                int r = r0 + d[0]*jump;
                int c = c0 + d[1]*jump;
                if (r<0 || r>=rows || c<0 || c>=cols || grid[r][c]=='#') break; // stop at walls or boundaries
                nextPos.push_back({r,c});
            }
        }
        return nextPos;
    }

    // DFS to check if Mouse can force a win from current state
    bool dfs(pair<int,int> mouse, pair<int,int> cat, int turn) {
        if (turn > 1000) return false;       // Cat wins by timeout
        if (mouse == food) return true;      // Mouse wins if it reaches food
        if (cat == food || mouse == cat) return false; // Cat wins if it reaches food or catches Mouse

        if (turn % 2 == 0) { // Mouse's turn
            // Mouse tries all possible moves
            for (auto nextMouse : getNextPositions(mouse, mouseJump)) {
                if (dfs(nextMouse, cat, turn+1)) return true; // If any move leads to Mouse winning, return true
            }
            return false; // No winning moves, Mouse cannot win from this state
        } else { // Cat's turn
            // Cat tries all possible moves
            for (auto nextCat : getNextPositions(cat, catJump)) {
                // Cat's goal: prevent Mouse from winning
                // dfs(next state) returns true if Mouse can win from that move
                // If !dfs(...) is true, it means Mouse cannot win from that move → good for Cat
                if (!dfs(mouse, nextCat, turn+1)) return false; // Cat found a move to prevent Mouse → Mouse loses
            }
            return true; // All Cat moves allow Mouse to win → Cat cannot prevent Mouse, so Mouse wins
        }
    }

    bool canMouseWin(vector<string>& g, int cJ, int mJ) {
        grid.resize(g.size(), vector<char>(g[0].size()));
        rows = g.size();
        cols = g[0].size();
        catJump = cJ;
        mouseJump = mJ;

        pair<int,int> mouse, cat;
        for (int i=0;i<rows;i++){
            for (int j=0;j<cols;j++){
                grid[i][j] = g[i][j];
                if (grid[i][j]=='M') mouse = {i,j};
                else if (grid[i][j]=='C') cat = {i,j};
                else if (grid[i][j]=='F') food = {i,j};
            }
        }

        return dfs(mouse, cat, 0);
    }
};












// cat and mouse 1 also is based on same logic try it out everything is based on base case 