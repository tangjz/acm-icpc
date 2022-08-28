class Solution {
public:
    int numSteps(string s) {
        int ans = 0;
        while(s != "1") {
            while(s.back() == '0') {
                ++ans;
                s.pop_back();
            }
            if(s == "1")
                break;
            ++ans;
            while(!s.empty() && s.back() == '1') {
                ++ans;
                s.pop_back();
            }
            if(s.empty())
                s += '0';
            s.back() = '1';
        }
        return ans;
    }
};
