class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        int n = (int)nums.size();
        if(n % k > 0)
            return 0;
        unordered_map<int, int> ctr;
        for(int x : nums)
            ++ctr[x];
        auto get = [&](int x) {
            auto it = ctr.find(x);
            return it == ctr.end() ? 0 : it -> second;
        };
        vector<int> pos;
        for(int x : nums)
            if(!get(x - 1))
                pos.push_back(x);
        for(int x : pos) {
            if(!get(x))
                continue;
            int cur = x, nxt;
            while(cur != -1) {
                nxt = -1;
                int las = get(cur - 1);
                for(int i = 0; i < k; ++i) {
                    int rem = get(cur + i);
                    if(!rem)
                        return 0;
                    --ctr[cur + i];
                    --rem;
                    if(nxt == -1 && !las && rem)
                        nxt = cur + i;
                    las = rem;
                }
                if(nxt == -1 && !las && get(cur + k))
                    nxt = cur + k;
                cur = nxt;
            }
        }
        return 1;
    }
};
