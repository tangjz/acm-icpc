class Solution {
public:
    int smallestCommonElement(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        priority_queue<pair<int, pair<int, int> > > que;
        for(int i = 0; i < n; ++i)
            que.push({-mat[i][0], {i, 0}});
        while(!que.empty()) {
            int val = que.top().first, cnt = 0;
            while(!que.empty() && que.top().first == val) {
                ++cnt;
                pair<int, int> cur = que.top().second;
                que.pop();
                if((++cur.second) < m)
                    que.push({-mat[cur.first][cur.second], cur});
            }
            if(cnt == n)
                return -val;
        }
        return -1;
    }
};
