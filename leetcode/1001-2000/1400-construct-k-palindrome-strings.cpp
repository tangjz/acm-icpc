class Solution {
public:
    bool canConstruct(string s, int k) {
        const int maxd = 26;
        int len = (int)s.length();
        vector<int> ctr(maxd, 0);
        for(char ch : s)
            ++ctr[(int)(ch - 'a')];
        int odd = 0;
        for(int x : ctr)
            odd += x & 1;
        return odd <= k && len >= k;
    }
};
