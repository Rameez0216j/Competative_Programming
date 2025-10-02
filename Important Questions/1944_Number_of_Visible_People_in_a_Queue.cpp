// Solution : https://www.youtube.com/watch?v=AFCFihGW09Y&t=79s
// ************************************* My Solution *************************************
class Solution
{
public:
    vector<int> canSeePersonsCount(vector<int> &heights)
    {
        int n = heights.size();
        vector<int> visibleCount(n, 0); // Stores number of people each person can see
        stack<int> indexStack;          // Monotonic stack storing indices of people

        for (int i = 0; i < n; i++)
        {

            // -----------------------------
            // Step 1: Pop all shorter people in front
            // While the stack is not empty and current person is taller than
            // the person at top of stack:
            //    - The person at top can see the current person
            //    - Increment their visible count by 1
            //    - Remove them from stack since they are "blocked" by current person
            // -----------------------------
            while (!indexStack.empty() && heights[indexStack.top()] < heights[i])
            {
                visibleCount[indexStack.top()] += 1;
                indexStack.pop();
            }

            // -----------------------------
            // Step 2: If a taller/equal person remains on stack,
            // they can also see the current person (but are not blocked)
            // -----------------------------
            if (!indexStack.empty())
            {
                visibleCount[indexStack.top()] += 1;
            }

            // -----------------------------
            // Step 3: Push current person's index to stack
            // They may be seen by future taller people
            // -----------------------------
            indexStack.push(i);
        }

        return visibleCount;
    }
};
// ************************************* My Solution *************************************
