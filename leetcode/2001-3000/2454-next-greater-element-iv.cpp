class Solution {
public:
    vector<int> secondGreaterElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> que = nums;
        sort(que.begin(), que.end());
        que.erase(unique(que.begin(), que.end()), que.end());
        int m = que.size();
        vector<pair<int, int> > bits(m + 1, {n, n});
        vector<int> ret(n);
        for(int i = n - 1; i >= 0; --i) {
            pair<int, int> cur = {n, n};
            int x = lower_bound(que.begin(), que.end(), nums[i]) - que.begin() + 1;
            for(int y = x + 1; y <= m; y += y & -y)
                for(int z: {bits[y].first, bits[y].second}) {
                    if(z < cur.first)
                        swap(z, cur.first);
                    if(z < cur.second)
                        swap(z, cur.second);
                }
            ret[i] = cur.second < n ? nums[cur.second] : -1;
            for(int y = x; y > 0; y -= y & -y) {
                int z = i;
                if(z < bits[y].first)
                    swap(z, bits[y].first);
                if(z < bits[y].second)
                    swap(z, bits[y].second);
            }
        }
        return ret;
    }
};
