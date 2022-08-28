/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 */

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {
        int ret = 0;
        while(ret < n) {
            int adt = read4(buf + ret);
            ret += adt;
            if(adt < 4)
                break;
        }
        if(ret > n) {
            ret = n;
            buf[ret] = '\0';
        }
        return ret;
    }
};
