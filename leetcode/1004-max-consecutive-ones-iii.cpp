class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> pos;
        for(int i = 0; i < n; ++i)
            if(nums[i])
                pos.push_back(i);
        int m = pos.size(), ans = k;
        for(int i = 0, j = 0; i < m; ++i) {
            for( ; j < m && pos[j] - pos[i] <= j - i + k; ++j);
            int L = pos[i], R = pos[j - 1];
            int dt = (j - 1 - i + k) - (R - L);
            int tp = min(n - 1 - R, dt);
            dt -= tp;
            R += tp;
            tp = min(L, dt);
            dt -= tp;
            L -= tp;
            ans = max(ans, R - L + 1);
        }
        return ans;
    }
};
