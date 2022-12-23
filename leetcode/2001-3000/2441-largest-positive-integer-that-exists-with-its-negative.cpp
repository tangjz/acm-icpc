class Solution {
public:
    int findMaxK(vector<int>& nums) {
        unordered_set<int> vis;
        for(int x: nums)
            if(x < 0)
                vis.insert(-x);
        int ans = -1;
        for(int x: nums)
            if(x > 0 && vis.count(x))
                ans = max(ans, x);
        return ans;
    }
};
