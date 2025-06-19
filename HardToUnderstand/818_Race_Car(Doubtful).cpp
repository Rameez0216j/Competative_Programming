// Solution 1
class Solution {
    public:
    int racecar(int target) {
        std::vector<int> dp(target + 1, -1);
        return dfs(target, dp);
    }

    int dfs(int target, std::vector<int>& dp) {
        if (dp[target] != -1) return dp[target];
        int min_steps = INT_MAX;

        // Try all k such that (2^k - 1) is the distance after k 'A' instructions
        for (int k = 1; ; ++k) {
            int distance_after_k_A = (1 << k) - 1;

            if (distance_after_k_A == target) {
                min_steps = k;  // Reached exactly with k accelerations
                break;
            }

            if (distance_after_k_A > target) {
                // Overshoot: reverse and come back
                min_steps = std::min(min_steps,
                                    k + 1 + dfs(distance_after_k_A - target, dp));
                break;
            }

            // Undershoot: move k steps, reverse, go back p steps (0 ≤ p < k)
            for (int p = 0; p < k; ++p) {
                int distance_back = (1 << p) - 1;
                int remaining = target - (distance_after_k_A - distance_back); // this never goes to negative

                // k A + 1 R + p A + 1 R + recurse
                int steps = k + 1 + p + 1 + dfs(remaining, dp);
                min_steps = std::min(min_steps, steps);
            }
        }

        return dp[target] = min_steps;
    }
};








// Solution 2
/*
License : This file is created by Paras Saini.
Question Link : https://leetcode.com/problems/race-car/
Solution Explanation : https://youtu.be/_Fm9JZDLYHg

*/

class CarAttributes{
private:
    int position,speed;

public:
    CarAttributes(int position,int speed)
    {
        this->position = position;
        this->speed = speed;
    }

    void setPosition(int position)
    {
        this->position = position;
    }

    void setSpeed(int speed)
    {
        this->speed = speed;
    }

    int getPosition()
    {
        return position;
    }

    int getSpeed()
    {
        return speed;
    }
    
};


class Solution {
    int target;
    
    bool isPositionNotFarFromTarget(int position,int target)
    {
        return abs(target - position) < target;
    }
    
    bool isValidInstruction(int position,unordered_set<string> &visSet,string &key,int target)
    {
        return !visSet.count(key) and isPositionNotFarFromTarget(position,target);
    }
    
    int getMinimumNumberOfInstructions()
    {
        int minimumNumberOfInstructions = 0;
        queue<CarAttributes> bfsQueue;
        unordered_set<string> visSet;
        string key = to_string(0) + "," + to_string(1);
        visSet.insert(key);
        bfsQueue.push(CarAttributes(0,1));
        
        // lambda function to deal with repititive work.
        auto moveToNextPos = [&](int nextPosition,int nextSpeed,CarAttributes &carAttribute,string &key){
            visSet.insert(key);
            carAttribute.setPosition(nextPosition);
            carAttribute.setSpeed(nextSpeed);
            bfsQueue.push(carAttribute);
        };
        
        while(!bfsQueue.empty())
        {
            int size = (int)bfsQueue.size();
            while(size--)
            {
                CarAttributes front = bfsQueue.front();
                bfsQueue.pop();
                int currPos = front.getPosition();
                int currSpd = front.getSpeed();

                if(currPos == target)
                return minimumNumberOfInstructions;

                // Explore option : "A" 
                int nextPos = currPos + currSpd;
                int nextSpd = currSpd * 2;
                key = to_string(nextPos) + "," + to_string(nextSpd);
                if(isValidInstruction(nextPos,visSet,key,target))
                {
                    moveToNextPos(nextPos,nextSpd,front,key);
                }
                
                // Explore option : "R"
                nextPos = currPos;
                nextSpd = currSpd < 0 ? 1 : -1;
                key = to_string(nextPos) + "," + to_string(nextSpd);
                if(isValidInstruction(nextPos,visSet,key,target))
                {
                     moveToNextPos(nextPos,nextSpd,front,key);
                }

            }
            minimumNumberOfInstructions += 1;
        }
        return -1;
    }

public:
    int racecar(int target) 
    {
        this->target = target;
        return getMinimumNumberOfInstructions();
    }
};