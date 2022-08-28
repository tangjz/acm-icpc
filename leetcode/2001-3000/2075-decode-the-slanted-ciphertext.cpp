class Solution {
public:
    string decodeCiphertext(string enc, int R) {
        int n = enc.length();
        if(!n)
            return "";
        int C = (n - 1) / R + 1;
        vector<string> dec(C);
        for(int i = 0, idx = 0; i < R; ++i)
            for(int j = 0; j < C; ++j, ++idx)
                if(j >= i)
                    dec[j - i] += enc[idx];
        while(!dec.empty()) {
            string &cur = dec.back();
            int pos, len = cur.length();
            for(pos = len - 1; pos >= 0 && cur[pos] == ' '; --pos);
            if(pos >= 0) {
                cur = cur.substr(0, pos + 1);
                break;
            } else {
                dec.pop_back();
            }
        }
        string ret = "";
        for(auto &it: dec)
            ret += it;
        return ret;
    }
};
