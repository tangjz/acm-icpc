class Solution {
public:
    int jump(vector<int>& nums) {
        int n = (int)nums.size();
        int ans = 0, L = 0, R = 0;
        while(R < n - 1) {
            int tL = R + 1, tR = R;
            for(int i = L; i <= R; ++i)
                tR = max(tR, i + nums[i]);
            L = tL;
            R = tR;
            ++ans;
        }
        return ans;
    }
};
