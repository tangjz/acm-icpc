class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int diff) {
        typedef long long LL;
        int n = nums1.size();
        for(int i = 0; i < n; ++i)
            nums1[i] -= nums2[i];
        LL ans = 0;
        function<void(int, int)> calc = [&](int L, int R) {
            if(L == R)
                return;
            int M = (L + R) >> 1;
            calc(L, M);
            calc(M + 1, R);
            for(int i = L, j = M + 1; i <= M && j <= R; ++i) {
                for( ; j <= R && nums1[i] > nums1[j] + diff; ++j);
                ans += R + 1 - j;
            }
            for(int i = L, j = M + 1, k = L; i <= M || j <= R; )
                if(j > R || (i <= M && nums1[i] < nums1[j])) {
                    nums2[k++] = nums1[i++];
                } else {
                    nums2[k++] = nums1[j++];
                }
            for(int i = L; i <= R; ++i)
                nums1[i] = nums2[i];
        };
        calc(0, n - 1);
        return ans;
    }
};
