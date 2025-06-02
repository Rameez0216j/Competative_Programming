int mex(vector<int> &arr, int N){
    // sort the array
    sort(arr.begin(), arr.end());
    int mex = 0;
    for (int idx = 0; idx < N; idx++){
	    if (arr[idx] == mex){
	        // Increment mex
	        mex += 1;
	       }
    }
    // Return mex as answer
    return mex;
}
