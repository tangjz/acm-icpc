class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        vector<int> que;
        for(int x: nums) {
            while(que.size() >= 2 && que.back() >= x && que[que.size() - 2] <= que.back()) {
                x -= que.back();
                que.pop_back();
                x += que.back();
                que.pop_back();
            }
            que.push_back(x);
        }
        auto it = min_element(que.begin(), que.end());
        reverse(que.begin(), it);
        inplace_merge(que.begin(), it, que.end());
        int ans = 0;
        while(!que.empty()) {
            ans += que.back();
            que.pop_back();
            if(que.empty())
                continue;
            ans -= que.back();
            que.pop_back();
        }
        return ans >= 0;
    }
};
