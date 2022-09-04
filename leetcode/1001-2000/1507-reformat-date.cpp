class Solution {
public:
    string reformatDate(string date) {
        static const char *months[] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        int yy, mm = 0, dd;
        static char buf[11];
        sscanf(date.c_str(), "%d%*s %s %d", &dd, buf, &yy);
        for(int i = 1; i <= 12; ++i)
            if(!strcmp(buf, months[i])) {
                mm = i;
                break;
            }
        sprintf(buf, "%04d-%02d-%02d", yy, mm, dd);
        return buf;
    }
};
