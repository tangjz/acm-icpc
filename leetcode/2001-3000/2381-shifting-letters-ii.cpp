class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& op) {
        int n = s.size();
        vector<int> ctr(n + 1);
        for(auto &it: op) {
            int sgn = it[2] ? 1 : -1;
            ctr[it[0]] += sgn;
            ctr[it[1] + 1] -= sgn;
        }
        const int maxd = 26;
        for(int i = 0; i < n; ++i) {
            (ctr[i] %= maxd) < 0 && (ctr[i] += maxd);
            s[i] = (s[i] - 'a' + ctr[i]) % maxd + 'a';
            ctr[i + 1] += ctr[i];
        }
        return s;
    }
};
