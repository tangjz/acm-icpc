class Solution {
public:
    string countAndSay(int n) {
        string ret = "1";
        for(int i = 1; i < n; ++i) {
            string tmp = "";
            char las = ret.front();
            int cnt = 0;
            for(char ch: ret) {
                if(ch != las) {
                    tmp += to_string(cnt);
                    tmp += las;
                    las = ch;
                    cnt = 0;
                }
                ++cnt;
            }
            tmp += to_string(cnt);
            tmp += las;
            ret = move(tmp);
        }
        return ret;
    }
};
