class Solution {
public:
    string toHexspeak(string num) {
        typedef long long LL;
        LL n = stol(num); // n > 0
        string ret;
        for( ; n > 0; n >>= 4) {
            int v = n & 15;
            if(v < 2) {
                ret.push_back("OI"[v]);
            } else if(v >= 10) {
                ret.push_back('A' + (v - 10));
            } else {
                return "ERROR";
            }
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
