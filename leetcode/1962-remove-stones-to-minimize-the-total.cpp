class Solution {
public:
    int minStoneSum(vector<int>& piles, int k) {
        int ans = 0;
        priority_queue<pair<int, int> > que;
        for(int x: piles) {
            ans += x;
            que.push({x >> 1, x});
        }
        while(k--) {
            int x = que.top().second;
            que.pop();
            ans -= x;
            x -= x >> 1;
            ans += x;
            que.push({x >> 1, x});
        }
        return ans;
    }
};
