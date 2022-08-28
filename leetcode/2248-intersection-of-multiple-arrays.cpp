class Solution {
public:
    vector<int> intersection(vector<vector<int>>& nums) {
        unordered_map<int, int> ctr;
        for(auto &it: nums)
            for(int x: it)
                ++ctr[x];
        int n = nums.size();
        vector<int> ret;
        for(auto &it: ctr)
            if(it.second == n)
                ret.push_back(it.first);
        sort(ret.begin(), ret.end());
        return ret;
    }
};
