class Solution {
public:
    int findSubstringInWraproundString(string p) {
        const int maxd = 26;
        int n = p.size();
        vector<int> upp(maxd);
        for(int i = 0, las, cnt = 0; i < n; ++i) {
            int cur = p[i] - 'a';
            if(!i || (las + 1) % 26 != cur)
                cnt = 0;
            upp[cur] = max(upp[cur], ++cnt);
            las = cur;
        }
        return accumulate(upp.begin(), upp.end(), 0);
    }
};
