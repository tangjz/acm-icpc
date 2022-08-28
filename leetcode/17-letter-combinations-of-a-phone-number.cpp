class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<char> cand[10];
        for(int i = 2, j = 0; i < 10; ++i) {
            int cnt = 3 + (i == 7 || i == 9);
            while(cnt--)
                cand[i].push_back(j++);
        }
        if(!digits.size())
            return {};
        vector<string> ret = {""};
        for(char ch: digits) {
            int o = ch - '0';
            vector<string> nxt;
            for(string &it: ret)
                for(int adt: cand[o])
                    nxt.push_back(it + (char)('a' + adt));
            ret = move(nxt);
        }
        return ret;
    }
};
