class Solution {
public:
    vector<vector<int>> largeGroupPositions(string s) {
        int n = s.size();
        vector<vector<int> > ret;
        for(int i = 0, j; i < n; ) {
            for(j = i; i < n && s[j] == s[i]; ++i);
            if(i - j >= 3)
                ret.push_back({j, i - 1});
        }
        return ret;
    }
};
