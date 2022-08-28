class Solution {
public:
    int busyStudent(vector<int>& startTime, vector<int>& endTime, int queryTime) {
        int n = (int)startTime.size(), ans = 0;
        for(int i = 0; i < n; ++i)
            ans += startTime[i] <= queryTime && queryTime <= endTime[i];
        return ans;
    }
};
