class Solution {
    vector<int> split(string_view s, char sep = '.') {
        int n = s.size();
        vector<int> ret;
        for(int i = 0; i < n; ++i) {
            int val = 0;
            for( ; i < n && s[i] != '.'; ++i)
                val = val * 10 + (s[i] - '0');
            ret.push_back(val);
        }
        return move(ret);
    }
public:
    int compareVersion(string version1, string version2) {
        vector<int> p = split(version1);
        vector<int> q = split(version2);
        int upp = max(p.size(), q.size());
        p.resize(upp);
        q.resize(upp);
        return (p > q) - (p < q);
    }
};
