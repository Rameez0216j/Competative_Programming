// Solution : https://www.youtube.com/watch?v=CAoBD84G2gI&t=2462s
// ********************************************* My solution *********************************************
class Solution {
    public:
    vector<int> ans; // Stores the smallest sufficient team found so far

    // Backtracking without memoization
    void solveRec(int ind, int currSkills, int reqSkills, vector<int> &team, vector<int> &peopleSkills) {
        if (ind >= peopleSkills.size()) {
            // Base case: All people considered
            if (currSkills == reqSkills) {
                // Check if this team covers all required skills
                // Update the answer if it's smaller
                if (ans.size() == 0 || ans.size() > team.size())
                    ans = team;
            }
            return;
        }

        // Choice 1: Include current person
        team.push_back(ind);
        solveRec(ind + 1, currSkills | peopleSkills[ind], reqSkills, team, peopleSkills);
        team.pop_back();

        // Choice 2: Exclude current person
        solveRec(ind + 1, currSkills, reqSkills, team, peopleSkills);
    }

    // Optimized backtracking with memoization (pruning)
    void solveRecMem(int ind, int currSkills, int &reqSkills, vector<int> &team, vector<int> &peopleSkills, vector<vector<int>> &dp) {
        if (ind >= peopleSkills.size()) {
            if (currSkills == reqSkills) {
                if (ans.size() == 0 || ans.size() > team.size())
                    ans = team;
            }
            return;
        }

        // Prune if we already reached this state with a smaller team
        if (dp[ind][currSkills] != -1 && dp[ind][currSkills] <= team.size())
            return;

        // Choice 1: Include current person (only if they add new skills)
        if ((currSkills | peopleSkills[ind]) != currSkills) {
            team.push_back(ind);
            solveRecMem(ind + 1, currSkills | peopleSkills[ind], reqSkills, team, peopleSkills, dp);
            team.pop_back();
        }

        // Choice 2: Exclude current person
        solveRecMem(ind + 1, currSkills, reqSkills, team, peopleSkills, dp);

        // Memoize the minimum team size for this state
        dp[ind][currSkills] = team.size();
    }

    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        int n = req_skills.size(); // Number of required skills

        // Map each skill to a unique bit position
        unordered_map<string, int> mp;
        for (int i = 0; i < n; i++)
            mp[req_skills[i]] = i;

        int p = people.size();
        vector<int> peopleSkills; // Bitmask representation of each person's skillset

        // Convert each person's skills to a bitmask
        for (int i = 0; i < p; i++) {
            int skillPoints = 0;
            for (string skill : people[i])
                skillPoints |= (1 << mp[skill]);
            peopleSkills.push_back(skillPoints);
        }

        int reqSkills = (1 << n) - 1; // Bitmask representing all required skills
        vector<int> team;

        // Recursion + Memoization approach
        vector<vector<int>> dp(p + 1, vector<int>(reqSkills + 1, -1));
        solveRecMem(0, 0, reqSkills, team, peopleSkills, dp);

        return ans;
    }
};
// ********************************************* My solution *********************************************