#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    int numWorkers, numJobs;
    cin >> numWorkers >> numJobs;
    vector<vector<int>> cost(numWorkers + 1, vector<int>(numJobs + 1));

    // Input cost matrix
    for (int i = 1; i <= numWorkers; ++i)
        for (int j = 1; j <= numJobs; ++j)
            cin >> cost[i][j];

    // These store potential adjustments (like prices)
    vector<int> workerPotential(numWorkers + 1, 0); // u[i]
    vector<int> jobPotential(numJobs + 1, 0);       // v[j]

    // jobMatch[j] = which worker is assigned to job j
    vector<int> jobMatch(numJobs + 1, 0);

    // Helps trace back augmenting paths
    vector<int> previousJob(numJobs + 1, 0);

    // Step through each worker and try to find them a job
    for (int worker = 1; worker <= numWorkers; ++worker) {
        // Step 1: Initialization
        jobMatch[0] = worker;          // Start with dummy job 0
        int currentJob = 0;            // Job we’re currently processing
        vector<int> minCost(numJobs + 1, INF);  // Best reduced cost so far for each job
        vector<bool> jobVisited(numJobs + 1, false);

        // Step 2: Dijkstra-like loop to find best augmenting path
        while (true) {
            jobVisited[currentJob] = true;
            int workerMatchedToCurrentJob = jobMatch[currentJob]; // Worker currently matched to this job
            int bestDelta = INF;
            int nextJob = 0;

            // Try all jobs to find the next edge to explore
            for (int job = 1; job <= numJobs; ++job) {
                if (jobVisited[job]) continue;

                // Reduced cost = actual cost adjusted by potentials
                int reducedCost = cost[workerMatchedToCurrentJob][job]
                                  - workerPotential[workerMatchedToCurrentJob]
                                  - jobPotential[job];

                // Found a cheaper connection to this job
                if (reducedCost < minCost[job]) {
                    minCost[job] = reducedCost;
                    previousJob[job] = currentJob; // remember the path
                }

                // Pick job with smallest current reduced cost
                if (minCost[job] < bestDelta) {
                    bestDelta = minCost[job];
                    nextJob = job;
                }
            }

            // Step 3: Adjust potentials so nextJob becomes reachable with reduced cost = 0
            for (int job = 0; job <= numJobs; ++job) {
                if (jobVisited[job]) {
                    // Increase potential of workers in the alternating tree
                    workerPotential[jobMatch[job]] += bestDelta;
                    // Decrease potential of visited jobs
                    jobPotential[job] -= bestDelta;
                } else {
                    // For unvisited jobs, just reduce their minCost (path distance)
                    minCost[job] -= bestDelta;
                }
            }

            currentJob = nextJob;

            // When we reach an unmatched job, we found an augmenting path
            if (jobMatch[currentJob] == 0)
                break;
        }

        // Step 4: Augment the matching (flip along the path)
        while (currentJob) {
            int prev = previousJob[currentJob];
            jobMatch[currentJob] = jobMatch[prev];
            currentJob = prev;
        }
    }

    // Compute final matching cost
    int totalCost = 0;
    for (int job = 1; job <= numJobs; ++job)
        totalCost += cost[jobMatch[job]][job];

    cout << "Minimum Cost = " << totalCost << "\n";
    for (int job = 1; job <= numJobs; ++job)
        cout << "Worker " << jobMatch[job] << " -> Job " << job << "\n";
}



