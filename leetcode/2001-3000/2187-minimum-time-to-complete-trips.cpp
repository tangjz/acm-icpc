class Solution {
public:
    long long minimumTime(vector<int>& time, int totalTrips) {
        typedef long long LL;
        LL L = 1, R = (LL)time.front() * totalTrips;
        while(L < R) {
            LL M = (L + R) >> 1;
            LL cnt = 0;
            for(int x: time)
                cnt += M / x;
            if(cnt >= totalTrips) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        return L;
    }
};
