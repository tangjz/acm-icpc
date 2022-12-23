class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int ans = 0, L = 0, R = nums.size() - 1;
        int cnt = 0, dt = 0;
        while(L <= R) {
            if(dt > 0) {
                dt -= nums[L++];
            } else {
                dt += nums[R--];
            }
            if(!dt)
                cnt += 2;
            ans = max(ans, cnt + (L <= R));
        }
        return nums.size() - ans;
    }
};
