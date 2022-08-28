class Solution {
public:
    int maxNumberOfBalloons(string text) {
        const int maxc = 26;
        vector<int> ctr(maxc), need(maxc);
        for(char ch: (string)"balloon")
            ++need[(int)(ch - 'a')];
        for(char ch: text)
            ++ctr[(int)(ch - 'a')];
        int ans = INT_MAX;
        for(int i = 0; i < maxc; ++i)
            if(need[i])
                ans = min(ans, ctr[i] / need[i]);
        return ans;
    }
};
