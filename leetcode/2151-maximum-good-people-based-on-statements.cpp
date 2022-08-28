class Solution {
public:
    int maximumGood(vector<vector<int>>& statements) {
        int n = statements.size(), ans = 0;
        for(int i = 1; i < (1 << n); ++i) {
            int ctr = 0;
            bool ban = false;
            for(int j = 0; j < n; ++j) {
                if(!((i >> j) & 1))
                    continue;
                ++ctr;
                for(int k = 0; k < n; ++k) {
                    int typ = statements[j][k];
                    if(typ == 2)
                        continue;
                    if(typ != ((i >> k) & 1)) {
                        ban = true;
                        break;
                    }
                }
            }
            if(!ban)
                ans = max(ans, ctr);
        }
        return ans;
    }
};
