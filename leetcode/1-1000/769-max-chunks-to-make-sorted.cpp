class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int ans = 0, n = arr.size();
        vector<int> res = arr;
        unordered_map<int, int> ctr;
        sort(res.begin(), res.end());
        auto upd = [&](int x, int v) {
            if(!(ctr[x] += v))
                ctr.erase(x);
        };
        for(int i = 0; i < n; ++i) {
            upd(arr[i], 1);
            upd(res[i], -1);
            ans += ctr.empty();
        }
        return ans;
    }
};
