class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        vector<int> pos;
        for(int i = 0; i < n; ++i) {
            int val = nums[i];
            if(pos.empty() || nums[pos.back()] > val)
                pos.push_back(i);
            int L = 0, R = pos.size() - 1;
            while(L < R) {
                int M = (L + R) >> 1;
                if(nums[pos[M]] <= val) {
                    R = M;
                } else {
                    L = M + 1;
                }
            }
            ans = max(ans, i - pos[L]);
        }
        return ans;
    }
};
