class Solution {
    int count(string_view s, char pat) {
        int cnt = 0;
        for(char ch: s)
            cnt += ch == pat;
        return cnt;
    }
public:
    int mostWordsFound(vector<string>& sentences) {
        int ans = 0;
        for(auto &it: sentences)
            ans = max(ans, count(it, ' ') + 1);
        return ans;
    }
};
