// Solution : https://www.youtube.com/watch?v=2H0zU6v-xck&t=1397s
// *********************************************** My Solution ***********************************************
class Solution {
    int M=1e9+7;

    public:
    int solveRec(int totalSongs,int uniqueSongs,int goal,int n,int k){
        if(totalSongs==goal){
            // As at last all songs needed to be played
            if(uniqueSongs==n) return 1;
            return 0; // This will void all the plalyst and make it disapper from count
        }

        // Play a unique song 
        int case1=0;
        // Assume as we can play a unique song only if the no of unique song does not exceeed the total unique songs ( a new unique song can only be played then )
        if(n>uniqueSongs) case1=(n-uniqueSongs)*solveRec(totalSongs+1,uniqueSongs+1,goal,n,k);

        // Play a previously played song
        int case2=0;
        // Assume this as we are having songs 1,2,3,4,5,....,k,k+1,k+2
        // At the (k + 2)th song, if I want to play a repeated song, I can only choose from the first (k + 2 − k) = 2 previously played songs, i.e., songs 1 and 2, because at least k different songs must be played before any song can be repeated.
        if(uniqueSongs>=k) case2=(uniqueSongs-k)*solveRec(totalSongs+1,uniqueSongs,goal,n,k);

        return case1+case2;
    }



    int solveRec_Mem(int totalSongs,int uniqueSongs,int goal,int n,int k,vector<vector<int>> &dp){
        if(totalSongs==goal){
            // As at last all songs needed to be played
            if(uniqueSongs==n) return 1;
            return 0;
        }

        if(dp[totalSongs][uniqueSongs]!=-1) return dp[totalSongs][uniqueSongs];

        // Play a unique song 
        int case1=0;
        if(n>uniqueSongs) case1=(1LL * (n-uniqueSongs)% M * solveRec_Mem(totalSongs+1,uniqueSongs+1,goal,n,k,dp)%M )%M;

        // Play a previously played song
        int case2=0;
        if(uniqueSongs>=k) case2=(1LL* (uniqueSongs-k)%M * solveRec_Mem(totalSongs+1,uniqueSongs,goal,n,k,dp)%M )%M;

        return dp[totalSongs][uniqueSongs]=(case1%M + case2%M )%M;
    }



    int numMusicPlaylists(int n, int goal, int k) {
        // Recursion
        // return solveRec(0,0,goal,n,k);

        // Rrecursion + Memoization
        vector<vector<int>> dp(goal+1,vector<int>(n+1,-1));
        return solveRec_Mem(0,0,goal,n,k,dp);
    }
};
// *********************************************** My Solution ***********************************************








// *************************************** Cleaned Solution with Explaination  ***************************************
/*
    totalSongs -> current playlist length built so far
    uniqueSongs -> number of unique songs used so far
    goal -> total desired playlist length
    n -> total number of available unique songs
    k -> a song can only be repeated if at least k other songs are played in between



    Case 1: Add a new unique song

        - We can do this only if we still have unused songs.
        - There are (n - uniqueSongs) songs left to be introduced.

        Example:
            n = 5, uniqueSongs = 3 → Already used: {1, 2, 3}
            → Remaining = 2 songs ({4, 5}) can still be added uniquely



    Case 2: Replay a previously played song

        - This is allowed only if we've already played at least 'k' different songs.
        - Only (uniqueSongs - k) songs are valid for repetition.

        Intuition from your example:
        ---------------------------------------------------------
        Suppose we've played songs like:
        1, 2, 3, 5, ..., k, k+1, k+2  → totalSongs = k+2
        To replay a song now, we must have played at least k different songs.
        So, at position (k+2), we can replay any of the earlier (k+2 - k) = 2 songs
        (e.g., song 1 or 2) to maintain the k-gap rule.

        Hence, valid repeat options = (uniqueSongs - k)
*/

/*
class Solution {
    public:
    
    int solveRec(int totalSongs, int uniqueSongs, int goal, int n, int k) {
        // Base case: If playlist has reached the desired length
        if (totalSongs == goal) {
            // Valid only if all unique songs have been used
            return (uniqueSongs == n) ? 1 : 0;
        }

        int case1 = 0; // Option 1: Add a new unique song
        int case2 = 0; // Option 2: Replay a previously used song


        if (n > uniqueSongs) {
            case1 = (n - uniqueSongs) * solveRec(
                totalSongs + 1,
                uniqueSongs + 1,
                goal, n, k
            );
        }

        if (uniqueSongs >= k) {
            case2 = (uniqueSongs - k) * solveRec(
                totalSongs + 1,
                uniqueSongs,
                goal, n, k
            );
        }

        // Return total valid playlists from this point
        return case1 + case2;
    }

    int numMusicPlaylists(int n, int goal, int k) {
        return solveRec(0, 0, goal, n, k);
    }
};
*/
// *************************************** Cleaned Solution with Explaination  ***************************************
