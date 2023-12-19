class Solution {
public:
    int maxSubarrayLength(vector<int>& A, int k) {
        int n = A.size(), c = 0, ans = 0;
        unordered_map<int, int> hs;
        for(int i = 0, j = 0; i < n; ++i) {
            c += (hs[A[i]]++) == k;
            for( ; j < i && c > 0; ++j)
                c -= (--hs[A[j]]) == k;
            if(!c)
                ans = max(ans, i - j + 1);
        }
        return ans;
    }
};
