class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> ctr(n + 1);
        for(auto &it: bookings) {
            ctr[it[0] - 1] += it[2];
            ctr[it[1]] -= it[2];
        }
        for(int i = 0; i < n; ++i)
            ctr[i + 1] += ctr[i];
        ctr.pop_back();
        return ctr;
    }
};
