// ************************************** My solution **************************************
/*
class DinnerPlates {
    vector<stack<int>> stacks;
    set<int> availableStacks;
    int capacity;

    public:
    DinnerPlates(int capacity) {
        this->capacity=capacity;
    }
    
    void push(int val) {
        if(!availableStacks.empty()){
            int ind=*availableStacks.begin();
            stacks[ind].push(val);
            if(stacks[ind].size()==capacity) availableStacks.erase(ind);
        }else if(stacks.size()==0 || stacks.back().size()==capacity){
            stack<int> new_stack;
            if(stacks.size()!=0) availableStacks.erase(stacks.size()-1);
            stacks.push_back(new_stack);
            stacks.back().push(val);
            if(stacks.back().size() < capacity) availableStacks.insert(stacks.size()-1);
        }else{
            stacks.back().push(val);
            if(stacks.back().size() == capacity) availableStacks.insert(stacks.size()-1);
        }
    }
    
    int pop() {
        int val=-1;
        if(stacks.size()==0) return -1;
        while(!stacks.empty() && stacks.back().empty()){
            stacks.pop_back();
            availableStacks.erase(stacks.size());
        }

        if(stacks.empty()) return -1;

        
        val=stacks.back().top();
        stacks.back().pop();
        availableStacks.insert(stacks.size()-1);
        return val;
    }
    
    int popAtStack(int index) {
        if(index >= stacks.size()) return -1;
        if(stacks[index].empty()) return -1;
        int val=stacks[index].top();
        stacks[index].pop();
        availableStacks.insert(index);
        return val;
    }
};
*/
// ************************************** My solution **************************************












// ************************************** My solution [Cleaned] **************************************
class DinnerPlates {
    private:
    vector<stack<int>> stacks;         // List of stacks
    set<int> availableStacks;          // Indices of stacks with available space
    int capacity;                      // Capacity of each stack

    public:
    DinnerPlates(int capacity) {
        this->capacity = capacity;
    }

    void push(int val) {
        // If any stack has space, use the leftmost one
        if (!availableStacks.empty()) {
            int index = *availableStacks.begin();
            stacks[index].push(val);

            // If full after push, remove from available
            if (stacks[index].size() == capacity) {
                availableStacks.erase(index);
            }
        } else {
            // Either first push or last stack is full
            stack<int> newStack;
            newStack.push(val);
            stacks.push_back(newStack);

            // If the new stack is not full, mark it available
            if (capacity > 1) availableStacks.insert(stacks.size() - 1);
        }
    }

    int pop() {
        // Clean up empty stacks from the end
        while (!stacks.empty() && stacks.back().empty()) {
            availableStacks.erase(stacks.size() - 1);
            stacks.pop_back();
        }

        if (stacks.empty()) return -1;

        int val = stacks.back().top();
        stacks.back().pop();

        // If space becomes available, mark it
        if (stacks.back().size() < capacity) {
            availableStacks.insert(stacks.size() - 1);
        }

        // Clean up again if stack became empty
        while (!stacks.empty() && stacks.back().empty()) {
            availableStacks.erase(stacks.size() - 1);
            stacks.pop_back();
        }

        return val;
    }

    int popAtStack(int index) {
        if (index >= stacks.size() || stacks[index].empty()) {
            return -1;
        }

        int val = stacks[index].top();
        stacks[index].pop();

        // Mark it available since it now has space
        availableStacks.insert(index);

        return val;
    }
};
// ************************************** My solution [Cleaned] **************************************

/**
 * Your DinnerPlates object will be instantiated and called as such:
 * DinnerPlates* obj = new DinnerPlates(capacity);
 * obj->push(val);
 * int param_2 = obj->pop();
 * int param_3 = obj->popAtStack(index);
 */

