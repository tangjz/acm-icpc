class Solution {
public:
    int subsetXORSum(vector<int>& nums) {
        int sum = 0, n = (int)nums.size();
        for(int i = 0; i < 1 << n; ++i) {
            int tmp = 0;
            for(int j = 0; j < n; ++j)
                tmp ^= (i >> j) & 1 ? nums[j] : 0;
            sum += tmp;
        }
        return sum;
    }
};
