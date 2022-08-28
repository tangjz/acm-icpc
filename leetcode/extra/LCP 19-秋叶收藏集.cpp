class Solution {
public:
    int minimumOperations(string leaves) {
        int n = leaves.size(), ans = INT_MAX, pre = INT_MAX, sum = 0;
        for(int i = 0; i < n; ++i) {
            sum += leaves[i] == 'y';
            if(i + 1 < n && pre < INT_MAX)
                ans = min(ans, pre + i - sum - sum);
            pre = min(pre, sum + sum - i);
        }
        return ans + sum;
    }
};
