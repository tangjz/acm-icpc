class Solution {
public:
    bool isFascinating(int n) {
        string buf = to_string(n) + to_string(n + n) + to_string(n + n + n);
        sort(buf.begin(), buf.end());
        return buf.size() == 9 && buf[0] == '1' && unique(buf.begin(), buf.end()) == buf.end();
    }
};
