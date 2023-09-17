class Solution {
public:
    long long countInterestingSubarrays(vector<int>& A, int mod, int k) {
        typedef long long LL;
        int n = A.size();
        LL ans = 0;
        map<int, int> ctr;
        for(int i = 0, c = 0, p = (mod - k) % mod; i < n; ++i) {
            ++ctr[c];
            if(A[i] % mod == k) {
                (++c) == mod && (c = 0);
                (++p) == mod && (p = 0);
            }
            ans += ctr[p];
        }
        return ans;
    }
};
