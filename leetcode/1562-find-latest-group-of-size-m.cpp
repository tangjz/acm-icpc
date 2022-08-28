class Solution {
public:
    int findLatestStep(vector<int>& arr, int m) {
        int n = (int)arr.size();
        vector<int> pL(n, -1), pR(n, -1);
        int ans = -1, cnt = 0;
        for(int i = 0; i < n; ++i) {
            int x = arr[i] - 1;
            int lft = x > 0 && pL[x - 1] != -1 ? pL[x - 1] : x;
            int rht = x + 1 < n && pR[x + 1] != -1 ? pR[x + 1] : x;
            if(lft < x)
                cnt -= x - lft == m;
            if(x < rht)
                cnt -= rht - x == m;
            pR[lft] = rht;
            pL[rht] = lft;
            cnt += rht - lft + 1 == m;
            if(cnt > 0)
                ans = i + 1;
        }
        return ans;
    }
};
