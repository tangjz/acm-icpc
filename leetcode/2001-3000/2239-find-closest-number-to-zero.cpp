class Solution {
public:
    int findClosestNumber(vector<int>& nums) {
        int ans = 1e9;
        for(int x: nums)
            if(abs(x) < abs(ans) || abs(x) == abs(ans) && x > ans)
                ans = x;
        return ans;
    }
};
