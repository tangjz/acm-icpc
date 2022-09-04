class Solution {
public:
    bool rotateString(string s, string goal) {
        if(s.size() != goal.size())
            return 0;
        s += s;
        return s.find(goal) != string::npos;
    }
};
