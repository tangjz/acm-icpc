class Solution {
    bool isUpper(char ch) {
        return ch >= 'A' && ch <= 'Z';
    }
    bool match(string const &pat, string const &buf) {
        char lft = pat.front(), rht = buf.front();
        if((isUpper(lft) || isUpper(rht)) && lft != rht)
            return false;
        int m = pat.size(), cnt = 0;
        for(char ch: buf) {
            cnt += ch == pat[cnt];
            if(cnt == m)
                return true;
        }
        return false;
    }
    vector<string> split(string const &pat) {
        vector<string> ret;
        for(char ch: pat) {
            if(ret.empty() || isUpper(ch))
                ret.push_back("");
            ret.back().push_back(ch);
        }
        return move(ret);
    }
public:
    vector<bool> camelMatch(vector<string>& queries, string pattern) {
        vector<bool> ans;
        vector<string> pat = split(pattern), que;
        int m = pat.size();
        bool canDrop = isUpper(pat.front().front());
        for(auto &it: queries) {
            que = split(it);
            if(canDrop && !isUpper(que.front().front())) {
                que.erase(que.begin());
            }
            bool good = que.size() == m;
            for(int i = 0; good && i < m; ++i) {
                good &= match(pat[i], que[i]);
            }
            ans.push_back(good);
        }
        return ans;
    }
};
