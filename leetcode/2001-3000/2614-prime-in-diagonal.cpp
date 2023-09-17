class Solution {
public:
    int diagonalPrime(vector<vector<int>>& nums) {
        int n = nums.size(), ans = 0;
        auto upd = [&](int x) {
            if(x <= ans)
                return;
            if(x < 2)
                return;
            for(int i = 2; i * i <= x; ++i)
                if(x % i == 0)
                    return;
            ans = x;
        };
        for(int i = 0; i < n; ++i) {
            upd(nums[i][i]);
            upd(nums[i][n - 1 - i]);
        }
        return ans;
    }
};
