class Solution {
public:
    int findClosest(vector<string>& words, string word1, string word2) {
        int n = words.size(), ans = n, u = -1, v = -1;
        for(int i = 0; i < n; ++i)
            if(words[i] == word1) {
                u = i;
                if(v != -1)
                    ans = min(ans, u - v);
            } else if(words[i] == word2) {
                v = i;
                if(u != -1)
                    ans = min(ans, v - u);
            }
        return ans;
    }
};
