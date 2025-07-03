// ********************************************** My Solution **********************************************
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int s1_count = 0;  // How many times we've scanned s1 so far
        int s2_count = 0;  // How many times we've matched full s2 so far
        int ind = 0;       // Index pointer in s2 (tracks current char match in s2)

        // Map to detect cycles: key = current index in s2, value = {s1_count, s2_count}
        unordered_map<int, pair<int, int>> mp;

        // Simulate repeating s1 n1 times
        while (s1_count < n1) {
            // For one full copy of s1, try to match s2
            for (char ch : s1) {
                if (ch == s2[ind]) {
                    ind++;
                    // One full s2 matched
                    if (ind == s2.size()) {
                        s2_count++;
                        ind = 0;  // Restart s2 match
                    }
                }
            }

            s1_count++;  // One s1 block processed

            // Check for a previously seen state (cycle detection)
            if (mp.find(ind) != mp.end()) {
                // Cycle found, calculate gain per loop
                int prev_s1_count = mp[ind].first;
                int prev_s2_count = mp[ind].second;

                int loop_s1 = s1_count - prev_s1_count;
                int loop_s2 = s2_count - prev_s2_count;

                // How many full loops can fit in remaining s1 blocks
                int remaining_s1 = n1 - s1_count;
                int num_loop = remaining_s1 / loop_s1;

                // Fast-forward through the loops
                s1_count += loop_s1 * num_loop;
                s2_count += loop_s2 * num_loop;

                break;  // No need to continue simulating; handled the looped part
            } else {
                // Save the state to detect future loops
                mp[ind] = {s1_count, s2_count};
            }

            // NOTE: This while loop is **not needed**, as the outer while already does this.
            // Keeping it would cause redundant iterations.
            while (s1_count < n1) {
                for (char ch : s1) {
                    if (ch == s2[ind]) {
                        ind++;
                        if (ind == s2.size()) {
                            s2_count++;
                            ind = 0;
                        }
                    }
                }
                s1_count++;
            }
        }

        // Return how many full s2^n2 fit into total matched s2
        return s2_count / n2;
    }
};
// ********************************************** My Solution **********************************************





// ********************************************** Editorial **********************************************
/*
int getMaxRepetitions(string s1, int n1, string s2, int n2)
{
    if (n1 == 0)
        return 0;
    int indexr[s2.size() + 1] = { 0 }; // index at start of each s1 block
    int countr[s2.size() + 1] = { 0 }; // count of repititions till the present s1 block
    int index = 0, count = 0;
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < s1.size(); j++) {
            if (s1[j] == s2[index])
                ++index;
            if (index == s2.size()) {
                index = 0;
                ++count;
            }
        }
        countr[i] = count;
        indexr[i] = index;
        for (int k = 0; k < i; k++) {
            if (indexr[k] == index) {
                int prev_count = countr[k];
                int pattern_count = (countr[i] - countr[k]) * (n1 - 1 - k) / (i - k);
                int remain_count = countr[k + (n1 - 1 - k) % (i - k)] - countr[k];
                return (prev_count + pattern_count + remain_count) / n2;
            }
        }
    }
    return countr[n1 - 1] / n2;
}
*/
// ********************************************** Editorial **********************************************