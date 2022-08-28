class Solution {
public:
    long long countPairs(vector<int>& nums1, vector<int>& nums2) {
        typedef long long LL;
        int n = nums1.size();
        for(int i = 0; i < n; ++i) {
            nums1[i] -= nums2[i];
            nums2[i] = nums1[i];
        }
        sort(nums2.begin(), nums2.end());
        nums2.erase(unique(nums2.begin(), nums2.end()), nums2.end());
        int m = nums2.size();
        LL ans = 0;
        vector<int> bits(m);
        for(int i = 0; i < n; ++i) {
            int j = upper_bound(nums2.begin(), nums2.end(), -nums1[i]) - nums2.begin();
            for(int x = j + 1; x <= m; x += x & -x)
                ans += bits[x - 1];
            j = lower_bound(nums2.begin(), nums2.end(), nums1[i]) - nums2.begin();
            for(int x = j + 1; x > 0; x -= x & -x)
                ++bits[x - 1];
        }
        return ans;
    }
};
