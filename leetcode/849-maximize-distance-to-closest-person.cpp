class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        int n = seats.size(), las = -1, ans = 0;
        for(int i = 0; i < n; ++i) {
            if(!seats[i])
                continue;
            if(las == -1) {
                ans = max(ans, i);
            } else {
                ans = max(ans, (i - las) >> 1);
            }
            las = i;
        }
        ans = max(ans, n - 1 - las);
        return ans;
    }
};
