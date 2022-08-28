class Solution {
public:
    int numPrimeArrangements(int n) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int ans = 1;
        vector<int> d(n + 1), pr;
        for(int i = 2; i <= n; ++i) {
            if(!d[i]) {
                d[i] = i;
                pr.push_back(i);
                ans = (LL)ans * pr.size() % mod;
            } else {
                ans = (LL)ans * (i - pr.size()) % mod;
            }
            for(int p: pr) {
                int j = i * p;
                if(j > n)
                    break;
                d[j] = p;
                if(d[i] == p)
                    break;
            }
        }
        return ans;
    }
};
