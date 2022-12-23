class Solution {
public:
    vector<int> arrangeBookshelf(vector<int>& order, int limit) {
        unordered_map<int, int> cap, use;
        for(int x: order)
            ++cap[x];
        vector<int> ret;
        for(int x: order) {
            if(use[x] == limit) {
                --cap[x];
                continue;
            }
            for(int y; !ret.empty() && x < (y = ret.back()) && cap[y] > limit; --use[y], --cap[y], ret.pop_back());
            ++use[x];
            ret.push_back(x);
        }
        return ret;
    }
};
