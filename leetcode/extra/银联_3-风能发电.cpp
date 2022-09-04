class Solution {
public:
    int StoredEnergy(int lim, const vector<int>& seq, const vector<vector<int>>& que)
    {
        int cnt = 0, low = 0, upp = 0, n = seq.size(), m = que.size();
        for(int i = 0, j = 0; i < n; ++i) {
            if(j < m && que[j][0] == i) {
                low = que[j][1];
                upp = que[j][2];
                ++j;
            }
            int val = seq[i];
            if(val < low) {
                int adt = min(low - val, cnt);
                val += adt;
                cnt -= adt;
            } else if(val > upp) {
                int adt = min(val - upp, lim - cnt);
                val -= adt;
                cnt += adt;
            }
        }
        return cnt;
    }
};
