class Solution {
public:
    int pathSum(vector<int>& nums) {
        vector<int> vals;
        for(int x: nums) {
            int v = x % 10;
            x /= 10;
            int p = x % 10, d = x / 10;
            int idx = (1 << (d - 1)) - 1 + p;
            while(idx >= vals.size())
                vals.push_back(-1);
            assert(vals[idx] == -1);
            vals[idx] = v;
        }
        int ans = 0, n = vals.size();
        for(int i = 1; i < n; ++i) {
            if(vals[i] == -1)
                continue;
            if(i > 1) {
                assert(vals[i >> 1] != -1);
                vals[i] += vals[i >> 1];
            }
            bool hasLeft = i + i < n && vals[i + i] != -1;
            bool hasRight = i + i + 1 < n && vals[i + i + 1] != -1;
            if(!hasLeft && !hasRight)
                ans += vals[i];
        }
        return ans;
    }
};
