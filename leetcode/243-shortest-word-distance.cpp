class Solution {
public:
    int shortestDistance(vector<string>& wordsDict, string word1, string word2) {
        int n = wordsDict.size(), ans = INT_MAX, u = -1, v = -1;
        for(int i = 0; i < n; ++i)
            if(wordsDict[i] == word1) {
                u = i;
                if(v != -1)
                    ans = min(ans, u - v);
            } else if(wordsDict[i] == word2) {
                v = i;
                if(u != -1)
                    ans = min(ans, v - u);
            }
        return ans;
    }
};
