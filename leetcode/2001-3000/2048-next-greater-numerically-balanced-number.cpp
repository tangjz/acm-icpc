class Solution {
public:
    int nextBeautifulNumber(int n) {
        static const int maxd = 10;
        string rep = to_string(++n);
        reverse(rep.begin(), rep.end());
        int bad = 0;
        vector<int> ctr(maxd);
        for(char ch: rep) {
            int o = ch - '0';
            bad -= ctr[o] && ctr[o] != o;
            ++ctr[o];
            bad += ctr[o] && ctr[o] != o;
        }
        while(bad) {
            ++n;
            bool sp = 0;
            for(int i = 0; ; ++i) {
                if(i == rep.size()) {
                    rep.push_back('0');
                    sp = 1;
                }
                int o = rep[i] - '0';
                if(!sp) {
                    bad -= ctr[o] && ctr[o] != o;
                    --ctr[o];
                    bad += ctr[o] && ctr[o] != o;
                }
                (++o) == maxd && (o = 0);
                bad -= ctr[o] && ctr[o] != o;
                ++ctr[o];
                bad += ctr[o] && ctr[o] != o;
                rep[i] = '0' + o;
                if(o)
                    break;
            }
        }
        return n;
    }
};
