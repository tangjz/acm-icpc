class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        unordered_set<string> cand;
        sort(words.begin(), words.end(), [&](string const &u, string const &v) {
            return u.size() < v.size();
        });
        for(auto &s: words) {
            reverse(s.begin(), s.end());
            cand.insert(s);
            while(!s.empty()) {
                s.pop_back();
                cand.erase(s);
            }
        }
        int ans = 0;
        for(auto &it: cand)
            ans += it.size() + 1;
        return ans;
    }
};
