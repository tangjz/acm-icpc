class Solution {
public:
    long long countFairPairs(vector<int>& A, int low, int upp) {
        typedef long long LL;
        int n = A.size();
        sort(A.begin(), A.end());
        auto calc = [&](int upp) {
            LL ans = 0;
            for(int i = 0, j = n - 1; i < j; ++i) {
                for( ; j > i && A[i] + A[j] > upp; --j);
                if(i < j)
                    ans += j - i;
            }
            return ans;
        };
        return calc(upp) - calc(low - 1);
    }
};
