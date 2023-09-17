class Solution {
public:
    int addMinimum(string word) {
        int cnt = 0, pos = 0;
        for(char ch: word) {
            int cur = ch - 'a';
            if(cur < pos) {
                ++cnt;
                pos = 0;
            }
            pos = cur + 1;
        }
        cnt += pos > 0;
        return cnt * 3 - word.size();
    }
};
