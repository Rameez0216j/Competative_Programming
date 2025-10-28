// Video Lecture : https://www.youtube.com/watch?v=cQ5MsiGaDY8

/*
====================================================================
🎯 Hungarian Algorithm (a.k.a. Kuhn-Munkres)
====================================================================

📘 Goal:
--------
Find the *minimum cost* matching (or maximum profit) between
two sets (Left and Right), where each edge (i, j) has a cost matrix A[i][j].

🧩 Problem Type:
----------------
Assignment Problem:
- You have n workers and m jobs.
- A[i][j] = cost for worker i doing job j.
- You must assign each worker exactly one job (or vice versa)
  minimizing the total cost (or maximizing total profit).

====================================================================
*/


// DRY RUN BELOW CODE FOR BETTER UNDERSTANDING
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    int numWorkers, numJobs;
    cin >> numWorkers >> numJobs; // Usually numWorkers == numJobs

    vector<vector<int>> costMatrix(numWorkers + 1, vector<int>(numJobs + 1));
    for (int i = 1; i <= numWorkers; ++i)
        for (int j = 1; j <= numJobs; ++j)
            cin >> costMatrix[i][j]; // costMatrix[i][j] = cost of assigning worker i → job j

    /*
    ==========================================================
    🧩 Vector Meaning and Roles
    ==========================================================

    workerPotential (u[i]) → potential (label) for each worker
        - helps adjust reduced costs during optimization

    jobPotential (v[j]) → potential (label) for each job
        - works together with worker potentials to keep costs balanced

    jobMatch (p[j]) → which worker is currently assigned to job j
        - p[j] = i means job j is currently matched with worker i

    previousJob (way[j]) → used to reconstruct the augmenting path
        - helps trace back when updating the matching

    minReducedCost (minv[j]) → minimal reduced cost seen for job j
        - used during scanning to decide the next job to process

    jobUsed (used[j]) → marks if a job was visited in the current iteration
        - prevents revisiting the same job in one matching attempt
    ==========================================================
    */

    vector<int> workerPotential(numWorkers + 1), jobPotential(numJobs + 1);
    vector<int> jobMatch(numJobs + 1), previousJob(numJobs + 1);

    // Hungarian Algorithm core
    for (int currentWorker = 1; currentWorker <= numWorkers; ++currentWorker) {
        jobMatch[0] = currentWorker; // "fake" start node
        int currentJob = 0; // current job index (starts from dummy 0)

        vector<int> minReducedCost(numJobs + 1, INF);
        vector<bool> jobUsed(numJobs + 1, false);

        do {
            jobUsed[currentJob] = true;
            int workerMatchedToJob = jobMatch[currentJob]; // currently matched worker
            int delta = INF, nextJob = 0;

            for (int job = 1; job <= numJobs; ++job) {
                if (!jobUsed[job]) {
                    int reducedCost = costMatrix[workerMatchedToJob][job] - workerPotential[workerMatchedToJob] - jobPotential[job];

                    // found better (smaller reduced cost) edge
                    if (reducedCost < minReducedCost[job]) {
                        minReducedCost[job] = reducedCost;
                        previousJob[job] = currentJob;
                    }

                    if (minReducedCost[job] < delta) {
                        delta = minReducedCost[job];
                        nextJob = job;
                    }
                }
            }

            // Adjust potentials (labels)
            for (int job = 0; job <= numJobs; ++job) {
                if (jobUsed[job]) {
                    workerPotential[jobMatch[job]] += delta;
                    jobPotential[job] -= delta;
                } else {
                    minReducedCost[job] -= delta;
                }
            }

            currentJob = nextJob;
        } while (jobMatch[currentJob] != 0);

        // Reconstruct augmenting path and update the matching
        do {
            int prev = previousJob[currentJob];
            jobMatch[currentJob] = jobMatch[prev];
            currentJob = prev;
        } while (currentJob);
    }

    // Construct final matching (Worker → Job)
    vector<int> workerToJob(numWorkers + 1);
    for (int j = 1; j <= numJobs; ++j)
        workerToJob[jobMatch[j]] = j;

    int totalCost = -jobPotential[0];

    cout << "Minimum Cost = " << totalCost << "\n";
    for (int i = 1; i <= numWorkers; ++i)
        cout << "Worker " << i << " → Job " << workerToJob[i] << "\n";

    return 0;
}

/*
====================================================================
📘 Example:
--------------------------------------------------------------------
Workers (L):  W1, W2, W3
Jobs (R):     J1, J2, J3

Cost Matrix (costMatrix[i][j]):
    J1  J2  J3
W1  3   2   1
W2  2   4   6
W3  4   5   3

✅ Optimal Assignment:
W1 → J3
W2 → J1
W3 → J2
Total Minimum Cost = 1 + 2 + 5 = 8

====================================================================
🎯 Tips & Tricks | Pattern Recognition
--------------------------------------------------------------------
🧠 Where used:
- "Assignment problems" → assigning tasks/jobs to agents
- Minimizing cost or maximizing efficiency
- Classic in operations research, scheduling, or resource allocation

🔍 How to recognize this pattern:
- You’re given two sets of equal size (workers, jobs)
- Each edge (i, j) has a cost
- You must assign each worker exactly one job minimizing total cost

🏹 Related Problems (LeetCode, HARD):
- 1595. Minim


/*
====================================================================
📘 NOTES (for Quick Revision)
====================================================================

🔹 Core Idea:
--------------
Hungarian Algorithm solves *weighted bipartite matching*
where each edge (i, j) has a cost/profit.

It maintains *potential functions (u, v)* for both sides
and uses them to find augmenting paths of minimal reduced cost.

🔹 Pattern Recognition:
-----------------------
When you see a problem asking:
  - "Assign items optimally with minimum/maximum cost."
  - "Match workers to tasks for maximum profit."
  - "Optimal assignment matrix / pairing problem."
→ It’s **Hungarian Algorithm (Assignment Problem)**

🔹 Real-world Use Cases:
------------------------
- Job assignment optimization
- Task scheduling
- Resource allocation
- Matching users to servers for minimal latency
- Pairing taxis to riders with minimal total distance

🔹 Time Complexity:
------------------
O(n² * m)
(Usually n == m → O(n³))

🔹 Tips:
--------
✅ For maximum profit instead of minimum cost,
   multiply all A[i][j] by -1 before running algorithm.

✅ For dense matrices, Hungarian is preferred over flow-based methods.

🔹 Related LeetCode HARD Problems:
---------------------------------
- 1349. Maximum Students Taking Exam
- 1681. Minimum Incompatibility
- 2127. Maximum Employees to Be Invited to a Meeting
- 1947. Maximum Compatibility Score Sum
- 630. Course Schedule III (conceptually related)

====================================================================
*/


