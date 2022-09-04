class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> msk;
        for(int x: nums1)
            msk[x] |= 1;
        for(int x: nums2)
            msk[x] |= 2;
        vector<int> ret;
        for(auto &it: msk)
            if(it.second == 3)
                ret.push_back(it.first);
        return ret;
    }
};
