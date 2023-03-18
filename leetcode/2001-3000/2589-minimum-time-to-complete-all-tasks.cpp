class Solution {
public:
    int findMinimumTime(vector<vector<int>>& tasks) {
        vector<int> seq;
        for(auto &it: tasks) {
            seq.push_back(it[0]);
            seq.push_back(it[1] + 1);
        }
        sort(seq.begin(), seq.end());
        seq.erase(unique(seq.begin(), seq.end()), seq.end());
        int ans = 0;
        while(seq.size() > 1) {
            int pR = seq.back();
            seq.pop_back();
            int pL = seq.back(), low = 0;
            // printf("p [%d, %d)\n", pL, pR);
            for(auto &it: tasks) {
                int qL = it[0], qR = it[1] + 1, qW = it[2];
                if(!qW || qR < pR)
                    continue;
                // printf("q [%d, %d) %d\n", qL, qR, qW);
                assert(qL <= pL && pR <= qR);
                low = max(low, qW - (pL - qL));
            }
            if(!low)
                continue;
            // printf("low %d\n", low);
            assert(low <= pR - pL);
            ans += low;
            for(auto &it: tasks) {
                int qL = it[0], qR = it[1] + 1, qW = it[2];
                if(!qW || qR < pR)
                    continue;
                it[2] = max(qW - low, 0);
                qW = it[2];
                // printf("newq [%d, %d) %d\n", qL, qR, qW);
            }
        }
        return ans;
    }
};
