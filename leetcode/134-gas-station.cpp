class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = (int)gas.size(), sum = 0, cur = 0, sta = 0;
        for(int i = 0; i < n; ++i) {
            int diff = gas[i] - cost[i];
            sum += diff;
            cur += diff;
            if(cur < 0) {
                cur = 0;
                sta = i + 1;
            }
        }
        return sum < 0 || sta == n ? -1 : sta;
    }
};
