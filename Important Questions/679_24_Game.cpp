// Solution (Most Important) : https://www.youtube.com/watch?v=uKdv5osHud8&t=7s
// ******************************** My Solution ********************************
#define Epsilon 1e-9 // This will work
// #define Epsilon numeric_limits<long double>::epsilon() =>  This won't work as it is not an expression (study Macros)
// const double Epsilon=numeric_limits<double>::epsilon(); // This will also not work
// const double Epsilon=1e-6; // This will work

// you can also put c++ provided epsilon values (Epsilon helps to check if the number is 0 or not)
// std::numeric_limits<float>::epsilon();
// std::numeric_limits<double>::epsilon();
// std::numeric_limits<long double>::epsilon();

class Solution {
    public:
    vector<double> getValidOperations(double &a,double &b){
        vector<double> results;
        results.push_back(a+b);
        results.push_back(a-b);
        results.push_back(b-a);
        results.push_back(a*b);
        if(abs(b)>Epsilon) results.push_back(a/b);
        if(abs(a)>Epsilon) results.push_back(b/a);

        return results;
    }

    bool isPossible(vector<double>& cards){
        int n=cards.size();
        if(n==1){
            double val=cards[0];
            if(abs(24.0 - val)<=Epsilon) return true;
            return false;
        }

        bool ans=false;
        /*
            Everytime we will pick any 2 numbers from card and do operations 
            later we make a new array with result of operation and remaining values

            EX:
            arr=[a,b,c,d]
            pick any two nums say a,c
            now newArray=[b,d,res(a,c)]
        */
        
        // j started form i+1 because in getValidOperations we are doing operations with a,b and b,a as well so they are handled there itself
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(i==j) continue;
                double val1=cards[i];
                double val2=cards[j];
                

                vector<double> nextCards;
                for(int k=0;k<n;k++){
                    if(k==i || k==j) continue;
                    nextCards.push_back(cards[k]);
                }


                vector<double> results=getValidOperations(val1,val2);
                for(double res : results){
                    nextCards.push_back(res);
                    ans=ans || isPossible(nextCards);
                    nextCards.pop_back(); // Backtracking
                }
            }
        }

        return ans;
    }

    bool judgePoint24(vector<int>& cards) {
        vector<double> newCards(cards.begin(),cards.end());
        return isPossible(newCards);
    }
};
// ******************************** My Solution ********************************