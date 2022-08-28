class Solution {
public:
    int maxSizeSlices(vector<int>& a) {
        int n = (int)a.size();
        vector<int> pL, pR;
        priority_queue<pair<int, int> > Q;
        for(int i = 0; i < n; ++i) {
            pL.push_back((i + n - 1) % n);
            pR.push_back((i + 1) % n);
            Q.push({a[i], i});
        }
        int ans = 0;
        for(int i = 0, j = 0; i < n && j < n / 3; ++i) {
            int u, cost;
            tie(cost, u) = Q.top();
            Q.pop();
            if(pL[pR[u]] != u)
                continue;
            ++j;
            ans += cost;
            int L = pL[u], R = pR[u];
            a[u] = a[L] + a[R] - a[u];
            pL[u] = pL[L];
            pR[u] = pR[R];
            pR[pL[u]] = pL[pR[u]] = u;
            Q.push({a[u], u});
        }
        return ans;
    }
};
