class Solution {
public:
    bool confusingNumber(int n) {
        unordered_map<char, char> nxt = {
            {'0', '0'},
            {'1', '1'},
            {'6', '9'},
            {'8', '8'},
            {'9', '6'},
        };
        string u = to_string(n), v = "";
        for(char ch: u) {
            if(!nxt.count(ch))
                return 0;
            v.push_back(nxt[ch]);
        }
        reverse(u.begin(), u.end());
        return u != v;
    }
};
