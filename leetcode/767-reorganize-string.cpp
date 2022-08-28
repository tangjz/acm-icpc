class Solution {
public:
    string reorganizeString(string s) {
        static const int maxd = 26;
        static int ctr[maxd];
        memset(ctr, 0, sizeof(ctr));
        for(char ch: s)
            ++ctr[(int)(ch - 'a')];
        int n = s.size(), las = -1;
        string ret = "";
        for(int i = 0; i < n; ++i) {
            int cur = -1;
            for(int j = 0; j < maxd; ++j)
                if(ctr[j] && j != las && (cur == -1 || ctr[j] > ctr[cur]))
                    cur = j;
            if(cur == -1)
                return "";
            ret.push_back('a' + cur);
            --ctr[cur];
            las = cur;
        }
        return ret;
    }
};
