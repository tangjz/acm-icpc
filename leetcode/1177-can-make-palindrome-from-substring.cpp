class Solution {
    static const int maxc = 26, BLEN = maxc >> 1, BMSK = (1 << BLEN) - 1;
public:
    vector<bool> canMakePaliQueries(string s, vector<vector<int>>& queries) {
        static int mx = 1, bits[BMSK + 2] = {};
        vector<int> psum = {0};
        for(char ch: s)
            psum.push_back(psum.back() ^ (1 << (ch - 'a')));
        vector<bool> ans;
        ans.reserve(queries.size());
        for(auto &it: queries) {
            int msk = psum[it[1] + 1] ^ psum[it[0]], lo = msk & BMSK, hi = msk >> BLEN;
            for( ; mx <= lo || mx <= hi; ++mx)
                bits[mx] = bits[mx >> 1] + (mx & 1);
            ans.push_back((bits[lo] + bits[hi]) / 2 <= it[2]);
        }
        return ans;
    }
};
