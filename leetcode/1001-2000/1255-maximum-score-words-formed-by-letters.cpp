class Solution {
    int dfs(int sum, vector<string>::iterator cur, vector<string>::iterator end, vector<int> &w, vector<int> &rem) {
        if(cur == end)
            return sum;
        int ret = dfs(sum, cur + 1, end, w, rem);
        bool chk = 1;
        for(char ch : *cur) {
            int o = (int)(ch - 'a');
            chk &= (--rem[o]) >= 0;
            sum += w[o];
        }
        if(chk)
            ret = max(ret, dfs(sum, cur + 1, end, w, rem));
        for(char ch : *cur) {
            int o = (int)(ch - 'a');
            ++rem[o];
            sum -= w[o];
        }
        return ret;
    }
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        const int maxd = 26;
        vector<int> rem(maxd);
        for(char ch : letters)
            ++rem[(int)(ch - 'a')];
        return dfs(0, words.begin(), words.end(), score, rem);
    }
};
