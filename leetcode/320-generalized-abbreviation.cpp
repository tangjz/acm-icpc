class Solution {
public:
    vector<string> generateAbbreviations(string word) {
        int n = word.size();
        string cur = "";
        vector<string> ret;
        function<void(int)> dfs = [&](int dep) {
            if(dep >= n) {
                ret.push_back(cur);
                return;
            }
            int m = cur.size();
            cur.push_back(word[dep]);
            dfs(dep + 1);
            cur.resize(m);
            for(int i = 1; dep < n; ++i) {
                cur += to_string(i);
                if((++dep) < n)
                    cur.push_back(word[dep]);
                dfs(dep + 1);
                cur.resize(m);
            }
        };
        dfs(0);
        return ret;
    }
};
