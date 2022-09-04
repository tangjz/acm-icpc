class Solution {
public:
    int minimumBuckets(string seq) {
        int n = seq.size(), m = 0;
        for(int i = 0; i < n; ++i) {
            if(seq[i] != 'H')
                continue;
            char pL = i > 0 ? seq[i - 1] : 'H';
            char pR = i + 1 < n ? seq[i + 1] : 'H';
            if(pL == 'H' && pR == 'H')
                return -1;
            if(pL == 'O' || pR == 'O')
                continue;
            (pR == '.' ? seq[i + 1] : seq[i - 1]) = 'O';
            ++m;
        }
        return m;
    }
};
