class Solution {
public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        int n = (int)nums1.size(), m = (int)nums2.size();
        const int maxd = 6;
        if(min(n, m) * maxd < max(n, m))
            return -1;
        int diff = 0;
        vector<int> ctr1(maxd + 1), ctr2(maxd + 1);
        for(int x: nums1) {
            ++ctr1[x];
            diff += x;
        }
        for(int x: nums2) {
            ++ctr2[x];
            diff -= x;
        }
        if(!diff)
            return 0;
        if(diff < 0) {
            swap(ctr1, ctr2);
            diff = -diff;
        }
        int ans = 0;
        for(int i = maxd - 1; i > 0; --i) {
            int upp = ctr1[i + 1] + ctr2[maxd - i];
            for(int j = 0; j < upp && diff > 0; ++j, diff -= i, ++ans);
        }
        return ans;
    }
};
