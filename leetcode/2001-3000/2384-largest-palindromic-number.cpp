class Solution {
public:
    string largestPalindromic(string num) {
        const int maxd = 10;
        auto parse = [&](vector<int> &ctr, int sp) -> string {
            string s = "";
            for(int i = maxd - 1; i >= 0; --i) {
                int adt = (ctr[i] - (i == sp)) / 2;
                if(!i && adt > 0 && s == "")
                    continue;
                while(adt--)
                    s.push_back('0' + i);
            }
            string t = s;
            reverse(t.begin(), t.end());
            if(sp >= 0)
                s.push_back('0' + sp);
            return s + t;
        };
        vector<int> ctr(maxd);
        for(char ch: num)
            ++ctr[(int)(ch - '0')];
        string ret = parse(ctr, -1);
        for(int i = 0; i < maxd; ++i) {
            if(!ctr[i])
                continue;
            string tmp = parse(ctr, i);
            if(ret.size() < tmp.size() || (ret.size() == tmp.size() && ret < tmp))
                ret = tmp;
        }
        return ret;
    }
};
