class Solution {
public:
    long long maximumSumOfHeights(vector<int>& upp) {
        typedef long long LL;
        int n = upp.size();
        LL sum = 0;
        vector<int> stk;
        vector<LL> res(n);
        for(int i = 0, j, k; i < n; ++i) {
            for( ; !stk.empty() && upp[j = stk.back()] > upp[i]; ) {
                stk.pop_back();
                k = stk.empty() ? -1 : stk.back();
                sum -= (LL)upp[j] * (j - k);
            }
            k = stk.empty() ? -1 : stk.back();
            stk.push_back(i);
            sum += (LL)upp[i] * (i - k);
            // printf("i %d: %lld\n", i, sum);
            res[i] += sum;
        }
        sum = 0;
        stk.clear();
        for(int i = n - 1, j, k; i >= 0; --i) {
            for( ; !stk.empty() && upp[j = stk.back()] > upp[i]; ) {
                stk.pop_back();
                k = stk.empty() ? n : stk.back();
                sum -= (LL)upp[j] * (k - j);
            }
            k = stk.empty() ? n : stk.back();
            stk.push_back(i);
            sum += (LL)upp[i] * (k - i);
            // printf("i %d: %lld\n", i, sum);
            res[i] += sum;
        }
        sum = 0;
        for(int i = 0; i < n; ++i) {
            res[i] -= upp[i];
            sum = max(sum, res[i]);
        }
        return sum;
    }
};
