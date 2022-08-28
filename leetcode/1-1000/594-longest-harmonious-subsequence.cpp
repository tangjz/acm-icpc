class Solution {
public:
    int findLHS(vector<int>& nums) {
        map<int, int> ctr;
        for(int x: nums)
            ++ctr[x];
        int ans = 0;
        pair<int, int> las = {INT_MIN, 0};
        for(auto &it: ctr) {
            if(las.first + 1 == it.first)
                ans = max(ans, las.second + it.second);
            las = it;
        }
        return ans;
    }
};
