class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        const int maxd = 26;
        vector<int> ctr(maxd);
        for(char ch: s)
            ++ctr[(int)(ch - 'a')];
        string t = "";
        for(int i = maxd - 1, j = i - 1; i >= 0; --i) {
            if(!ctr[i])
                continue;
            for(j = min(j, i - 1); j >= 0 && !ctr[j]; --j);
            bool bad = 0;
            while(ctr[i] > repeatLimit) {
                for(int k = 0; k < repeatLimit; ++k, --ctr[i])
                    t.push_back('a' + i);
                if(j < 0) {
                    bad = 1;
                    break;
                }
                --ctr[j];
                t.push_back('a' + j);
                for( ; j >= 0 && !ctr[j]; --j);
            }
            if(bad)
                break;
            while(ctr[i]--)
                t.push_back('a' + i);
        }
        return t;
    }
};
