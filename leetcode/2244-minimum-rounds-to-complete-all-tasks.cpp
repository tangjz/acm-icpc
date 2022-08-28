class Solution {
public:
    int minimumRounds(vector<int>& tasks) {
        int n = tasks.size(), ans = 0;
        sort(tasks.begin(), tasks.end());
        for(int i = 0, j = 0; i < n; i = j) {
            for( ; j < n && tasks[i] == tasks[j]; ++j);
            int len = j - i;
            if(len == 1)
                return -1;
            ans += len / 3 + (len % 3 > 0);
        }
        return ans;
    }
};
