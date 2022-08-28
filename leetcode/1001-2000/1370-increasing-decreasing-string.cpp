class Solution {
public:
    string sortString(string s) {
        const int maxd = 26;
        vector<int> ctr(maxd, 0);
        for(char ch : s)
            ++ctr[(int)(ch - 'a')];
        string ret = "";
        while(1) {
            bool upd = 0;
            for(int i = 0; i < maxd; ++i)
                if(ctr[i] > 0) {
                    upd = 1;
                    ret += 'a' + i;
                    --ctr[i];
                }
            for(int i = maxd - 1; i >= 0; --i)
                if(ctr[i] > 0) {
                    upd = 1;
                    ret += 'a' + i;
                    --ctr[i];
                }
            if(!upd)
                break;
        }
        return ret;
    }
};
