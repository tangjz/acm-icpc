class Solution {
public:
    int createSortedArray(vector<int>& seq) {
        const int mod = (int)1e9 + 7;
        vector<int> que = seq;
        sort(que.begin(), que.end());
        que.erase(unique(que.begin(), que.end()), que.end());
        int m = que.size(), ans = 0, pos = 0;
        vector<int> bits(m), ctr(m);
        for(int x: seq) {
            int y = lower_bound(que.begin(), que.end(), x) - que.begin() + 1;
            int lt = 0;
            for(int i = y - 1; i > 0; i -= i & -i)
                lt += bits[i - 1];
            int gt = pos - lt - ctr[y - 1];
            // printf("%d: %d %d: %d %d %d\n", pos, x, y, lt, ctr[y - 1], gt);
            (ans += min(lt, gt)) >= mod && (ans -= mod);
            ++pos;
            ++ctr[y - 1];
            for(int i = y; i <= m; i += i & -i)
                ++bits[i - 1];
        }
        return ans;
    }
};
