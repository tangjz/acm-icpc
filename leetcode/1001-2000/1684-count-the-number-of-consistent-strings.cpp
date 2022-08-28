class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        unordered_set<char> vis;
        for(char ch: allowed)
            vis.insert(ch);
        int ans = 0;
        for(auto &it: words) {
            bool bad = false;
            for(char ch: it)
                if(!vis.count(ch)) {
                    bad = true;
                    break;
                }
            ans += !bad;
        }
        return ans;
    }
};
