class Solution {
public:
    int reversePairs(vector<int>& nums) {
        function<int(int, int)> solve = [&](int L, int R) {
            if(L >= R)
                return 0;
            int ret = 0, M = (L + R) >> 1;
            ret += solve(L, M);
            ret += solve(M + 1, R);
            vector<int> vals;
            vals.reserve(R - L + 1);
            for(int i = L, j = M + 1; i <= M || j <= R; )
                if(j > R || (i <= M && nums[i] <= nums[j])) {
                    ret += j - M - 1;
                    vals.push_back(nums[i++]);
                } else {
                    vals.push_back(nums[j++]);
                }
            for(int i = R; i >= L; --i) {
                nums[i] = vals.back();
                vals.pop_back();
            }
            return ret;
        };
        return solve(0, nums.size() - 1);
    }
};
