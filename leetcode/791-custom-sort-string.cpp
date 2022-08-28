class Solution {
public:
    string customSortString(string order, string s) {
        const int maxd = 26;
        int ctr[maxd + 1] = {};
        bool vis[maxd + 1] = {};
        for(char ch: order)
            vis[(int)(ch - 'a')] = 1;
        for(char ch: s) {
            int o = ch - 'a';
            ++ctr[o];
            if(!vis[o]) {
                vis[o] = 1;
                order.push_back(ch);
            }
        }
        int n = 0;
        for(char ch: order) {
            int o = ch - 'a';
            while(ctr[o]--)
                s[n++] = ch;
        }
        return s;
    }
};
