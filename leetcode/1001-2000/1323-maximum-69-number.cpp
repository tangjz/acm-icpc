class Solution {
public:
    int maximum69Number (int num) {
        string buf = to_string(num);
        int n = (int)buf.size();
        for(int i = 0; i < n; ++i)
            if(buf[i] == '6') {
                buf[i] = '9';
                break;
            }
        return stoi(buf);
    }
};
