class Solution {
public:
    int maximumsSplicedArray(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), low = 0, upp = 0, s1 = 0, s2 = 0, p1 = 0, p2 = 0;
        for(int i = 0; i < n; ++i) {
            int v1 = nums1[i], v2 = nums2[i];
            s1 += v1;
            s2 += v2;
            int dt = v2 - v1;
            low = max(low - dt, 0);
            upp = max(upp + dt, 0);
            p1 = max(p1, upp);
            p2 = max(p2, low);
        }
        return max(s1 + p1, s2 + p2);
    }
};
