class Solution {
public:
    vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
        typedef long long LL;
        vector<vector<LL> > ret;

        int n = segments.size();
        map<int, LL> events;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < 2; ++j)
                events[segments[i][j]] += segments[i][2] * (1 - j - j);
        LL las = INT_MAX, sum = 0;
        for(auto &it: events) {
            if(sum > 0)
                ret.push_back({las, (LL)it.first, sum});
            las = it.first;
            sum += it.second;
        }
        return ret;
    }
};
