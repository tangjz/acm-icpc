class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> hs;
        for(int x: nums)
            if(!hs.insert(x).second)
                return true;
        return false;
    }
};
