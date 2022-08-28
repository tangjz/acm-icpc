class Solution {
public:
    int minSteps(string s, string t) {
        const int maxd = 26;
        vector<int> ctr(maxd, 0);
        for(char ch : s)
            ++ctr[(int)(ch - 'a')];
        for(char ch : t)
            --ctr[(int)(ch - 'a')];
        int ret = 0;
        for(int x : ctr)
            ret += abs(x);
        return ret >> 1;
    }
};
