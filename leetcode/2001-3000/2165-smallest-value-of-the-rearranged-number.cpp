class Solution {
public:
    long long smallestNumber(long long num) {
        typedef long long LL;
        string buf = to_string(abs(num));
        sort(buf.begin(), buf.end());
        if(num < 0) {
            buf.push_back('-');
            reverse(buf.begin(), buf.end());
        } else if(num > 0 && buf[0] == '0') {
            int p = 1;
            for( ; buf[p] == '0'; ++p);
            swap(buf[0], buf[p]);
        }
        return stol(buf);
    }
};
