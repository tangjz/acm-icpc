class Solution {
public:
    int numSubseq(vector<int>& nums, int target) {
        const int mod = (int)1e9 + 7;
        int n = (int)nums.size(), ans = 0;
        vector<int> pw(n);
        pw[0] = 1;
        for(int i = 1; i < n; ++i)
            (pw[i] = pw[i - 1] << 1) >= mod && (pw[i] -= mod);
        sort(nums.begin(), nums.end());
        for(int i = 0, j = n - 1; i < n; ++i) {
            for( ; i <= j && nums[i] + nums[j] > target; --j);
            if(i > j)
                break;
            (ans += pw[j - i]) >= mod && (ans -= mod);
        }
        return ans;
    }
};
