class Solution {
public:
    vector<string> ipToCIDR(string ip, int n) {
        typedef unsigned int UL;
        auto ip_to_ul = [&](string const &buf) {
            int n = buf.size();
            UL ret = 0, adt;
            for(int i = 0, j; i < n; ++i) {
                adt = 0;
                for(j = i; i < n && isdigit(buf[i]); ++i)
                    adt = adt * 10 + (buf[i] - '0');
                ret = ret << 8 | adt;
            }
            return ret;
        };
        auto ul_to_ip = [&](UL val) {
            string ret = "";
            for(int ofs = 24; ofs >= 0; ofs -= 8) {
                ret += to_string((val >> ofs) & 255);
                if(ofs > 0)
                    ret.push_back('.');
            }
            return ret;
        };
        UL cur = ip_to_ul(ip);
        vector<string> ret;
        while(n > 0) {
            int mx = 0;
            for( ; !((cur >> mx) & 1) && (2 << mx) <= n; ++mx);
            ret.push_back(ul_to_ip(cur) + "/" + to_string(32 - mx));
            n -= 1 << mx;
            cur += 1 << mx;
        }
        return ret;
    }
};
