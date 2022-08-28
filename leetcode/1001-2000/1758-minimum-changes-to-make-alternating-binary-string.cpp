class Solution {
public:
    int minOperations(string s) {
        int n = (int)s.size(), ctr = 0;
        char cur = '0';
        for(char ch: s) {
            ctr += ch != cur;
            cur = '1' - cur + '0';
        }
        return min(ctr, n - ctr);
    }
};
