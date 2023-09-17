class Solution {
public:
    string smallestNumber(long long n) {
        string ret = "";
        while(n > 1) {
            int d = 9;
            for( ; d > 1 && n % d > 0; --d);
            if(d == 1)
                return "-1";
            ret.push_back('0' + d);
            n /= d;
        }
        reverse(ret.begin(), ret.end());
        if(ret.empty())
            ret.push_back('1');
        return ret;
    }
};
