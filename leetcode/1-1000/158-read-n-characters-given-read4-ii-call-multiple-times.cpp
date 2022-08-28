/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 */

class Solution {
    int rem;
    char tmp[5];
public:
    Solution() {
        rem = 0;
    }

    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {
        int ret = rem;
        for(int i = 0; i < rem; ++i)
            buf[i] = tmp[i];
        while(ret < n) {
            int adt = read4(buf + ret);
            ret += adt;
            if(adt < 4)
                break;
        }
        if(ret > n) {
            rem = ret - n;
            ret = n;
            for(int i = 0; i < rem; ++i)
                tmp[i] = buf[ret + i];
            buf[ret] = '\0';
        } else {
            rem = 0;
        }
        return ret;
    }
};
