class Solution {
public:
    string strWithout3a3b(int a, int b) {
        char u = 'a', v = 'b';
        if(a < b) {
            swap(a, b);
            swap(u, v);
        }
        string ret = "";
        while(a > 0) {
            int t = min(max(a - b, 1), 2);
            a -= t;
            while(t--)
                ret.push_back(u);
            swap(a, b);
            swap(u, v);
        }
        return ret;
    }
};
