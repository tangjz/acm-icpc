class Solution {
    bool isPrefix(string &u, string &v) {
        return u.size() < v.size() && u == v.substr(0, u.size()) && v[(int)u.size()] == '/';
    }
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        int n = (int)folder.size();
        vector<string> ret;
        sort(folder.begin(), folder.end());
        for(int i = 0, j; i < n; i = j) {
            ret.push_back(folder[i]);
            for(j = i + 1; j < n && isPrefix(folder[i], folder[j]); ++j);
        }
        return ret;
    }
};
