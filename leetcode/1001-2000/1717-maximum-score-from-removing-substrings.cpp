class Solution {
public:
    int maximumGain(string s, int x, int y) {
        string u = "ab", v = "ba";
        if(x < y) {
            swap(u, v);
            swap(x, y);
        }
        int ans = 0;
        string t = "";
        for(char ch : s) {
            if(ch == u.back() && !t.empty() && t.back() == u.front()) {
                t.pop_back();
                ans += x;
            } else {
                t.push_back(ch);
            }
        }
        s = t;
        t = "";
        for(char ch : s) {
            if(ch == v.back() && !t.empty() && t.back() == v.front()) {
                t.pop_back();
                ans += y;
            } else {
                t.push_back(ch);
            }
        }
        return ans;
    }
};
