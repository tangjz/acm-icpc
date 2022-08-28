class Solution {
public:
    int catchMaximumAmountofPeople(vector<int>& team, int dist) {
        int n = team.size();
        queue<int> que;
        for(int i = 0; i < n; ++i)
            if(!team[i])
                que.push(i);
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            if(!team[i])
                continue;
            while(!que.empty() && que.front() < i - dist)
                que.pop();
            if(!que.empty() && que.front() <= i + dist) {
                ++ans;
                que.pop();
            }
        }
        return ans;
    }
};
