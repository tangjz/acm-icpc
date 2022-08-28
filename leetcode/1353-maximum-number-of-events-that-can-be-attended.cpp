class Solution {
public:
    int maxEvents(vector<vector<int>>& seg) {
        sort(seg.begin(), seg.end());
        priority_queue<int> que;
        auto it = seg.begin();
        int cur = 0, ctr = 0;
        while(it != seg.end() || !que.empty()) {
            if(que.empty() && (*it)[0] > cur)
                cur = (*it)[0];
            while(it != seg.end() && (*it)[0] <= cur)
                que.push(-(*it++)[1]);
            while(!que.empty() && -que.top() < cur)
                que.pop();
            if(!que.empty()) {
                ++cur;
                ++ctr;
                que.pop();
            }
        }
        return ctr;
    }
};
