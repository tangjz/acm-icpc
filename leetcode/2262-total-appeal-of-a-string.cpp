class Solution {
public:
    long long appealSum(string s) {
        typedef long long LL;
        int n = s.size();
        unordered_map<char, vector<int> > pos;
        for(int i = 0; i < n; ++i)
            pos[s[i]].push_back(i);
        LL ans = 0;
        for(auto &it: pos) {
            ans += n * (n + 1LL) / 2;
            int las = -1;
            for(int cur: it.second) {
                int len = cur - las - 1;
                ans -= len * (len + 1LL) / 2;
                las = cur;
            }
            int len = n - 1 - las;
            ans -= len * (len + 1LL) / 2;
            // printf("%c %lld\n", it.first, ans);
        }
        return ans;
    }
};
