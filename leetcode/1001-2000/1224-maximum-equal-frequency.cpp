class Solution {
public:
    int maxEqualFreq(vector<int>& nums) {
        int ans = 1, n = nums.size(), low = 0, upp = 0;
        unordered_map<int, int> occ;
        vector<int> ctr(n + 1);
        for(int i = 1; i <= n; ++i) {
            int v = nums[i - 1];
            if(occ.count(v)) {
                --ctr[occ[v]];
            } else {
                low = 0;
            }
            ++occ[v];
            ++ctr[occ[v]];
            for( ; !ctr[low]; ++low);
            upp = max(upp, occ[v]);
            // printf("#%d: low %d upp %d size %d\n", i, low, upp, (int)occ.size());
            if(occ.size() == 1)
                ans = max(ans, i);
            if(upp - low == 1 && i - occ.size() * low == 1)
                ans = max(ans, i);
            if(low == 1 && i - (occ.size() - 1) * upp == 1)
                ans = max(ans, i);
        }
        return ans;
    }
};
