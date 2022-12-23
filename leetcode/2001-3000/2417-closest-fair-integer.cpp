class Solution {
public:
    int closestFair(int n) {
        string buf = to_string(n - 1);
        int len = buf.size();
        if(!(len & 1)) {
            int best = -1;
            for(int i = 0, c = 0; i < len; ++i) {
                for(char ch = '9'; ch >= '8' && ch > buf[i]; --ch) {
                    int nc = c + (ch & 1 ? 1 : -1);
                    if(abs(nc) <= len - 1 - i) {
                        best = i;
                        break;
                    }
                }
                c += buf[i] & 1 ? 1 : -1;
            }
            if(best != -1) {
                int c = 0;
                for(int i = 0; i < best; ++i)
                    c += buf[i] & 1 ? 1 : -1;
                for(char ch = buf[best] + 1; ch <= '9'; ++ch) {
                    int nc = c + (ch & 1 ? 1 : -1);
                    if(abs(nc) <= len - 1 - best) {
                        int zero = (len - 1 - best + nc) / 2, one = zero - nc;
                        buf[best] = ch;
                        for(int j = 0; j < zero; ++j)
                            buf[best + 1 + j] = '0';
                        for(int j = 0; j < one; ++j)
                            buf[best + 1 + zero + j] = '1';
                        return stoi(buf);
                    }
                }
            }
        }
        len = (len / 2 + 1) * 2;
        buf.assign(len, '0');
        buf[0] = '1';
        for(int i = 1; i < len / 2; ++i)
            buf[len - i] = '1';
        return stoi(buf);
    }
};
