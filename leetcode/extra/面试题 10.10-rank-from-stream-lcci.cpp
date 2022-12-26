class StreamRank {
    static const int maxv = (int)5e4 + 9;
    static int st;
    static pair<int, int> bits[maxv];

public:
    StreamRank() {
        if(!(++st)) {
            memset(bits, 0, sizeof bits);
            st = 0;
        }
    }

    void track(int x) {
        for(++x; x < maxv; x += x & -x)
            if(bits[x].second != st) {
                bits[x] = {1, st};
            } else {
                ++bits[x].first;
            }
    }

    int getRankOfNumber(int x) {
        int ret = 0;
        for(++x; x > 0; x -= x & -x)
            if(bits[x].second == st)
                ret += bits[x].first;
        return ret;
    }
};

int StreamRank::st = 0;
pair<int, int> StreamRank::bits[maxv] = {};

/**
 * Your StreamRank object will be instantiated and called as such:
 * StreamRank* obj = new StreamRank();
 * obj->track(x);
 * int param_2 = obj->getRankOfNumber(x);
 */
