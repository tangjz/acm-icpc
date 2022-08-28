class Solution {
public:
    vector<long long> kthPalindrome(vector<int>& queries, int intLength) {
        typedef long long LL;
        vector<LL> pw(intLength + 1);
        pw[0] = 1;
        for(int i = 1; i <= intLength; ++i)
            pw[i] = pw[i - 1] * 10;
        int half = (intLength + 1) / 2;
        vector<LL> ret;
        for(int x: queries) {
            if(x > pw[half] - pw[half - 1]) {
                ret.push_back(-1LL);
                continue;
            }
            LL val = x + pw[half - 1] - 1, tmp = val;
            if(half + half > intLength)
                tmp /= 10;
            for(int i = half; i < intLength; ++i) {
                val = val * 10 + (tmp % 10);
                tmp /= 10;
            }
            ret.push_back(val);
        }
        return ret;
    }
};
