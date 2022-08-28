class Solution {
public:
    int calculateTime(string A, string B) {
        unordered_map<char, int> pos;
        for(int i = 0; i < 26; ++i)
            pos[A[i]] = i;
        int las = 0, cur, ans = 0;
        for(char ch: B) {
            cur = pos[ch];
            ans += abs(las - cur);
            las = cur;
        }
        return ans;
    }
};
