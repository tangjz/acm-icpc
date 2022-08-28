class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int n = nums.size(), low = (int)-1e5, upp = (int)1e5;
        vector<vector<int> > ids(upp - low + 1, vector<int>());
        for(int i = 0; i < n; ++i)
            for(auto &val : nums[i])
                if(ids[val - low].empty() || ids[val - low].back() != i)
                    ids[val - low].push_back(i);
        int sta = low, ans = upp - low + 1, ctr = 0;
        vector<int> cnt(upp - low + 1, 0);
        for(int i = low, j = low; i <= upp; ++i) {
            for( ; ctr < n && j <= upp; ++j)
                for(auto &idx : ids[j - low])
                    if((++cnt[idx]) == 1)
                        ++ctr;
            if(ctr < n)
                break;
            if(ans > j - i) {
                ans = j - i;
                sta = i;
            }
            for(auto &idx : ids[i - low])
                if((--cnt[idx]) == 0)
                    --ctr;
        }
        return vector<int>{sta, sta + ans - 1};
    }
};
