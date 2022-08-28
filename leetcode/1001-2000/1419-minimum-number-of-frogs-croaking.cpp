class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs) {
        const char *pat = "croak";
        vector<int> pos[5];
        int len = 0;
        for(char ch : croakOfFrogs) {
            for(int i = 0; i < 5; ++i)
                if(ch == pat[i])
                    pos[i].push_back(len++);
        }
        int sz = pos[0].size();
        for(int i = 1; i < 5; ++i)
            if(pos[i].size() != sz)
                return -1;
        vector<int> occ = vector<int>(len + 1, 0);
        for(int i = 0; i < sz; ++i) {
            for(int j = 1; j < 5; ++j)
                if(pos[j - 1][i] > pos[j][i])
                    return -1;
            ++occ[pos[0][i]];
            --occ[pos[4][i] + 1];
        }
        int mx = 0;
        for(int i = 0; i < len; ++i) {
            mx = max(mx, occ[i]);
            occ[i + 1] += occ[i];
        }
        return mx;
    }
};
