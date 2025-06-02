// Solution : https://www.youtube.com/watch?v=b12SZXrZF9I&t=596s
// ********************************************* My Solution *********************************************
/*
class Solution {
    public:
    // Pure Profit ==> netProfit
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n=profits.size();
        
        // sorting projects by capital in ascending order
        vector<pair<int,int>> projects;
        for(int i=0;i<n;i++) projects.push_back({capital[i],profits[i]});
        auto comp=[](pair<int,int> &a, pair<int,int> &b) {
            return a.first < b.first;
        };
        sort(projects.begin(),projects.end(),comp);
        
        priority_queue<int> pq; // To track max profit we can get
        int ind=0;
        while(ind<n && k){
            while(ind<n && projects[ind].first <= w){
                pq.push(projects[ind].second);
                ind++;
            }
            if(!pq.empty()){
                w=(w+pq.top());
                pq.pop();
                k--;
            }else break; // if there is no element in priority queue then it means nothing is less than the w to buy
        }

        while(!pq.empty() && k){
            w=(w+pq.top());
            pq.pop();
            k--;
        }

        return w;
    }
};
*/
// ********************************************* My Solution *********************************************






// ************************************ My Solution [cleaned and optimized] ************************************
class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n = profits.size();

        // Build and sort projects by capital
        vector<pair<int, int>> projects;
        for (int i = 0; i < n; ++i)
            projects.emplace_back(capital[i], profits[i]);

        sort(projects.begin(), projects.end(),
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 return a.first < b.first;
             });

        priority_queue<int> pq; // max-heap for profits
        int ind = 0;

        while (k--) {
            // Push all affordable projects into the heap
            while (ind < n && projects[ind].first <= w) pq.push(projects[ind++].second);

            if (pq.empty()) break; // No affordable projects

            w += pq.top(); // Choose most profitable
            pq.pop();
        }

        return w;
    }
};

// ************************************ My Solution [cleaned and optimized] ************************************


/*
    Difference between push_back and emplace_back:

    push_back:
    - Requires a constructed object.
    - May cause an extra copy or move.
    - Example:
        vector<pair<int, int>> v;
        v.push_back(make_pair(1, 2)); // Creates pair first, then pushes it

    emplace_back:
    - Constructs the object directly inside the vector.
    - Avoids copy/move; more efficient and cleaner.
    - Example:
        vector<pair<int, int>> v;
        v.emplace_back(1, 2); // Constructs pair<int, int>(1, 2) directly in place

    Another example with a custom struct:

        struct Student {
            string name;
            int age;
            Student(string n, int a) : name(n), age(a) {}
        };

        vector<Student> students;

        // Less efficient: creates a temporary Student, then pushes it
        students.push_back(Student("Rameez", 24));

        // More efficient: constructs Student directly in vector memory
        students.emplace_back("Rameez", 24);

    Rule of Thumb:
    - Use emplace_back when constructing objects directly in the container.
    - Use push_back when you already have a constructed object.
*/

