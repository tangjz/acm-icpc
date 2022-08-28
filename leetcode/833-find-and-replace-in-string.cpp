class Solution {
public:
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {
        int n = s.size(), m = indices.size(), las = n;
        vector<int> ord(m);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return indices[u] < indices[v];
        });
        while(!ord.empty()) {
            int u = ord.back();
            ord.pop_back();
            if(indices[u] + sources[u].size() > las)
                continue;
            if(s.substr(indices[u], sources[u].size()) == sources[u]) {
                s = s.substr(0, indices[u]) + targets[u] + s.substr(indices[u] + sources[u].size());
                las = indices[u];
            }
        }
        return s;
    }
};
