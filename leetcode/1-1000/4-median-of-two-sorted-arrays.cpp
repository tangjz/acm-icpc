class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = (int)nums1.size(), m = (int)nums2.size(), k = ((n + m) >> 1) + 1;
        vector<int> cand;
        if(n > 0) {
            cand.push_back(nums1.front());
            cand.push_back(nums1.back());
        }
        if(m > 0) {
            cand.push_back(nums2.front());
            cand.push_back(nums2.back());
        }
        sort(cand.begin(), cand.end());
        int low = cand.front(), upp = cand.back();
        int L = max(k - m, 0), R = min(n, k);
        while(L < R) {
            int M = (L + R) >> 1;
            int fir = M < n ? nums1[M] : upp;
            int sec = k - M > 0 ? nums2[k - M - 1] : low;
            if(fir < sec) {
                L = M + 1;
            } else {
                R = M;
            }
        }
        cand.clear();
        int need = (n + m) & 1 ? 1 : 2;
        for(int i = L - 1, j = need; i >= 0 && j > 0; --i, --j)
            cand.push_back(nums1[i]);
        for(int i = k - L - 1, j = need; i >= 0 && j > 0; --i, --j)
            cand.push_back(nums2[i]);
        sort(cand.begin(), cand.end(), greater<int>());
        double ret = cand[0];
        if(need == 2)
            ret = (ret + cand[1]) / 2;
        return ret;
    }
};
