class Solution {
public:
    int countMatches(vector<vector<string>>& items, string ruleKey, string ruleValue) {
        const string pat[] = {"type", "color", "name"};
        int pos = 0;
        for( ; pos < 3 && pat[pos] != ruleKey; ++pos);
        int ans = 0;
        for(auto &it: items)
            ans += it[pos] == ruleValue;
        return ans;
    }
};
