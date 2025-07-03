// ********************************* My Solution *********************************
class Solution {
    public:
    int solveBFS(string s1,string s2){
        queue<string> q;
        unordered_map<string,bool> seen;

        q.push(s1);
        seen[s1]=true;
        int n=s1.size();
        int k=0;
        
        while(!q.empty()){
            int m=q.size();
            for(int i=0;i<m;i++){
                string curr_str=q.front();
                q.pop();
                
                int ind=0;
                for(ind=0;ind<n;ind++){
                    if(curr_str[ind]!=s2[ind]) break;
                }
                
                if(ind==n) return k;
                
                int j=ind;
                while(j<n){
                    if(curr_str[j]==s2[ind]){
                        string temp=curr_str;
                        swap(temp[j],temp[ind]);
                        if(!seen[temp]){
                            seen[temp]=true;
                            q.push(temp);
                        }
                    }
                    j++;
                }
            }
            k++;
        }

        return -1;
    }


    int kSimilarity(string s1, string s2) {
        return solveBFS(s1,s2);
    }
};
// ********************************* My Solution *********************************