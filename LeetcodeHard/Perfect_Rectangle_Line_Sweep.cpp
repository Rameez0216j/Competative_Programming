// Method 1 (if overlapping is allowed)
/*
You can count the area of rectangles without overlapping regions and store it in total_area.
Now find out min_x,min_y, max_x, max_y and then calculate the area_needed=(max_x - min_x)*(max_y - min_y) 

return total_area==area_needed
*/

// Method 2 ( Overlapping is also not allowed)
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

bool isRectangleCover(vector<vector<int>>& rectangles) {
    // To track the total area
    long long totalArea = 0;
    int xMin = INT_MAX, yMin = INT_MAX;
    int xMax = INT_MIN, yMax = INT_MIN;

    // To count corner occurrences
    unordered_map<string, int> cornerCount;

    for (const auto& rect : rectangles) {
        int x1 = rect[0], y1 = rect[1], x2 = rect[2], y2 = rect[3];

        // Update bounding rectangle
        xMin = min(xMin, x1);
        yMin = min(yMin, y1);
        xMax = max(xMax, x2);
        yMax = max(yMax, y2);

        // Update total area
        totalArea += static_cast<long long>(x2 - x1) * (y2 - y1);

        // Count corners
        string corners[] = {to_string(x1) + "," + to_string(y1),
                            to_string(x1) + "," + to_string(y2),
                            to_string(x2) + "," + to_string(y1),
                            to_string(x2) + "," + to_string(y2)};
        for (const auto& corner : corners) {
            cornerCount[corner]++;
        }
    }

    // Calculate the area of the bounding rectangle
    long long boundingArea = static_cast<long long>(xMax - xMin) * (yMax - yMin);

    // Check if the total area matches the bounding rectangle's area
    if (totalArea != boundingArea) {
        return false;
    }

    // Check corner occurrences
    int oddCorners = 0;
    for (const auto& [corner, count] : cornerCount) {
        if (count % 2 == 1) {
            oddCorners++;
        }
    }

    // There should be exactly four corners appearing an odd number of times
    return oddCorners == 4;
}

int main() {
    vector<vector<int>> rectangles = {
        {1, 1, 3, 3}, {3, 1, 4, 2}, {3, 2, 4, 4},
        {1, 3, 2, 4}, {2, 3, 3, 4}};
    cout << (isRectangleCover(rectangles) ? "True" : "False") << endl;
    return 0;
}