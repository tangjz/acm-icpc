class Solution {
public:
    string convertToTitle(int columnNumber) {
        typedef long long LL;
        int n = 0;
        LL pw = 1;
        while(1) {
            ++n;
            pw *= 26;
            if(columnNumber <= pw) {
                string buf = "";
                --columnNumber;
                for(int i = 0; i < n; ++i) {
                    buf.push_back('A' + (columnNumber % 26));
                    columnNumber /= 26;
                }
                reverse(buf.begin(), buf.end());
                return buf;
            }
            columnNumber -= pw;
        }
        return "";
    }
};
