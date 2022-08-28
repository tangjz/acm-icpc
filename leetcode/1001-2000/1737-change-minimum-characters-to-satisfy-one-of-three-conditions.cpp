class Solution {
public:
    int minCharacters(string a, string b) {
        const int maxd = 26;
        int n = a.size(), m = b.size();
        int ans = n + m;
        vector<int> cA(maxd), cB(maxd);
        for(char ch: a)
            ++cA[(int)(ch - 'a')];
        for(char ch: b)
            ++cB[(int)(ch - 'a')];
        int bestA = n, bestB = m;
        int preA = 0, preB = 0;
        for(int i = 0; i < maxd; ++i) {
            bestA = min(bestA, n - cA[i]);
            bestB = min(bestB, m - cB[i]);
            if(i > 0) {
                ans = min(ans, n - preA + preB);
                ans = min(ans, preA + m - preB);
            }
            preA += cA[i];
            preB += cB[i];
        }
        ans = min(ans, bestA + bestB);
        return ans;
    }
};
