class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int ans = 0, n = (int)arr.size();
        for(int i = 0, j = 0; i < k; ++i)
            for(++ans; j < n && arr[j] == ans; ++j, ++ans);
        return ans;
    }
};
