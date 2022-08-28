class Solution {
public:
    bool makeEqual(vector<string>& words) {
        const int maxd = 26;
        vector<int> ctr(maxd);
        for(auto &it: words)
            for(char ch: it)
                ++ctr[(int)(ch - 'a')];
        int n = words.size();
        for(int i = 0; i < maxd; ++i)
            if(ctr[i] % n > 0)
                return false;
        return true;
    }
};
