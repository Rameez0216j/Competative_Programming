// Leetcode : 3335_Total_Characters_in_String_After_Transformations

// ********** Using Matrix Exponentiation (Most suitable for these types of problems ) **********
/*
    a b c d e f g h i j k l m n o p q r s t u v w x y z     ← input (column)
a [ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 ]   ← 'a' appears from 'z'
b [ 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 ]   ← 'b' from 'a' and 'z'
c [ 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ]   ← 'c' from 'b'
d [ 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ]   ← 'd' from 'c'
e [ 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ]
f [ 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ]
g [ 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ]
h [ 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ]
i [ 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ]
j [ 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ]
k [ 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ]
l [ 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ]
m [ 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ]
n [ 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 ]
o [ 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 ]
p [ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 ]
q [ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 ]
r [ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 ]
s [ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 ]
t [ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 ]
u [ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 ]
v [ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 ]
w [ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 ]
x [ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 ]
y [ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 ]
z [ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 ]


Here we multiply out main vector with each row and add all the values to find occurence of characters of that particular row character as a result --> that will be our transformed new_vector (containing each characters freq after transformation)

for example 
mai vector = [ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 ] 
b_th row   = [ 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 ]
the above values are multiplied vertically and added 
        =>  Σ[ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 ] = 1
        above thing represents that for our given main vector we have only z with freq 1 and so 
        b will appear once for that z (same with b)

        and final new vector will be as below
        [ 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ]
        (above 1 s are result of transformation)

        total freq is as Σ[ 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ] = 2

        so for "z"-->"ab"(2  chars)

*/

// Use Modulo below for correct answer

class Solution {
    public:
    // Transformation Based on question
    vector<vector<int>> createTransformation(){
        vector<vector<int>> T(26,vector<int>(26,0));
        for(int i=0;i<25;i++) T[i+1][i]=1;  //  --> represents character occurrence for every alphabet
        T[0][25]=1;
        T[1][25]=1;
        return T;
    }

    vector<vector<int>> matMul(vector<vector<int>> &M1,vector<vector<int>> &M2){
        int r1=M1.size();
        int c1=M1[0].size();
        int r2=M2.size();
        int c2=M2[0].size();

        // assuming c1==r2 as multiplication is valid
        // Very careful about below loops order (it should be as below)
        vector<vector<int>> result(r1,vector<int>(c2,0));
        for(int i=0;i<r1;i++){
            for(int k=0;k<c2;k++){
                for(int j=0;j<c1;j++){
                    result[i][k]+=(M1[i][j]*M2[j][k]);
                }
            }
        }
        return result;
    }
    
    // Matrix Exponentiation is possible only for square matrix (So, n=m)
    vector<vector<int>> matExp(vector<vector<int>> &Matrix,int power){
        int n=Matrix.size();
        int m=Matrix[0].size();
        vector<vector<int>> result(n,vector<int>(m,0));
        for(int i=0;i<n;i++) result[i][i]=1; // identity matrix
        while(power){
            if(power%2==1) result=matMul(result,Matrix); 
            Matrix=matMul(Matrix,Matrix);
            power/=2;
        }
        // result=MatMul(result,Matrix); (wrong as power becomes 1 result is automatically gettiing multiplied i.e if(power%2==1) result=matMul(result,Matrix);)
        return result;
    }

    vector<int> applyTransformation(vector<int> &V,vector<vector<int>> &T){
        vector<int> ans(V.size());
        for(int i=0;i<V.size();i++){
            for(int j=0;j<T.size();j++){
                ans[i]+=(V[j]*T[i][j]);
            }
        }
        return ans;
    }



    int lengthAfterTransformations(string s, int t) {
        vector<int> repMat(26,0); // repMat ==> representation_matrix
        for(char ch:s) repMat[ch-'a']++;
        vector<vector<int>> T=createTransformation(); // T ==> Transformation
        vector<vector<int>> Tfinal=matExp(T,t); // Tfinal ==> finalTransformation
        vector<int> Tchar_freq=applyTransformation(repMat,Tfinal);
        int ans=0;
        for(int i=0;i<26;i++) ans+=Tchar_freq[i];
        return ans;
    }
};



// After using Modulo
/*
class Solution {
    int mod=1e9+7;

    public:
    // Transformation Based on question
    vector<vector<int>> createTransformation(){
        vector<vector<int>> T(26,vector<int>(26,0));
        for(int i=0;i<25;i++) T[i+1][i]=1;  //  --> represents character occurrence for every alphabet
        T[0][25]=1;
        T[1][25]=1;
        return T;
    }

    vector<vector<int>> matMul(vector<vector<int>> &M1,vector<vector<int>> &M2){
        int r1=M1.size();
        int c1=M1[0].size();
        int r2=M2.size();
        int c2=M2[0].size();

        // assuming c1==r2 as multiplication is valid
        // Very careful about below loops order (it should be as below)
        vector<vector<int>> result(r1,vector<int>(c2,0));
        for(int i=0;i<r1;i++){
            for(int k=0;k<c2;k++){
                for(int j=0;j<c1;j++){
                    result[i][k]=(result[i][k]%mod +  (1LL * M1[i][j]%mod * M2[j][k]%mod)%mod)%mod ;
                }
            }
        }
        return result;
    }
    
    // Matrix Exponentiation is possible only for square matrix (So, n=m)
    vector<vector<int>> matExp(vector<vector<int>> &Matrix,int power){
        int n=Matrix.size();
        int m=Matrix[0].size();
        vector<vector<int>> result(n,vector<int>(m,0));
        for(int i=0;i<n;i++) result[i][i]=1; // identity matrix
        while(power){
            if(power%2==1) result=matMul(result,Matrix); 
            Matrix=matMul(Matrix,Matrix);
            power/=2;
        }
        // result=MatMul(result,Matrix); (wrong as power becomes 1 result is automatically gettiing multiplied i.e if(power%2==1) result=matMul(result,Matrix);)
        return result;
    }

    vector<int> applyTransformation(vector<int> &V,vector<vector<int>> &T){
        vector<int> ans(V.size());
        for(int i=0;i<V.size();i++){
            for(int j=0;j<T.size();j++){
                ans[i]=(ans[i]%mod + (1LL* V[j]%mod * T[i][j]%mod)%mod)%mod ;
            }
        }
        return ans;
    }



    int lengthAfterTransformations(string s, int t) {
        vector<int> repMat(26,0); // repMat ==> representation_matrix
        for(char ch:s) repMat[ch-'a']++;
        vector<vector<int>> T=createTransformation(); // T ==> Transformation
        vector<vector<int>> Tfinal=matExp(T,t); // Tfinal ==> finalTransformation
        vector<int> Tchar_freq=applyTransformation(repMat,Tfinal);
        int ans=0;
        for(int i=0;i<26;i++) ans=(ans%mod + Tchar_freq[i]%mod)%mod;
        return ans;
    }
};
*/
// ********** Using Matrix Exponentiation (Most suitable for these types of problems ) **********