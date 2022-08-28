class Solution {
public:
    int countLargestGroup(int n) {
        const int maxd = 37;
        int upp = 0;
        vector<int> ctr(maxd, 0);
        for(int i = 1; i <= n; ++i) {
            int sum = 0;
            for(int tmp = i; tmp > 0; tmp /= 10)
                sum += tmp % 10;
            upp = max(upp, ++ctr[sum]);
        }
        int cnt = 0;
        for(int x : ctr)
            cnt += x == upp;
        return cnt;
    }
};
