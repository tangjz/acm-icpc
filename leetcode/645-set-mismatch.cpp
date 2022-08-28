class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        typedef long long LL;
        int n = nums.size(), s1 = 0;
        LL s2 = 0;
        for(int i = 0; i < n; ++i) {
            int u = i + 1, v = nums[i];
            s1 += v - u;
            s2 += (LL)v * v - (LL)u * u;
        }
        s2 /= s1;
        int x = (s1 + s2) / 2, y = s2 - x;
        return {x, y};
    }
};
