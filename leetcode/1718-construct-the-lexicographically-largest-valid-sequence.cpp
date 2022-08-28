class Solution {
    bool dfs(vector<int>::iterator cur, vector<int>::iterator end, vector<int> &pL, vector<int> &pR) {
        if(cur == end)
            return 1;
        if(*cur)
            return dfs(cur + 1, end, pL, pR);
        for(int i = pL.back(); i > 0; i = pL[i]) {
            if(i > 1 && (cur + i >= end || *(cur + i)))
                continue;
            *cur = i;
            if(i > 1)
                *(cur + i) = i;
            pL[pR[i]] = pL[i];
            pR[pL[i]] = pR[i];
            if(dfs(cur + 1, end, pL, pR))
                return 1;
            pL[pR[i]] = i;
            pR[pL[i]] = i;
            *cur = 0;
            if(i > 1)
                *(cur + i) = 0;
        }
        return 0;
    }
public:
    vector<int> constructDistancedSequence(int n) {
        vector<int> path(n + n - 1), pL(n + 2), pR(n + 2);
        pR[0] = 1;
        for(int i = 1; i <= n; ++i) {
            pL[i] = i - 1;
            pR[i] = i + 1;
        }
        pL[n + 1] = n;
        dfs(path.begin(), path.end(), pL, pR);
        return path;
    }
};
