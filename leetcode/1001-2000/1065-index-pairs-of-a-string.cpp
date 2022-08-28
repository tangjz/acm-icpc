class Solution {
public:
    vector<vector<int>> indexPairs(string text, vector<string>& words) {
        int n = text.size();
        vector<vector<int> > ret;
        unordered_set<string> Hash;
        for(auto &it: words)
            Hash.insert(it);
        for(int i = 0; i < n; ++i) {
            string tmp = "";
            for(int j = i; j < n; ++j) {
                tmp.push_back(text[j]);
                if(Hash.count(tmp))
                    ret.push_back({i, j});
            }
        }
        return ret;
    }
};
