// ****************************** My Solution [Monotonic stack] ******************************
class Solution {
public:
    vector<double> getCollisionTimes(vector<vector<int>>& cars) {
        int n = cars.size();
        vector<double> collisionTime(n, -1);
        stack<int> st; // Stack to keep track of potential collisions

        for (int curr = n - 1; curr >= 0; --curr) {
            // Remove cars ahead that are slower or moving at same speed (no collision)
            while (!st.empty() && cars[st.top()][1] >= cars[curr][1]) {
                st.pop();
            }

            while (!st.empty()) {
                int next = st.top();
                double distance = cars[next][0] - cars[curr][0];
                double speedDiff = cars[curr][1] - cars[next][1];
                double timeToCollide = distance / speedDiff;

                // Check if the car ahead will not collide before this one reaches it
                if (collisionTime[next] == -1 || timeToCollide <= collisionTime[next]) {
                    collisionTime[curr] = timeToCollide;
                    break;
                }

                st.pop();
            }

            st.push(curr);
        }

        return collisionTime;
    }
};
// ****************************** My Solution [Monotonic stack] ******************************



