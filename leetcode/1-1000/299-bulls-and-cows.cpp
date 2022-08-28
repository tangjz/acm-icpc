class Solution {
public:
    string getHint(string secret, string guess) {
        const int maxd = 10;
        int n = (int)secret.size();
        vector<int> ctr1(maxd), ctr2(maxd);
        for(char ch: secret)
            ++ctr1[(int)(ch - '0')];
        for(char ch: guess)
            ++ctr2[(int)(ch - '0')];
        int ans1 = 0, ans2 = 0;
        for(int i = 0; i < n; ++i)
            ans1 += secret[i] == guess[i];
        for(int i = 0; i < maxd; ++i)
            ans2 += min(ctr1[i], ctr2[i]);
        ans2 -= ans1;
        return to_string(ans1) + 'A' + to_string(ans2) + 'B';
    }
};
