// Similar to 1823. Find the Winner of the Circular Game --> Leetcode

class Solution {
    public:
    // for 0 based indexing
    int solveRec0(int n, int k) {
        if(n==1) return 0;
        return (solveRec0(n-1,k)+k)%n;
    }



    // Explaination
    /*
    Base case --> if there is only one person the he is the winner
    Now in any game with N people (N,K)
    start 1 2 3 4 .... K(kill this guy) K+1 K+2 .... N
    now total number of people left = N-1
    Now counting starts from (K+1)th guy ---> K+1 K+2 ..... N 1 2 3 .... K-1 [N-1 persons]
    if we change this to 1 2 3 .. K .. N-1 then we can solve (N-1,K)

    the mapping is like...
    curr(N,K)        next(N-1,K)
        K+1                 1
        K+2                 2
        .
        .
        N                   N-K
        1                   [1+(N-K)]  [added total no of people after K killed in curr step]
        .
        .

        K-1                 [(K-1)+(N-K)] ---> [K-1+N-K] = N-1

        [K do not exist as it died] K --> K-K=0


        so what ever answer we get from next we need to add K to it to get original in curr step 
        1 --> 1+K ....


        Now after we get winner from next step
        curr_winner=next_winner+K;
        if next_winner==N-1 --> curr_winner= [ (N-1 + K) > N ] if K>1 so we mod with N at curr step
        Now % N 
        N-1+K = N ==> (N)%N --> 0 last person (return N) Exception
        N-1+K = N+1 ==> (N+1)%N --> 1 person
        .
        .
        .

        Adjustment: 
        return [(curr_winner-1)%N + 1] 
        consider next_winner= N-1 ;
            K           curr_winner    curr_winner-1    (curr_winner-1)%N       (curr_winner-1)%N + 1      curr_winner
            1            N-1+K = N          N-1           (N-1)%N = N-1              N-1+1 = N                 0 last person (return N) Exception
            2           N-1+K = N+1       N+1-1= N          (N)%N = 0                 0+1 = 1                  1 person


        Now if 
        curr_winner is bound to N
        for next_winner+K
                1           ---> 0%N + 1 = 1
                2           ---> 1%N + 1 = 2
                N           ---> (N-1)%N+1 = N
                N+1         ---> (N)%N+1 = 1
            

        Learning key material and make sure rotation happens well use --->  [(next_winner + K -1)%N + 1]  ---> RANGE [1,N]
        insted of [(next_winner + K)%N]
        
    */

    int solveRec1(int n, int k) {
        if(n==1) return 1;
        int winner=(solveRec1(n-1,k)+k)%n; 
        if(winner==0) return n;
        return winner;
    }
    

    // For 1 based indexing (adjusting)
    /* 
    int solveRec1(int n, int k) {
        if(n==1) return 1;
        return (solveRec1(n-1,k)+k-1)%n+1;
    }
    */ 

    int findTheWinner(int n, int k) {
        return solveRec1(n,k);
    }
};
