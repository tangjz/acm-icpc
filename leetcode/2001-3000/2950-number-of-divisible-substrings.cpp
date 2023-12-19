class Solution {
public:
    int countDivisibleSubstrings(string word) {
        int n = word.size(), ans = 0;
        vector<int> psum = {0};
        for(char ch: word)
            psum.push_back(psum.back() + (ch - 'a' + 4) / 3);
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j <= n; ++j)
                ans += (psum[j] - psum[i]) % (j - i) == 0;
        return ans;
    }
};
