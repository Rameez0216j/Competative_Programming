// ********************************** My Solution [Eulerian path] **********************************
class Solution {
    public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        // Min-heap comparator for lexical order
        auto comp = [](const string& a, const string& b) {
            return a > b;  // min-heap (lexicographically smallest string on top)
        };

        // Adjacency list: each node maps to a min-heap of destinations
        unordered_map<string, priority_queue<string, vector<string>, decltype(comp)>> adjL;

        // Build the graph
        for (const auto& ticket : tickets) {
            string u=ticket[0];
            string v=ticket[1];
            adjL[u].push(v);
        }

        vector<string> itinerary;
        stack<string> st;
        st.push("JFK"); // start = "JFK" [given]

        // Hierholzer’s algorithm for Eulerian path
        while (!st.empty()) {
            string curr = st.top();
            if (!adjL[curr].empty()) {
                st.push(adjL[curr].top());
                adjL[curr].pop();
            } else {
                itinerary.push_back(curr);
                st.pop();
            }
        }

        reverse(itinerary.begin(), itinerary.end());
        return itinerary;
    }
};
// ********************************** My Solution [Eulerian path] **********************************
