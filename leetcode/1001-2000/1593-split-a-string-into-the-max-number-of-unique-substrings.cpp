class Solution {
public:
    int maxUniqueSplit(string s) {
        int n = s.size(), ans = 1;
        for(int i = 1; i < (1 << (n - 1)); ++i) {
            bool chk = true;
            unordered_set<string> vis;
            int las = 0, cnt = 0;
            for(int j = 1, tmp = i; chk && j < n; ++j, tmp >>= 1) {
                if(!(tmp & 1))
                    continue;
                chk &= vis.insert(s.substr(las, j - las)).second;
                las = j;
                ++cnt;
            }
            if(chk) {
                chk &= vis.insert(s.substr(las)).second;
                ++cnt;
                if(chk)
                    ans = max(ans, cnt);
            }
        }
        return ans;
    }
};
