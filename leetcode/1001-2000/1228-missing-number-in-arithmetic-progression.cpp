class Solution {
public:
    int missingNumber(vector<int>& arr) {
        int n = arr.size(), dt = (arr.back() - arr.front()) / n;
        for(int i = 0; i < n; ++i)
            if(arr[i] != arr[0] + dt * i)
                return arr[0] + dt * i;
        return arr.front();
    }
};
