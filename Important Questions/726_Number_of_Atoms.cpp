// ***************************************** My Solution *****************************************
/*
class Solution {
    public:
    string countOfAtoms(string formula) {
        stack<unordered_map<string,int>> st;
        st.push(unordered_map<string,int> ());
        
        int n=formula.size();
        int ind=0;
        while(ind<n){
            if(formula[ind]=='('){
                unordered_map<string,int> temp;
                st.push(temp);
                
                // Move the pointer
                ind++;
            }else if(formula[ind]==')'){
                unordered_map<string,int> temp=st.top();
                st.pop();
                
                ind++;
                // parse the number
                string count="";
                while(ind<n && formula[ind]>='0' && formula[ind]<='9') count+=formula[ind++];
                int multiplier = count == "" ? 1 : stoi(count);
                
                for(auto ele:temp){
                    string atom=ele.first;
                    int atomCount=ele.second;
                    st.top()[atom]+=(atomCount*multiplier);
                }                
            }else{
                // Parse the atom
                string atom="";
                atom+=formula[ind++];
                while(ind<n && formula[ind]>='a' && formula[ind]<='z') atom+=formula[ind++];

                // Parse the count
                string num="";
                while(ind<n && formula[ind]>='0' && formula[ind]<='9') num+=formula[ind++];
                int count = (num == "") ? 1 : stoi(num);

                st.top()[atom]+=count;
            }
        } 


        map<string,int> finalFreq(st.top().begin(),st.top().end());
        string ans="";
        for(auto ele:finalFreq){
            ans+=ele.first;
            if(ele.second>1) ans+=to_string(ele.second);
        }
        return ans;
    }
};
*/
// ***************************************** My Solution *****************************************






// Solution : https://www.youtube.com/watch?v=XnVWIT47H0Y
/*
    Why we push an empty map at the very beginning of the stack:
    
    Consider the formula: "(NB3)33"

    1. We encounter '(', so we push a new empty map onto the stack for this group.
    2. We parse:
       - 'N' → count = 1 → map becomes { "N": 1 }
       - 'B3' → count = 3 → map becomes { "N": 1, "B": 3 }
    3. We then encounter ')33':
       - We pop the top map { "N": 1, "B": 3 }
       - Parse multiplier: 33
       - Multiply all values: { "N": 33, "B": 99 }

    ⚠️ Now we try to merge this map into st.top()
       BUT... if there was nothing in the stack before the first '(', we just popped the only map.
       So st.top() is now invalid — leads to a runtime error or undefined behavior.

    ✅ That's why we push a dummy/global empty map at the very beginning.
       It serves as the outermost container, ensuring there is always at least one map
       in the stack when merging any group (even if the entire formula is inside parentheses).
*/
// ***************************************** Cleaned Solution *****************************************
class Solution {
    public:
    string countOfAtoms(string formula) {
        stack<unordered_map<string, int>> st; // Stack to handle nested groups
        st.push(unordered_map<string, int>());
        int n = formula.size();
        int ind = 0;

        while (ind < n) {
            if (formula[ind] == '(') {
                // Start of a new group, push empty map
                st.push(unordered_map<string, int>());
                ind++;
            }
            else if (formula[ind] == ')') {
                // End of group
                unordered_map<string, int> temp = st.top();
                st.pop();

                // Parse multiplier after ')'
                ind++;
                string count = "";
                while (ind < n && isdigit(formula[ind])) count += formula[ind++];
                int multiplier = count.empty() ? 1 : stoi(count);

                // Multiply all atom counts in group and merge into previous level
                for (auto ele : temp) {
                    st.top()[ele.first] += ele.second * multiplier;
                }
            }
            else {
                // Parse atom name (starts with uppercase, may have lowercase letters)
                string atom = "";
                atom += formula[ind++];  // First uppercase
                while (ind < n && islower(formula[ind])) atom += formula[ind++];

                // Parse count (may be empty → implies 1)
                string num = "";
                while (ind < n && isdigit(formula[ind])) num += formula[ind++];
                int count = num.empty() ? 1 : stoi(num);

                st.top()[atom] += count;
            }
        }

        // Sort atom names and build final result
        map<string, int> finalFreq(st.top().begin(), st.top().end());
        string ans = "";
        for (auto ele : finalFreq) {
            ans += ele.first;
            if (ele.second > 1) ans += to_string(ele.second); // Omit count if 1
        }
        return ans;
    }
};
// ***************************************** Cleaned Solution *****************************************