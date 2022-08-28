class Solution {
public:
    string minWindow(string s1, string s2) {
        unordered_map<char, int> Hash;
        vector<int> pos;
        pos.reserve(s2.size());
        for(char ch: s2) {
            Hash.insert({ch, Hash.size()});
            pos.push_back(Hash[ch]);
        }
        int n = s1.size(), m = Hash.size();
        vector<vector<int> > nxt(n, vector<int>(m));
        for(int i = 0; i < m; ++i)
            nxt[n - 1][i] = n;
        for(int i = n - 1; i >= 0; --i) {
            auto it = Hash.find(s1[i]);
            if(it != Hash.end())
                nxt[i][it -> second] = i;
            if(i > 0)
                nxt[i - 1] = nxt[i];
        }
        int ans = n + 1, sta = -1;
        for(int i = 0; i < n; ++i) {
            int j = i - 1;
            for(int x: pos)
                if((++j) < n)
                    j = nxt[j][x];
            if(j < n && ans > j - i + 1) {
                ans = j - i + 1;
                sta = i;
            }
        }
        return sta < 0 ? "" : s1.substr(sta, ans);
    }
};
