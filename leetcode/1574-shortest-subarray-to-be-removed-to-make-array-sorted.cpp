class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = (int)arr.size(), sta = n - 1;
        for( ; sta > 0 && arr[sta - 1] <= arr[sta]; --sta);
        int ans = sta;
        for(int i = 0, j = sta; i < n; ++i) {
            for( ; j < n && (j <= i || arr[i] > arr[j]); ++j);
            ans = min(ans, j - i - 1);
            if(i + 1 < n && arr[i] > arr[i + 1])
                break;
        }
        return ans;
    }
};
