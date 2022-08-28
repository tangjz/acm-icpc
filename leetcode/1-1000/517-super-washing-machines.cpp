class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        int n = machines.size(), sum = 0;
        for(int x: machines)
            sum += x;
        if(sum % n > 0)
            return -1;
        sum /= n;
        int ans = 0, cur = 0, pre = 0;
        for(int x: machines) {
            pre = cur;
            cur += x - sum;
            ans = max(ans, abs(cur));
            ans = max(ans, cur - pre);
        }
        return ans;
    }
};
