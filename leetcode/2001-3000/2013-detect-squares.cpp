class DetectSquares {
    unordered_map<int, unordered_map<int, int> > hs;
    
    int get(int x, int y) {
        auto it = hs.find(x);
        if(it == hs.end())
            return 0;
        auto jt = (it -> second).find(y);
        if(jt == (it -> second).end())
            return 0;
        return jt -> second;
    }
public:
    DetectSquares() {
        hs.clear();
    }
    
    void add(vector<int> point) {
        int x = point[0], y = point[1];
        hs[x][y] += 1;
    }
    
    int count(vector<int> point) {
        int x = point[0], y = point[1];
        int ans = 0;
        for(auto &it: hs) {
            if(x == it.first)
                continue;
            int dif = abs(x - it.first);
            for(int v: {y - dif, y + dif}) {
                ans += get(it.first, v) * get(it.first, y) * get(x, v);
            }
        }
        return ans;
    }
};

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares* obj = new DetectSquares();
 * obj->add(point);
 * int param_2 = obj->count(point);
 */
