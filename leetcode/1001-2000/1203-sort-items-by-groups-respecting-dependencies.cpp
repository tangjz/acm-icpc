class Solution {
public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        for(int &x: group)
            if(x == -1)
                x = m++;
        vector<int> degA(n), degB(m);
        vector<vector<int> > pos(m), eA(n), eB(m);
        for(int i = 0; i < n; ++i) {
            pos[group[i]].push_back(i);
            for(int j: beforeItems[i]) {
                if(group[i] == group[j]) {
                    ++degA[i];
                    eA[j].push_back(i);
                } else {
                    ++degB[group[i]];
                    eB[group[j]].push_back(group[i]);
                }
            }
        }
        vector<int> retA, retB;
        for(int i = 0; i < m; ++i)
            if(!degB[i])
                retB.push_back(i);
        for(int i = 0; i < (int)retB.size(); ++i) {
            int u = retB[i];
            for(int v: eB[u])
                if(!(--degB[v]))
                    retB.push_back(v);
        }
        if(retB.size() != m)
            return {};
        for(int x: retB) {
            int sta = retA.size();
            for(int i: pos[x])
                if(!degA[i])
                    retA.push_back(i);
            for(int i = sta; i < (int)retA.size(); ++i) {
                int u = retA[i];
                for(int v: eA[u])
                    if(!(--degA[v]))
                        retA.push_back(v);
            }
            if(retA.size() - sta != pos[x].size())
                return {};
        }
        return retA;
    }
};
