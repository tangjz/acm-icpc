class Solution {
public:
    int countPairs(vector<vector<int>>& A, int k) {
        typedef long long LL;
        const int maxv = (int)1e6 + 1;
        unordered_map<LL, int> hs;
        sort(A.begin(), A.end());
        int ans = 0;
        for(auto &it: A) {
            int x = it[0], y = it[1];
            LL key = (LL)x * maxv + y;
            for(int dx = 0, dy = k; dx <= k; ++dx, --dy) {
                int xx = x ^ dx, yy = y ^ dy;
                LL key2 = (LL)xx * maxv + yy;
                if(xx < 0 || xx >= maxv || yy < 0 || yy >= maxv || key2 > key)
                    continue;
                auto jt = hs.find(key2);
                if(jt != hs.end())
                    ans += jt -> second;
            }
            ++hs[key];
        }
        return ans;
    }
};
