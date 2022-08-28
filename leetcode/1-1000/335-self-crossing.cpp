class Solution {
public:
    bool isSelfCrossing(vector<int>& distance) {
        int n = distance.size();
        for(int i = 3; i < n; ++i) {
            static int dt[7] = {};
            dt[0] = -distance[i];
            dt[1] = distance[i - 1];
            dt[2] = dt[0] + distance[i - 2];
            dt[3] = dt[1] - distance[i - 3];
            if(dt[0] <= dt[2] && dt[2] <= 0 && dt[3] <= 0 && 0 <= dt[1])
                return 1;
            if(i == 3)
                continue;
            dt[4] = dt[2] - distance[i - 4];
            if(max(dt[0], dt[4]) <= min(0, dt[2]) && dt[3] == 0)
                return 1;
            if(i == 4)
                continue;
            dt[5] = dt[3] + distance[i - 5];
            if(dt[0] <= dt[4] && dt[4] <= 0 && dt[3] <= 0 && 0 <= dt[5])
                return 1;
        }
        return 0;
    }
};
