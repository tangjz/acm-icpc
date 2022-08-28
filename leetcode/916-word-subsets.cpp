class Solution {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        static const int maxd = 26;
        static int low[maxd + 1], ctr[maxd + 1];
        memset(low, 0, sizeof(low));
        for(auto &buf: words2) {
            memset(ctr, 0, sizeof(ctr));
            for(char ch: buf) {
                int o = ch - 'a';
                low[o] = max(low[o], ++ctr[o]);
            }
        }
        int n = 0, m = 0;
        for(int i = 0; i < maxd; ++i)
            m += low[i] > 0;
        for(auto &buf: words1) {
            int rem = m;
            memcpy(ctr, low, sizeof(ctr));
            for(char ch: buf) {
                int o = ch - 'a';
                rem -= !(--ctr[o]);
                if(!rem)
                    break;
            }
            if(!rem)
                words1[n++] = buf;
        }
        words1.resize(n);
        return words1;
    }
};
