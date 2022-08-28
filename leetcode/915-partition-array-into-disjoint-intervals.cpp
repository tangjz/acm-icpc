class Solution {
public:
    int partitionDisjoint(vector<int>& nums) {
        int n = nums.size();
        vector<int> pre(n), suf(n);
        for(int i = n - 1; i >= 0; --i) {
            suf[i] = nums[i];
            if(i + 1 < n)
                suf[i] = min(suf[i], suf[i + 1]);
        }
        for(int i = 0; i < n; ++i) {
            pre[i] = nums[i];
            if(i > 0) {
                if(pre[i - 1] <= suf[i])
                    return i;
                pre[i] = max(pre[i], pre[i - 1]);
            }
        }
        return -1;
    }
};
