/*
===============================================
Difference between push_back() and emplace_back()
===============================================

1. push_back():
   - Constructs the object outside the container.
   - Then copies or moves the object into the container.
   - Syntax: v.push_back(make_pair(1, 2));
   - Less efficient for complex objects due to extra copy/move.

2. emplace_back():
   - Constructs the object directly in-place inside the container.
   - Avoids unnecessary copy/move operations.
   - Syntax: v.emplace_back(1, 2);  // No need for make_pair
   - Preferred for performance, especially with user-defined types.

3. When to use:
   - For simple types (like int, pair<int, int>), both are similar.
   - For complex or large objects, always prefer emplace_back().

Example:
--------------------------------
vector<pair<int, int>> v;

v.push_back(make_pair(1, 2));   // Uses copy/move
v.emplace_back(1, 2);           // Directly constructs pair<int, int>(1, 2)

Conclusion:
   emplace_back() is more efficient and should be the default choice
   unless you already have a constructed object to insert.
*/




// ********************************************* My Solution  *********************************************
// If there are multiple possibilities based on constraints like time and lower of it is getting priority then instead on visited array we use an array as time used below
class Solution {
public:
    int solveDijkshtra(int start, int target,
                       unordered_map<int, vector<pair<int, int>>> &adjL,
                       vector<int>& passingFees, int maxTime) {
        int n = passingFees.size();
        vector<int> time(n, INT_MAX);
        time[start] = 0;

        auto comp = [](vector<int> &a, vector<int> &b) {
            if (a[1] == b[1]) return a[0] > b[0];  // If cost equal, prefer lower time
            return a[1] > b[1];                    // Prefer lower cost
        };

        priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> pq(comp);
        pq.push({0, passingFees[start], start});  // {time, cost, currNode}

        while (!pq.empty()) {
            int curr_time = pq.top()[0];
            int curr_cost = pq.top()[1];
            int curr_node = pq.top()[2];
            pq.pop();

            if (curr_time > maxTime) continue;
            if (curr_node == target) return curr_cost;

            for (auto& ele : adjL[curr_node]) {
                int nbr = ele.first;
                int t = ele.second;

                int new_time = curr_time + t;
                int new_cost = curr_cost + passingFees[nbr];

                if (new_time <= maxTime && new_time < time[nbr]) {
                    time[nbr] = new_time;  // ✅ ✅ CRITICAL LINE
                    pq.push({new_time, new_cost, nbr});
                }
            }
        }

        return -1;
    }

    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        unordered_map<int, unordered_map<int, int>> filter;

        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], t = edge[2];

            if (filter[u].count(v)) {
                filter[u][v] = min(filter[u][v], t);
                filter[v][u] = min(filter[v][u], t);
            } else {
                filter[u][v] = t;
                filter[v][u] = t;
            }
        }

        unordered_map<int, vector<pair<int, int>>> adjL;
        for (auto& [u, neighbors] : filter) {
            for (auto& [v, t] : neighbors) {
                adjL[u].emplace_back(v, t);  // (neighbor, time)
            }
        }

        int n = passingFees.size();
        return solveDijkshtra(0, n - 1, adjL, passingFees, maxTime);
    }
};
// ********************************************* My Solution  *********************************************






// ********************************* My Solution [improved and with notes] *********************************
// TUPLE : A tuple is an object that can hold a number of elements. The elements can be of different data types. 
/*
class Solution {
    public:
    // Dijkstra variant: minimize cost with time constraint
    int solveDijkstra(int start, int target, unordered_map<int, vector<pair<int, int>>> &adjL,
                      vector<int>& passingFees, int maxTime) {
        int n = passingFees.size();

        // Min-heap priority queue: {total_time, total_cost, node}
        using T = tuple<int, int, int>; // time, cost, node
        auto comp = [](const T &a, const T &b) {
            // Minimize cost; if equal cost, minimize time
            if (get<1>(a) == get<1>(b)) return get<0>(a) > get<0>(b);
            return get<1>(a) > get<1>(b);
        };

        priority_queue<T, vector<T>, decltype(comp)> pq(comp);
        pq.emplace(0, passingFees[start], start);  // Initial state

        // time[node] = minimum time taken to reach node with any cost
        vector<int> time(n, INT_MAX);
        time[start] = 0;

        while (!pq.empty()) {
            auto [curr_time, curr_cost, curr_node] = pq.top();
            pq.pop();

            // If time exceeds limit, skip
            if (curr_time > maxTime) continue;

            // If reached target within time, return cost
            if (curr_node == target) return curr_cost;

            for (auto &[nbr, edge_time] : adjL[curr_node]) {
                int new_time = curr_time + edge_time;
                int new_cost = curr_cost + passingFees[nbr];

                // Only process if we reach nbr in less time than before
                if (new_time <= maxTime && new_time < time[nbr]) {
                    time[nbr] = new_time;
                    pq.emplace(new_time, new_cost, nbr);
                }
            }
        }

        return -1; // Not reachable within maxTime
    }

    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        int n = passingFees.size();

        // Step 1: Filter multiple edges — keep only min-time edge between two nodes
        unordered_map<int, unordered_map<int, int>> filter;
        for (auto &edge : edges) {
            int u = edge[0], v = edge[1], t = edge[2];
            if (filter[u].count(v)) {
                filter[u][v] = min(filter[u][v], t);
                filter[v][u] = min(filter[v][u], t);
            } else {
                filter[u][v] = t;
                filter[v][u] = t;
            }
        }

        // Step 2: Build adjacency list using filtered edges
        unordered_map<int, vector<pair<int, int>>> adjL;
        for (auto &[u, neighbors] : filter) {
            for (auto &[v, t] : neighbors) {
                adjL[u].emplace_back(v, t);  // (neighbor, time)
            }
        }

        // Step 3: Run modified Dijkstra
        return solveDijkstra(0, n - 1, adjL, passingFees, maxTime);
    }
};
*/
// ********************************* My Solution [improved and with notes] *********************************
