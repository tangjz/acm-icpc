class Solution {
public:
    int minProductSum(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), ans = 0;
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        for(int i = 0; i < n; ++i)
            ans += nums1[i] * nums2[n - 1 - i];
        return ans;
    }
};
