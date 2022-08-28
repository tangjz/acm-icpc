class Solution {
public:
    vector<string> ambiguousCoordinates(string s) {
        int n = s.size();
        vector<string> ret;
        auto gen = [&](vector<string> &cand, int L, int R) {
            if(s[L] == '0') {
                if(L == R) {
                    cand.push_back(s.substr(L, R - L + 1));
                } else if(s[R] != '0') {
                    cand.push_back("0." + s.substr(L + 1, R - L));
                }
            } else {
                cand.push_back(s.substr(L, R - L + 1));
                if(s[R] != '0')
                    for(int k = L; k < R; ++k)
                        cand.push_back(s.substr(L, k - L + 1) + "." + s.substr(k + 1, R - k));
            }
        };
        for(int i = 2; i < n - 1; ++i) { // [1, i) [i, n - 1)
            vector<string> lft, rht;
            gen(lft, 1, i - 1);
            gen(rht, i, n - 2);
            for(auto &it: lft)
                for(auto &jt: rht)
                    ret.push_back("(" + it + ", " + jt + ")");
        }
        return ret;
    }
};
