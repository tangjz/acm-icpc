class Solution {
public:
    int wordCount(vector<string>& startWords, vector<string>& targetWords) {
        const int maxd = 26;
        set<vector<int> > vis;
        for(auto &it: startWords) {
            vector<int> ctr(maxd);
            for(char ch: it)
                ++ctr[(int)(ch - 'a')];
            vis.insert(ctr);
        }
        int ans = 0;
        for(auto &it: targetWords) {
            vector<int> ctr(maxd);
            for(char ch: it)
                ++ctr[(int)(ch - 'a')];
            bool chk = false;
            for(int i = 0; !chk && i < maxd; ++i)
                if(ctr[i] == 1) {
                    --ctr[i];
                    chk |= vis.count(ctr);
                    ++ctr[i];
                }
            ans += chk;
        }
        return ans;
    }
};
