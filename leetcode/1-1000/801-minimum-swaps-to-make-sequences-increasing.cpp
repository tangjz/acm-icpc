class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), f[2] = {0, 1};
        for(int i = 1; i < n; ++i) {
            int g[2] = {INT_MAX, INT_MAX}, val[2][2] = {
                {nums1[i - 1], nums1[i]},
                {nums2[i - 1], nums2[i]},
            };
            for(int j = 0; j < 2; ++j) {
                if(f[j] == INT_MAX)
                    continue;
                for(int k = 0; k < 2; ++k) {
                    bool flip = j != k;
                    if(val[0][0] < val[flip][1] && val[1][0] < val[!flip][1])
                        g[k] = min(g[k], f[j]);
                }
            }
            if(g[1] < INT_MAX)
                ++g[1];
            f[0] = g[0];
            f[1] = g[1];
        }
        return min(f[0], f[1]);
    }
};
