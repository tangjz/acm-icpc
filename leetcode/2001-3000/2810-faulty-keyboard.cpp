class Solution {
public:
    string finalString(string s) {
        deque<char> que;
        bool rev = 0;
        for(char ch: s) {
            if(ch == 'i') {
                rev = !rev;
                continue;
            }
            if(rev) {
                que.push_front(ch);
            } else {
                que.push_back(ch);
            }
        }
        s = "";
        while(!que.empty()) {
            s.push_back(que.front());
            que.pop_front();
        }
        if(rev)
            reverse(s.begin(), s.end());
        return s;
    }
};
