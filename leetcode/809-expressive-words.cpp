class Solution {
public:
    int expressiveWords(string s, vector<string>& words) {
        auto compress = [&](string &buf) {
            vector<pair<char, int> > ret;
            for(char ch: buf)
                if(ret.empty() || ret.back().first != ch) {
                    ret.push_back({ch, 1});
                } else {
                    ++ret.back().second;
                }
            return ret;
        };
        vector<pair<char, int> > pat = compress(s), txt;
        int ans = 0, m = pat.size();
        for(auto &buf: words) {
            txt = compress(buf);
            bool ban = m != txt.size();
            for(int i = 0; !ban && i < m; ++i)
                ban |= pat[i].first != txt[i].first || pat[i].second < txt[i].second || (pat[i].second == 2 && txt[i].second == 1);
            ans += !ban;
        }
        return ans;
    }
};
