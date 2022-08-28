class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        const int QLEN = 10, BMSK = (1 << (QLEN + QLEN)) - 1;
        static string pat = "ACGT";
        static int tr[1 << 8 | 1] = {};
        for(int i = 0; i < (int)pat.size(); ++i)
            tr[(int)pat[i]] = i;
        unordered_map<int, int> ctr;
        for(int i = 0, msk = 0; i < (int)s.size(); ++i) {
            msk = (msk << 2 | tr[(int)s[i]]) & BMSK;
            if(i + 1 >= QLEN)
                ++ctr[msk];
        }
        vector<string> ret;
        for(auto &it: ctr) {
            if(it.second == 1)
                continue;
            string buf = "";
            for(int i = 0, rem = it.first; i < QLEN; ++i, rem >>= 2)
                buf.push_back(pat[rem & 3]);
            reverse(buf.begin(), buf.end());
            ret.push_back(buf);
        }
        return ret;
    }
};
