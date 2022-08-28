class Solution {
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        int m = n * (n + 1) / 2;
        vector<int> vals;
        vals.reserve(m);
        for(int i = 0; i < n; ++i) {
            int sum = 0;
            for(int j = i; j < n; ++j)
                vals.push_back(sum += nums[j]);
        }
        nth_element(vals.begin(), vals.begin() + (left - 1), vals.end());
        nth_element(vals.begin() + (left - 1), vals.begin() + (right - 1), vals.end());
        const int mod = (int)1e9 + 7;
        int ans = 0;
        for(int i = left - 1; i < right; ++i)
            (ans += vals[i]) >= mod && (ans -= mod);
        return ans;
    }
};
