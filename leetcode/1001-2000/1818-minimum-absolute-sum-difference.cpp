class Solution {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        set<int> Hash;
        for(int x: nums1)
            Hash.insert(x);
        const int mod = (int)1e9 + 7;
        int ans = 0, adt = 0, n = (int)nums1.size();
        for(int i = 0; i < n; ++i) {
            int dif = abs(nums1[i] - nums2[i]);
            adt = (adt + dif) % mod;
            int best = dif;
            auto it = Hash.lower_bound(nums2[i]);
            if(it != Hash.end()) {
                best = min(best, abs(*it - nums2[i]));
            }
            if(it != Hash.begin()) {
                best = min(best, abs(*(--it) - nums2[i]));
            }
            ans = min(ans, best - dif);
        }
        ans = (ans + mod + adt) % mod;
        return ans;
    }
};
