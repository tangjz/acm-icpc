class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        typedef long long LL;
        int n = nums1.size();
        vector<int> A(n + 1);
        for(int i = 0; i < n; ++i)
            A[i] = abs(nums1[i] - nums2[i]);
        ++n;
        sort(A.begin(), A.end());
        LL ans = 0, sum = 0, m = k1 + k2;
        for(int i = n - 1; i > 0; --i) {
            sum += A[i];
            if(m > sum - (LL)(n - i) * A[i - 1])
                continue;
            for(int j = i; j < n; ++j) {
                m -= A[j] - A[i - 1];
                A[j] = A[i - 1];
            }
            m = -m;
            LL q = m / (n - i), r = m % (n - i);
            for(int j = i; j < n; ++j) {
                A[j] += q + (j - i < r);
            }
            for(int j = 0; j < n; ++j)
                ans += (LL)A[j] * A[j];
            return ans;
        }
        return 0;
    }
};
