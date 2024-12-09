//Method 1 (2 pass Greedy approach)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int candy(vector<int>& ratings) {
    int n = ratings.size();
    vector<int> candies(n, 1); // Initially, give 1 candy to each child.

    // Forward pass
    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }

    // Backward pass
    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            candies[i] = max(candies[i], candies[i + 1] + 1);
        }
    }

    // Calculate the total number of candies
    return accumulate(candies.begin(), candies.end(), 0);
}

int main() {
    vector<int> ratings = {1, 0, 2};
    cout << "Minimum candies required: " << candy(ratings) << endl;
    return 0;
}




// Method 2 (Single pass Heap based approach)
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int candy(vector<int>& ratings) {
    int n = ratings.size();
    vector<int> candies(n, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Push all ratings with their indices into the min-heap
    for (int i = 0; i < n; i++) {
        pq.push({ratings[i], i});
    }

    // Assign candies based on heap order
    while (!pq.empty()) {
        auto [rating, i] = pq.top();
        pq.pop();

        // Max of 1 or 1 + neighbor's candies
        candies[i] = 1;
        if (i > 0 && ratings[i] > ratings[i - 1]) {
            candies[i] = max(candies[i], candies[i - 1] + 1);
        }
        if (i < n - 1 && ratings[i] > ratings[i + 1]) {
            candies[i] = max(candies[i], candies[i + 1] + 1);
        }
    }

    // Calculate the total number of candies
    return accumulate(candies.begin(), candies.end(), 0);
}

int main() {
    vector<int> ratings = {1, 0, 2};
    cout << "Minimum candies required: " << candy(ratings) << endl;
    return 0;
}




//Method 3 (Mathematical peak and valley approach)
#include <iostream>
#include <vector>
using namespace std;

int candy(vector<int>& ratings) {
    int n = ratings.size();
    if (n == 1) return 1;

    int totalCandies = 0;
    int i = 0;

    while (i < n) {
        // Find length of increasing sequence
        int inc = 0;
        while (i + 1 < n && ratings[i] < ratings[i + 1]) {
            inc++;
            i++;
        }

        // Find length of decreasing sequence
        int dec = 0;
        while (i + 1 < n && ratings[i] > ratings[i + 1]) {
            dec++;
            i++;
        }

        // Calculate the candies for the peak (1 at the peak)
        // Here inc and dec sequence exclude peak
        totalCandies += (inc * (inc + 1)) / 2 + (dec * (dec + 1)) / 2 + max(inc, dec) + 1;

        // Move pointer if it's flat
        while (i + 1 < n && ratings[i] == ratings[i + 1]) {
            totalCandies += 1;
            i++;
        }
    }

    return totalCandies;
}

int main() {
    vector<int> ratings = {1, 2, 2, 3, 4, 3, 2, 1};
    cout << "Minimum candies required: " << candy(ratings) << endl;
    return 0;
}