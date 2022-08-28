class Solution {
public:
    vector<int> executeInstructions(int n, vector<int>& startPos, string s) {
        unordered_map<char, pair<int, int> > dir = {
            {'L', {0, -1}},
            {'R', {0, 1}},
            {'U', {-1, 0}},
            {'D', {1, 0}},
        };
        int m = s.size();
        vector<int> ans(m);
        for(int i = 0; i < m; ++i) {
            int x = startPos[0], y = startPos[1];
            for(int j = i; j < m; ++j) {
                int dx, dy;
                tie(dx, dy) = dir[s[j]];
                x += dx;
                y += dy;
                if(0 <= x && x < n && 0 <= y && y < n) {
                    ++ans[i];
                } else {
                    break;
                }
            }
        }
        return ans;
    }
};
