class Solution {
public:
    vector<int> findIntersectionValues(vector<int>& nums1, vector<int>& nums2) {
        auto calc = [&](vector<int> &A, vector<int> &B) {
            unordered_set<int> sp;
            for(int x: B)
                sp.insert(x);
            int ret = 0;
            for(int x: A)
                ret += sp.count(x);
            return ret;
        };
        return {calc(nums1, nums2), calc(nums2, nums1)};
    }
};
