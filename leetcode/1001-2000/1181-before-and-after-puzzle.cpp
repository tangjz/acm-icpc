class Solution {
public:
    vector<string> beforeAndAfterPuzzles(vector<string>& phrases) {
        unordered_map<string, int> idx;
        auto getID = [&](string const &s) {
            return idx.insert({s, idx.size()}).first -> second;
        };
        int n = phrases.size();
        vector<int> pos(n), pre(n), suf(n);
        for(int i = 0; i < n; ++i) {
            string &cur = phrases[i];
            auto p = cur.find(' ');
            if(p == string::npos) {
                pos[i] = -1;
                pre[i] = suf[i] = getID(cur);
            } else {
                pos[i] = p;
                pre[i] = getID(cur.substr(0, p));
                p = cur.rfind(' ');
                suf[i] = getID(cur.substr(p + 1));
            }
        }
        set<string> ret;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                if(i != j && suf[i] == pre[j]) {
                    if(pos[j] == -1) {
                        ret.insert(phrases[i]);
                    } else {
                        ret.insert(phrases[i] + phrases[j].substr(pos[j]));
                    }
                }
        return vector<string>(ret.begin(), ret.end());
    }
};
