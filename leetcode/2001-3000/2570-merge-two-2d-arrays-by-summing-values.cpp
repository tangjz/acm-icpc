class Solution {
public:
    vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
        map<int, int> ctr;
        for(auto &it: nums1)
            ctr[it[0]] += it[1];
        for(auto &it: nums2)
            ctr[it[0]] += it[1];
        nums1.clear();
        for(auto &it: ctr)
            nums1.push_back({it.first, it.second});
        return nums1;
    }
};
