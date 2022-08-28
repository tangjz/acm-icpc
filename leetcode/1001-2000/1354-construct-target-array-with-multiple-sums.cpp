class Solution {
public:
    bool isPossible(vector<int>& target) {
        typedef long long LL;
        LL sum = 0;
        int pos = 0;
        priority_queue<pair<int, int> > que;
        for(int x : target) {
            sum += x;
            que.push({x, pos++});
        }
        while(!que.empty()) {
            int val;
            tie(val, pos) = que.top();
            que.pop();
            if(val == 1)
                continue;
            int nxt = max(que.empty() ? 1 : que.top().first, 2);
            LL rem = sum - val;
            if(!rem)
                return 0;
            LL stp = (val - nxt) / rem + 1;
            if(val - stp * rem < 1)
                return 0;
            target[pos] = (val -= stp * rem);
            sum -= stp * rem;
            que.push({val, pos});
        }
        return 1;
    }
};
