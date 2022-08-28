class Solution {
public:
    vector<int> twoOutOfThree(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3) {
        unordered_map<int, int> h;
        for(int x: nums1)
            h[x] |= 1;
        for(int x: nums2)
            h[x] |= 2;
        for(int x: nums3)
            h[x] |= 4;
        vector<int> ret;
        for(auto &it: h)
            if(it.second == 3 || it.second == 5 || it.second == 6 || it.second == 7)
                ret.push_back(it.first);
        return ret;
    }
};
