class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size(), ans = 0;
        vector<int> f(m + 1);
        for(int i = 1; i <= n; ++i)
            for(int j = 1, las = 0, cur; j <= m; ++j) {
                cur = f[j];
                f[j] = nums1[i - 1] == nums2[j - 1] ? las + 1 : 0;
                ans = max(ans, f[j]);
                las = cur;
            }
        return ans;
    }
};
