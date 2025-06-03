class Solution {
    public:
    /*
        Problem: LeetCode 829 - Consecutive Numbers Sum

        Goal: Given an integer n, find the number of ways to write n as the sum of 
            consecutive positive integers.

        Observation:
        - Any sequence of consecutive positive integers can be represented as:
            k + (k+1) + (k+2) + ... + (k + m - 1)
        where:
            - k is the starting number (k >= 1)
            - m is the number of terms in the sequence (m >= 1)

        - The sum of this arithmetic sequence is:
            Sum = m/2 * (2k + m - 1)

        We want this sum to equal 'n':
            (m/2) * (2k + m - 1) = n

        Rearranging:
        => m * (2k + m - 1) = 2n
        => 2k + m - 1 = (2n) / m
        => 2k = (2n / m) - (m - 1)
        => k = ((2n / m) - (m - 1)) / 2

        To ensure k is a positive integer:
        1. (2n / m) must be an integer ⇒ m must divide 2n
        2. ((2n / m) - (m - 1)) must be even
        3. The final result k must be ≥ 1

        Approach:
        - Loop through all possible values of m from 1 to sqrt(2n)
        - For each m, check if m divides 2n
        - For valid m, compute k using the rearranged formula
        - If k is a positive integer, increment the answer count

        This approach runs in O(√n) time and avoids brute-force checking all sequences.



        NOTE:
        We only consider m (the sequence length) from the divisor pair (m, 2n/m) 
        because using the second value (2n/m) as m usually leads to a negative or 
        non-positive starting number k.

        Proof:
        -----------
        The formula derived from the sum of consecutive numbers is:
            k = ((2n / m) - (m - 1)) / 2

        Now assume 2n/m = M (i.e., the other divisor in the pair), where M ≥ m.
        Let’s write M = m + x for some x ≥ 0

        Then:
            ((2n / M) - (M - 1)) 
        =   (m - 1) - (m + x - 1) 
        =   m - 1 - m - x + 1 
        =   -x  → which is negative or zero!

        Hence, using M = 2n/m as the sequence length results in:
            ((2n / M) - (M - 1)) / 2 = (-x) / 2 ≤ 0 → Invalid!

        So, we safely ignore the larger value of each divisor pair (2n/m) as a 
        potential sequence length. Iterating only over m up to sqrt(2n) is correct and complete.

    */
    
    int consecutiveNumbersSum(int num) {
        int ans=0;
        for(int m=1;m*m<=2*num;m++){
            // (2*num/m)-(m-1)>0 as 0 is not included in the AP
            if((2*num)%m!=0) continue;

            int val=((2*num)/m)-(m-1);
            if(val>0 && val%2==0) ans++;
        }
        return ans;
    }


};