class Solution {
public:
    int minimumTime(vector<int>& jobs, vector<int>& workers) {
        int n = jobs.size(), ans = 0;
        sort(jobs.begin(), jobs.end());
        sort(workers.begin(), workers.end());
        for(int i = 0; i < n; ++i)
            ans = max(ans, (jobs[i] - 1) / workers[i] + 1);
        return ans;
    }
};
