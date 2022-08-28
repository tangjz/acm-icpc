class Solution {
public:
    int distanceBetweenBusStops(vector<int>& d, int s, int t) {
        int n = d.size(), ctr[2] = {};
        if(s > t)
            swap(s, t);
        for(int i = 0; i < n; ++i) {
            ctr[s <= i && i < t] += d[i];
        }
        return min(ctr[0], ctr[1]);
    }
};
