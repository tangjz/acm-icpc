class Solution {
public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        typedef long long LL;
        int n = nums1.size();
        vector<int> bits(n + 1), suf(n), pos(n);
        for(int i = 0; i < n; ++i)
            pos[nums2[i]] = i + 1;
        for(int i = n - 1; i >= 0; --i) {
            for(int j = pos[nums1[i]] + 1; j <= n; j += j & -j)
                suf[i] += bits[j];
            for(int j = pos[nums1[i]]; j > 0; j -= j & -j)
                ++bits[j];
        }
        LL ans = 0;
        vector<int>(n + 1).swap(bits);
        for(int i = 0; i < n; ++i) {
            int tmp = 0;
            for(int j = pos[nums1[i]] - 1; j > 0; j -= j & -j)
                tmp += bits[j];
            ans += (LL)tmp * suf[i];
            for(int j = pos[nums1[i]]; j <= n; j += j & -j)
                ++bits[j];
        }
        return ans;
    }
};
