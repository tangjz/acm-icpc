class Solution {
public:
    bool buddyStrings(string s, string goal) {
        int n = (int)s.length();
        if(n < 2 || n != (int)goal.length())
            return false;
        const int maxd = 26;
        int cnt = 0, pos[3];
        int upp = 0, ctr[maxd] = {};
        for(int i = 0; cnt < 3 && i < n; ++i) {
            if(s[i] != goal[i])
                pos[cnt++] = i;
            upp = max(upp, ++ctr[int(s[i] - 'a')]);
        }
        if(!cnt)
            return upp >= 2;
        if(cnt == 2)
            return s[pos[0]] == goal[pos[1]] && s[pos[1]] == goal[pos[0]];
        return false;
    }
};
