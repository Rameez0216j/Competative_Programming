#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct Event {
    int x, y1, y2, type; // x-coordinate, y-range, type (1 for start, -1 for end)
    Event(int x, int y1, int y2, int type) : x(x), y1(y1), y2(y2), type(type) {}
};

int rectangleArea(vector<vector<int>>& rectangles) {
    const int MOD = 1e9 + 7;
    vector<Event> events;
    
    // Create events for each rectangle
    for (auto& rect : rectangles) {
        events.push_back(Event(rect[0], rect[1], rect[3], 1));  // Start of rectangle
        events.push_back(Event(rect[2], rect[1], rect[3], -1)); // End of rectangle
    }

    // Sort events by x-coordinate
    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        return a.x < b.x;
    });

    multiset<pair<int, int>> activeSegments; // Active y-ranges
    int prevX = events[0].x;
    long long totalArea = 0;

    for (const auto& event : events) {
        // Calculate the total active y-length
        int currentYLength = 0;
        int prevY = -1;

        for (const auto& seg : activeSegments) {
            int y1 = seg.first, y2 = seg.second;
            currentYLength += max(0, y2 - max(y1, prevY));
            prevY = max(prevY, y2);
        }

        // Add the area for the previous x-interval
        totalArea += static_cast<long long>(currentYLength) * (event.x - prevX);
        totalArea %= MOD;

        // Update active segments
        if (event.type == 1) { // Start of a rectangle
            activeSegments.insert({event.y1, event.y2});
        } else { // End of a rectangle
            activeSegments.erase(activeSegments.find({event.y1, event.y2}));
        }

        prevX = event.x;
    }

    return totalArea;
}

int main() {
    vector<vector<int>> rectangles = {{1, 1, 3, 3}, {2, 2, 4, 4}, {2, 3, 3, 5}};
    cout << "Total rectangle area: " << rectangleArea(rectangles) << endl;
    return 0;
}