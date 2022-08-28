class Solution {
public:
    vector<string> commonChars(vector<string>& words) {
        const int maxd = 26;
        vector<int> ans(maxd, INT_MAX);
        for(auto &it: words) {
            vector<int> tmp(maxd);
            for(char ch: it)
                ++tmp[(int)(ch - 'a')];
            for(int i = 0; i < maxd; ++i)
                ans[i] = min(ans[i], tmp[i]);
        }
        vector<string> ret;
        for(int i = 0; i < maxd; ++i)
            while(ans[i]--) {
                string tmp = "";
                tmp += 'a' + i;
                ret.push_back(tmp);
            }
        return ret;
    }
};
