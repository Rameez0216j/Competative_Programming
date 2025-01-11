#include <bits/stdc++.h>
using namespace std;

int main() {
    // cout<<to_string(100)<<endl;


    // Conversions of number from string base on radix
    // string num="1010";
    // int ans=stoi(num,0,2); // integer form radix
    // cout<<ans<<endl;

    // string num="011";
    // int ans=stoi(num,0,17); // integer form radix
    // cout<<ans<<endl;

    // string num="G";
    // int ans=stoi(num,0,17); // integer form radix
    // cout<<ans<<endl;

    // string num="A";
    // int ans=stoi(num,0,16); // integer form radix
    // cout<<ans<<endl;
    // cout<<oct<<ans<<endl;
    // cout<<hex<<ans<<endl;

    // bitset<32> binary(10);
    // cout<<binary<<endl;

    // float val=126.1465719;
    // cout<<val<<endl;
    // cout<<setprecision(2)<<val<<endl;
    // cout<<fixed<<setprecision(2)<<val<<endl; // fixed to avoid sintific notation


    // custom split in c++
    // string s;
    // getline(cin,s);

    // istringstream iss(s);
    // string token;
    // while(getline(iss,token,' ')){
    //     if(token=="") continue;
    //     cout<<token<<",";
    // }





    // IMPORTANT SNIPPET
    // bitset<32> binary(10);
    // string str=binary.to_string();
    // auto ind=str.find('1');
    // string ans=str.substr(ind,str.size());
    // cout<<ans<<endl;



    // IMPORTANT SNIPPET
    // bitset<32> binary(10);
    // string str=binary.to_string();
    // auto ind=str.find('1');
    // string ans=str.substr(ind,str.size());


    // // strings are mutable in C++
    // for(int i=0;i<ans.size();i++){
    //     if(ans[i]=='0') ans[i]='1';
    //     else if(ans[i]=='1') ans[i]='0';
    // }

    // int final_decimal=stoi(ans,0,2);
    // cout<<final_decimal<<endl;




    // // Formatting Output with setw
    // cout << "\nFormatting Output:" << endl;
    // cout << setw(10) << "Hello" << setw(10) << "World" << endl;
    // cout << setw(10) << setfill('0') << "Hello" << setw(10) << setfill('0') << "World" << endl;

    // // Precision for Floating Point Numbers
    // cout << "\nPrecision for Floating Point Numbers:" << endl;
    // double pi = 3.14159265358979323846;
    // cout << fixed << setprecision(4) << pi << endl; //rounded
    // cout << setprecision(4) << pi << endl;

    // pi = 3.16;
    // cout << fixed << setprecision(5) << pi << endl;
    // cout << setprecision(4) << pi << endl;



    // // Formatting Flags
    // cout << "\nFormatting Flags:" << endl;
    // double number = 12345.6789;
    // cout << fixed << number << endl;
    // cout << scientific << setprecision(4) << number << endl;



    // // Alignment
    // // cout << "\nAlignment:" << endl;
    // cout << left << setw(10) << "Left" << right << setw(10) << "Right" << endl;
    // cout << left << setw(10) << setfill('0') << "Left" << right << setw(10) << setfill('0') << "Right" << endl;


    
    // output string stream ostrigstream ( any output of type [cout] can be stored in it )
    // ostringstream oss;
    // oss<<fixed<<setprecision(4)<<10;
    // string ans=oss.str();
    // cout<<ans;

    // ostringstream oss;
    // oss<<fixed<<setprecision(4)<<double(10.01);
    // string ans=oss.str();
    // cout<<ans;


    // sintific conversion
    // double number = 12345.6789;
    // ostringstream oss;
    // oss << scientific << setprecision(4) << number;
    // string scientificString = oss.str();
    // cout << "Scientific String: " << scientificString << endl;


    // double number = 12345.6789;
    // ostringstream oss;
    // oss << scientific << setprecision(4) << number;
    // string scientificString = oss.str();
    // // for(char ch:scientificString) cout<<ch<<",";
    // for(int i=0;i<scientificString.size();i++) i==scientificString.size()-1 ? cout<<scientificString[i] : cout<<scientificString[i]<<",";





    // int arr[] = {1, 2,3};
    // // sort(arr, arr + 3);
    // cout << "The 3! possible permutations with 3 elements:\n";
    // do
    // {
    //     cout << arr[0] << " " << arr[1] << " " << arr[2] << "\n";
    // } while (prev_permutation(arr, arr + 3));
    // // cout << "After loop: " << arr[0] << ' '<< arr[1] << ' ' << arr[2] << '\n';




    // int arr[] = {1, 2,3};
    // // sort(arr, arr + 3);
    // cout << "The 3! possible permutations with 3 elements:\n";
    // do
    // {
    //     cout << arr[0] << " " << arr[1] << " " << arr[2] << "\n";
    // } while (next_permutation(arr, arr + 3));
    // // cout << "After loop: " << arr[0] << ' '<< arr[1] << ' ' << arr[2] << '\n';
    

    // double num1=123.1231;
    // cout<<ceil(num1)<<"|"<<floor(num1)<<endl;

    
    return 0;
}