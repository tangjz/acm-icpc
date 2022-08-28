class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int sum = 0, cntL = 0;
        for(char ch : s) {
            sum += ch == '(' ? 1 : (ch == ')' ? -1 : 0);
            cntL = max(cntL, -sum);
        }
        int cntR = sum + cntL;
        if(cntL > 0)
            for(char &ch : s)
                if(ch == ')') {
                    ch = '\0';
                    if(!(--cntL))
                        break;
                }
        if(cntR > 0) {
            reverse(s.begin(), s.end());
            for(char &ch : s)
                if(ch == '(') {
                    ch = '\0';
                    if(!(--cntR))
                        break;
                }
            reverse(s.begin(), s.end());
        }
        string t = "";
        for(char ch : s)
            if(ch != '\0')
                t.push_back(ch);
        return t;
    }
};
