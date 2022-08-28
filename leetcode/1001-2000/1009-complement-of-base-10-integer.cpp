class Solution {
public:
    int bitwiseComplement(int n) {
        int mx = 1;
        for( ; n >= (1 << mx); ++mx);
        return n ^ ((1 << mx) - 1);
    }
};
