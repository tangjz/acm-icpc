class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> ctr;
        for(int x: nums1)
            ctr[x] += 1;
        vector<int> ret;
        for(int x: nums2) {
            auto it = ctr.find(x);
            if(it == ctr.end())
                continue;
            ret.push_back(x);
            if(it -> second == 1) {
                ctr.erase(x);
            } else {
                (it -> second) -= 1;
            }
        }
        return ret;
    }
};
