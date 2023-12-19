class Solution {
public:
    long long maximumSum(vector<int>& nums) {
        static const int maxv = (int)1e4 + 1;
        static int ptot = 0, d[maxv], pr[maxv];
        if(!ptot) {
            memset(d, -1, sizeof d);
            for(int i = 2; i < maxv; ++i) {
                if(d[i] == -1) {
                    d[i] = ptot;
                    pr[ptot++] = i;
                }
                for(int j = 0, k; (k = i * pr[j]) < maxv; ++j) {
                    d[k] = j;
                    if(d[i] == j)
                        break;
                }
            }
        }
        typedef long long LL;
        int n = nums.size();
        LL ans = 0;
        map<vector<int>, LL> hs;
        for(int i = 0; i < n; ++i) {
            int x = i + 1;
            static vector<int> key;
            key.clear();
            for(int c, p; x > 1; ) {
                for(c = 0, p = d[x]; d[x] == p; x /= pr[p], ++c);
                if(c & 1)
                    key.push_back(p);
            }
            ans = max(ans, hs[key] += nums[i]);
        }
        return ans;
    }
};
