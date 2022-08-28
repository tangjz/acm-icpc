class Solution {
public:
    vector<int> volunteerDeployment(vector<int>& finalCnt, long long totalNum, vector<vector<int>>& edges, vector<vector<int>>& plans) {
        typedef long long LL;
        int n = finalCnt.size() + 1;
        vector<vector<int> > e(n);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        vector<pair<LL, LL> > ctr(n);
        ctr[0] = {1, 0};
        for(int i = 1; i < n; ++i)
            ctr[i] = {0, (LL)finalCnt[i - 1]};
        while(!plans.empty()) {
            int typ = plans.back()[0], idx = plans.back()[1];
            plans.pop_back();
            if(typ == 1) {
                ctr[idx].first *= 2;
                ctr[idx].second *= 2;
            } else if(typ == 2) {
                for(int v: e[idx]) {
                    ctr[v].first -= ctr[idx].first;
                    ctr[v].second -= ctr[idx].second;
                }
            } else {
                for(int v: e[idx]) {
                    ctr[v].first += ctr[idx].first;
                    ctr[v].second += ctr[idx].second;
                }
            }
        }
        LL c0 = 0, c1 = 0;
        for(auto &it: ctr) {
            c0 += it.first;
            c1 += it.second;
        }
        LL x = c0 ? (totalNum - c1) / c0 : 0;
        vector<int> ret(n);
        for(int i = 0; i < n; ++i)
            ret[i] = ctr[i].first * x + ctr[i].second;
        return ret;
    }
};
