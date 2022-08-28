class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        sort(words.begin(), words.end(), [&](string const &u, string const &v) {
            return u.size() > v.size();
        });
        int ans = 0;
        unordered_set<string> sp;
        for(string &buf: words) {
            reverse(buf.begin(), buf.end());
            if(sp.count(buf))
                continue;
            ans += buf.size() + 1;
            while(!buf.empty()) {
                sp.insert(buf);
                buf.pop_back();
            }
        }
        return ans;
    }
};
