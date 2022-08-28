class Solution {
public:
    int largestUniqueNumber(vector<int>& nums) {
        unordered_map<int, int> ctr;
        for(int x: nums)
            ++ctr[x];
        int ans = -1;
        for(auto &it: ctr)
            if(it.second == 1)
                ans = max(ans, it.first);
        return ans;
    }
};
