class Solution {
public:
    int findFinalValue(vector<int>& nums, int original) {
        unordered_set<int> vis;
        for(int x: nums)
            vis.insert(x);
        while(vis.count(original))
            original *= 2;
        return original;
    }
};
