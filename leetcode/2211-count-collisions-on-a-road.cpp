class Solution {
public:
    int countCollisions(string dir) {
        int n = dir.size(), ans = n;
        for(int i = 0; i < n && dir[i] == 'L'; ++i, --ans);
        for(int i = n - 1; i >= 0 && dir[i] == 'R'; --i, --ans);
        for(int i = 0; i < n; ans -= dir[i++] == 'S');
        return ans;
    }
};
