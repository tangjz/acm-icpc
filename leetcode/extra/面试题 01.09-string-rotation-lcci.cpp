class Solution {
    int getMinRep(string const &s) {
        int n = s.size(), i = 0, j = 1, k = 0, dt;
        while(i < n && j < n && k < n) {
            dt = s[(i + k) % n] - s[(j + k) % n];
            if(!dt) {
                ++k;
            } else {
                (dt < 0 ? j : i) += k + 1;
                j += i == j;
                k = 0;
            }
        }
        return min(i, j);
    }
public:
    bool isFlipedString(string s1, string s2) {
        if(s1.size() != s2.size())
            return 0;
        int n = s1.size();
        int dt1 = getMinRep(s1), dt2 = getMinRep(s2);
        (dt2 -= dt1) < 0 && (dt2 += n);
        for(int i = 0; i < n; ++i, (++dt2) == n && (dt2 = 0))
            if(s1[i] != s2[dt2])
                return 0;
        return 1;
    }
};
