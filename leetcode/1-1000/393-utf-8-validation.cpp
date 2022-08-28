class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int n = data.size();
        for(int i = 0; i < n; ) {
            int c = __builtin_clz(~((unsigned)data[i] << 24));
            if(!c) {
                c = 1;
            } else if(c == 1 || c > 4 || i + c > n) {
                return 0;
            }
            for(int j = 1; j < c; ++j)
                if((data[i + j] & 192) != 128)
                    return 0;
            i += c;
        }
        return 1;
    }
};
