class Solution {
public:
    int validSubarraySize(vector<int>& nums, int threshold) {
        int n = nums.size();
        vector<int> ord(n), pL(n, -1), pR(n, -1);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return nums[u] > nums[v];
        });
        for(int i = 0; i < n; ++i) {
            int L = ord[i], R = L;
            pL[L] = pR[L] = L;
            if(L > 0 && pL[L - 1] != -1) {
                L = pL[L - 1];
                pR[L] = R;
                pL[R] = L;
            }
            if(R + 1 < n && pR[R + 1] != -1) {
                R = pR[R + 1];
                pL[R] = L;
                pR[L] = R;
            }
            int best = R - L + 1;
            // printf("%d: %d %d\n", ord[i], best, nums[ord[i]], threshold / best);
            if(threshold / best < nums[ord[i]])
                return best;
        }
        return -1;
    }
};
