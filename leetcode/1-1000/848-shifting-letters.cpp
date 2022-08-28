class Solution {
public:
    string shiftingLetters(string s, vector<int>& shifts) {
        const int maxd = 26;
        int n = s.size();
        for(int i = n - 1; i >= 0; --i) {
            if(i + 1 < n)
                shifts[i] += shifts[i + 1];
            shifts[i] %= maxd;
            s[i] = (s[i] - 'a' + shifts[i]) % maxd + 'a';
        }
        return s;
    }
};
