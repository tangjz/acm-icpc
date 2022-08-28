class Solution {
public:
    string addSpaces(string s, vector<int>& spaces) {
        string t = "";
        if(spaces.front() > 0)
            t = s.substr(0, spaces.front());
        int n = spaces.size();
        for(int i = 0; i < n; ++i) {
            int cur = spaces[i];
            int nxt = i + 1 < n ? spaces[i + 1] : (int)s.length();
            t += " " + s.substr(cur, nxt - cur);
        }
        return t;
    }
};
