class Solution {
    int query(string &seq, int k, char ch) {
        int n = seq.length(), ans = 0;
        for(int i = 0, j = 0, c = 0; i < n; ++i) {
            c += seq[i] == ch;
            while(c > k) {
                c -= seq[j] == ch;
                ++j;
            }
            ans = max(ans, i - j + 1);
        }
        return ans;
    }
public:
    int maxConsecutiveAnswers(string seq, int k) {
        return max(query(seq, k, 'T'), query(seq, k, 'F'));
    }
};
