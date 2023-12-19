class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        int n = nums.size(), ans = 0;
        vector<int> pos(k + 1);
        for(int i = 0; i < n; ++i) {
            int v = nums[n - 1 - i];
            if(v <= k && !pos[v])
                ans = pos[v] = i + 1;
        }
        return ans;
    }
};
