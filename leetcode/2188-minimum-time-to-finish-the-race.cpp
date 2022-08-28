class Solution {
public:
    int minimumFinishTime(vector<vector<int>>& tires, int changeTime, int numLaps) {
        const int INF = 0x3f3f3f3f;
        int upp = ((*min_element(tires.begin(), tires.end()))[0] + changeTime) * numLaps;
        vector<int> f(numLaps + 1, INF);
        f[0] = 0;
        for(auto &it: tires) {
            int sum = changeTime, cur = it[0];
            for(int i = 1; i <= numLaps; ++i) {
                sum += cur;
                if(sum > upp)
                    break;
                f[i] = min(f[i], sum);
                if(cur > INF / it[1])
                    break;
                cur *= it[1];
            }
        }
        int mx = 0;
        for( ; mx <= numLaps && f[mx] < INF; ++mx);
        for(int i = 1; i <= numLaps; ++i) {
            // printf("%d: %d", i, f[i]);
            for(int j = 1; j < i && j < mx; ++j)
                f[i] = min(f[i], f[i - j] + f[j]);
            // printf(" %d\n", f[i]);
        }
        return f.back() - changeTime;
    }
};
