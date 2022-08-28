class Solution {
public:
    string printBin(double num) {
        string ret = "0.";
        while(num && ret.size() <= 32) {
            num *= 2;
            if(num >= 1) {
                ret.push_back('1');
                num -= 1;
            } else {
                ret.push_back('0');
            }
        }
        return ret.size() <= 32 ? ret : "ERROR";
    }
};
