class Solution {
public:
    string reformatNumber(string number) {
        int cnt = 0;
        string ret = "";
        for(char ch : number)
            if(ch >= '0' && ch <= '9') {
                ret += ch;
                if((++cnt) == 3) {
                    ret += '-';
                    cnt = 0;
                }
            }
        if(!cnt) {
            ret.pop_back();
        } else if(cnt == 1) {
            char ch1 = ret.back();
            ret.pop_back();
            ret.pop_back();
            char ch0 = ret.back();
            ret.pop_back();
            ret += '-';
            ret += ch0;
            ret += ch1;
        }
        return ret;
    }
};
