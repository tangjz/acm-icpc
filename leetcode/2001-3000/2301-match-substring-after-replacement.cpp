class Solution {
public:
    bool matchReplacement(string s, string sub, vector<vector<char>>& mappings) {
        unordered_map<char, unordered_set<char> > mp;
        for(auto &it: mappings)
            mp[it[0]].insert(it[1]);
        int n = s.size(), m = sub.size();
        for(int i = 0; i <= n - m; ++i) {
            bool ban = 0;
            for(int j = 0; !ban && j < m; ++j) {
                if(s[i + j] == sub[j])
                    continue;
                if(mp[sub[j]].count(s[i + j]))
                    continue;
                ban = 1;
            }
            if(!ban)
                return 1;
        }
        return 0;
    }
};
