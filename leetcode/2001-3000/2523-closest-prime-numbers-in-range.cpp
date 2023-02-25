class Solution {
public:
    vector<int> closestPrimes(int L, int R) {
        vector<int> d(R + 1), pr;
        for(int i = 2; i <= R; ++i) {
            if(!d[i]) {
                pr.push_back(i);
                d[i] = i;
            }
            for(int p: pr) {
                int j = i * p;
                if(j > R)
                    break;
                d[j] = p;
                if(d[i] == p)
                    break;
            }
        }
        int dis = INT_MAX, las = pr.empty() ? -1 : pr.back();
        pair<int, int> ans = {-1, -1};
        if(las != -1)
           pr.pop_back();
        while(!pr.empty() && pr.back() >= L) {
            int cur = pr.back(), dt = las - cur;
            pr.pop_back();
            if(dt <= dis) {
                dis = dt;
                ans = {cur, las};
            }
            las = cur;
        }
        return {ans.first, ans.second};
    }
};
