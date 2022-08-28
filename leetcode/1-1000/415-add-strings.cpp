class Solution {
public:
    string addStrings(string num1, string num2) {
        int n = num1.size(), m = num2.size();
        string ret = "";
        int rem = 0;
        for(int i = 0; i < n || i < m; ++i) {
            rem += i < n ? num1[n - 1 - i] - '0' : 0;
            rem += i < m ? num2[m - 1 - i] - '0' : 0;
            ret += '0' + (rem % 10);
            rem /= 10;
        }
        if(rem > 0)
            ret += '0' + rem;
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
