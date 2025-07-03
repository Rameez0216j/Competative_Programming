// Solution : https://www.youtube.com/watch?v=Ns47YIWMuKs&t=700s
// ************************************ My Solution ************************************
class Solution {
    public:
    long long minDamage(int power, vector<int>& damage, vector<int>& health) {
        int n=damage.size();
        vector<pair<int,int>> arr;
        for(int i=0;i<n;i++){
            int dmg=damage[i];
            int hlt=health[i];
            int turnsToDie= hlt/power + (hlt%power !=0 ? 1 : 0);
            arr.push_back({dmg,turnsToDie});
        }

        auto comp=[](pair<int,int> &a,pair<int,int> &b){
            // This compares who deals more damage while other is dying 
            return 1LL*a.first*b.second > 1LL*b.first*a.second;
        };

        sort(arr.begin(),arr.end(),comp);
        long long int ans=0;
        int turns=0;
        for(int i=0;i<n;i++){
            ans+=(1LL * arr[i].first*(arr[i].second + turns));
            turns+=arr[i].second;
        }
        return ans;
    }
};
// ************************************ My Solution ************************************







// ************************************ My Solution [Code with Explaination] ************************************
/*
class Solution {
    public:
    long long minDamage(int power, vector<int>& damage, vector<int>& health) {
        int n = damage.size();

        // Step 1: Preprocess monsters — store each as (damage per turn, turns to kill)
        vector<pair<int, int>> arr;
        for (int i = 0; i < n; i++) {
            int dmg = damage[i];
            int hlt = health[i];

            // Calculate number of turns required to kill monster i
            // turnsToDie = ceil(health / power)
            int turnsToDie = hlt / power + (hlt % power != 0 ? 1 : 0);

            arr.push_back({dmg, turnsToDie});
        }

        // Step 2: Sort monsters in an order that minimizes total damage taken
        auto comp = [](pair<int, int>& a, pair<int, int>& b) {
            // This compares who deals more damage while other is dying 
            // Greedy logic: compare based on relative damage × time
            // If a.first * b.second > b.first * a.second → 'a' should come before 'b'
            // 1LL is used to prevent integer overflow during multiplication
            return 1LL * a.first * b.second > 1LL * b.first * a.second;
        };

        sort(arr.begin(), arr.end(), comp);

        // Step 3: Compute total damage received by hero
        long long ans = 0;   // Total damage accumulated
        int turns = 0;       // Total turns passed so far

        for (int i = 0; i < n; i++) {
            int dmg = arr[i].first;
            int time = arr[i].second;

            // Each monster inflicts damage every turn until it dies
            // Total damage from this monster = damage × (turns spent before + time to kill)
            ans += 1LL * dmg * (turns + time);

            // Update total turns spent after killing this monster
            turns += time;
        }

        return ans;
    }
};
*/
// ************************************ My Solution [Code with Explaination] ************************************
