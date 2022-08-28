class Solution {
public:
    string removeKdigits(string num, int k) {
        int len = (int)num.length(), rem = k;
        string ret = "";
        for(int i = 0; i < len; ++i) {
            char &ch = num[i];
            while(rem > 0 && !ret.empty() && ret.back() > ch) {
                ret.pop_back();
                --rem;
            }
            ret.push_back(ch);
        }
        while(rem > 0) {
            ret.pop_back();
            --rem;
        }
        len = (int)ret.length();
        int sta;
        for(sta = 0; sta < len && ret[sta] == '0'; ++sta);
        return sta < len ? ret.substr(sta, len - sta) : "0";
    }
};
