class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        constexpr int maxd = 26;
        int mx = 0, sm = 0, ct = 0;
        vector<int> ctr(maxd);
        for(char ch : tasks) {
            mx = max(mx, ++ctr[(int)(ch - 'A')]);
            ++sm;
        }
        for(int x : ctr)
            ct += x == mx;
        return max((mx - 1) * (n + 1) + ct, sm);
    }
};
