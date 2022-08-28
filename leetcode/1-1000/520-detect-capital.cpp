class Solution {
public:
    bool detectCapitalUse(string word) {
        int tot = 0, cnt = 0;
        for(char ch : word) {
            ++tot;
            cnt += ch >= 'A' && ch <= 'Z';
        }
        return !cnt || cnt == tot || (tot > 0 && cnt == 1 && word[0] >= 'A' && word[0] <= 'Z');
    }
};
