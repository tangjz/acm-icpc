class Solution {
public:
    int maxNonDecreasingLength(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        for(int i = 0; i < n; ++i) {
            int &u = nums1[i], &v = nums2[i];
            if(u < v)
                swap(u, v);
        }
        int ans = 1;
        function<void(int, int)> solve = [&](int L, int R) {
            if(R - L + 1 <= ans)
                return;
            int M = (L + R) >> 1;
            for(int vM: {nums1[M], nums2[M]}) {
                int vL = vM, vR = vM, cnt = 1;
                for(int i = M - 1; i >= L; --i, ++cnt)
                    if(nums1[i] <= vL) {
                        vL = nums1[i];
                    } else if(nums2[i] <= vL) {
                        vL = nums2[i];
                    } else {
                        break;
                    }
                for(int i = M + 1; i <= R; ++i, ++cnt)
                    if(nums2[i] >= vR) {
                        vR = nums2[i];
                    } else if(nums1[i] >= vR) {
                        vR = nums1[i];
                    } else {
                        break;
                    }
                ans = max(ans, cnt);
            }
            solve(L, M - 1);
            solve(M + 1, R);
        };
        solve(0, n - 1);
        return ans;
    }
};
