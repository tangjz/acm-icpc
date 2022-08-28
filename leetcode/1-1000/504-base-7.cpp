class Solution {
public:
    string convertToBase7(int num) {
        string ret = "";
        bool neg = false;
        if(num < 0) {
            neg = true;
            num = -num;
        } else if(!num) {
            ret += '0';
        }
        while(num > 0) {
            ret += '0' + (num % 7);
            num /= 7;
        }
        if(neg)
            ret += '-';
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
