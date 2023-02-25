class Solution {
public:
    int getCommon(vector<int>& nums1, vector<int>& nums2) {
        int ans = INT_MAX;
        unordered_set<int> sp;
        for(int x: nums1)
            sp.insert(x);
        for(int x: nums2)
            if(sp.count(x))
                ans = min(ans, x);
        return ans < INT_MAX ? ans : -1;
    }
};
