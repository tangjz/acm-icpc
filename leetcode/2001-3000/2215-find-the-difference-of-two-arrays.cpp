class Solution {
public:
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> msk;
        for(int x: nums1)
            msk[x] |= 1;
        for(int x: nums2)
            msk[x] |= 2;
        vector<vector<int> > ret(2);
        for(auto &it: msk)
            if(it.second && it.second < 3)
                ret[it.second - 1].push_back(it.first);
        return ret;
    }
};
