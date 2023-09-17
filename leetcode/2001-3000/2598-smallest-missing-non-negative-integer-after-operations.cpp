class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int mod) {
        vector<int> ctr(mod);
        for(int x: nums) {
            (x %= mod) < 0 && (x += mod);
            ++ctr[x];
        }
        int low = ctr[0];
        for(int i = 1; i < mod; ++i)
            low = min(low, ctr[i]);
        for(int i = 0; i < mod; ++i)
            if(ctr[i] == low)
                return low * mod + i;
        return -1;
    }
};
