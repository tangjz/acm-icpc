class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& p, int k) {
        int ans = INT_MIN;
        deque<pair<int, int> > que;
        for(auto &it : p) {
            while(!que.empty() && it[0] - que.front().second > k)
                que.pop_front();
            if(!que.empty())
                ans = max(ans, it[1] + it[0] + que.front().first);
            pair<int, int> tmp = {it[1] - it[0], it[0]};
            while(!que.empty() && que.back() < tmp)
                que.pop_back();
            que.push_back(tmp);
        }
        deque<pair<int, int> >().swap(que);
        reverse(p.begin(), p.end());
        for(auto &it : p) {
            while(!que.empty() && que.front().second - it[0] > k)
                que.pop_front();
            if(!que.empty())
                ans = max(ans, it[1] - it[0] + que.front().first);
            pair<int, int> tmp = {it[1] + it[0], it[0]};
            while(!que.empty() && que.back() < tmp)
                que.pop_back();
            que.push_back(tmp);
        }
        return ans;
    }
};
