class Solution {
public:
    int findString(vector<string>& words, string s) {
        int n = words.size(), L = 0, R = n - 1;
        while(L <= R) {
            int M = (L + R) >> 1;
            int ML = M, MR = M;
            for( ; ML >= L && words[ML].empty(); --ML);
            for( ; MR <= R && words[MR].empty(); ++MR);
            if(ML >= L) {
                if(s == words[ML])
                    return ML;
                if(s < words[ML]) {
                    R = ML - 1;
                    continue;
                }
            }
            if(MR <= R) {
                if(s == words[MR])
                    return MR;
                if(s > words[MR]) {
                    L = MR + 1;
                    continue;
                }
            }
            return -1;
        }
        return -1;
    }
};
