class Solution {
public:
    int rearrangeCharacters(string s, string target) {
        const int maxd = 26;
        vector<int> A(maxd), B(maxd);
        for(char ch: s)
            ++A[ch - 'a'];
        for(char ch: target)
            ++B[ch - 'a'];
        int ans = INT_MAX;
        for(int i = 0; i < maxd; ++i)
            if(B[i])
                ans = min(ans, A[i] / B[i]);
        return ans;
    }
};
