class Solution {
public:
    vector<int> relocateMarbles(vector<int>& nums, vector<int>& moveFrom, vector<int>& moveTo) {
        unordered_map<int, int> ctr;
        for(int x: nums)
            ++ctr[x];
        int m = moveTo.size();
        for(int i = 0; i < m; ++i) {
            int u = moveFrom[i], v = moveTo[i];
            if(u == v)
                continue;
            ctr[v] += ctr[u];
            ctr.erase(u);
        }
        nums.clear();
        for(auto &it: ctr)
            nums.push_back(it.first);
        sort(nums.begin(), nums.end());
        return nums;
    }
};
