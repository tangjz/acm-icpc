class Solution {
public:
    string maximumBinaryString(string binary) {
        int n = (int)binary.size(), cnt[2] = {};
        for(char ch : binary)
            ++cnt[(int)(ch - '0')];
        int pre = 0;
        for( ; pre < n && binary[pre] == '1'; ++pre, --cnt[1]);
        string &ret = binary;
        ret.resize(pre);
        for(int i = 1; i < cnt[0]; ++i)
            ret += '1';
        if(cnt[0] > 0)
            ret += '0';
        for(int i = 0; i < cnt[1]; ++i)
            ret += '1';
        return ret;
    }
};
