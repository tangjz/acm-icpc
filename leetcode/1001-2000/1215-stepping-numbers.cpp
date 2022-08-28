class Solution {
public:
    vector<int> countSteppingNumbers(int low, int high) {
        vector<int> f, h = {0};
        for(int i = 1; i < 10; ++i)
            f.push_back(i);
        h.insert(h.end(), f.begin(), f.end());
        int lim = high / 10;
        for(int pw = 10; pw <= high; pw = pw * 10) {
            vector<int> g;
            for(int x: f) {
                if(x > lim)
                    continue;
                int d = x % 10;
                if(d > 0)
                    g.push_back(x * 10 + d - 1);
                if(d + 1 < 10)
                    g.push_back(x * 10 + d + 1);
            }
            f = move(g);
            h.insert(h.end(), f.begin(), f.end());
            if(pw > high / 10)
                break;
        }
        vector<int> g;
        for(int x: h)
            if(x >= low && x <= high)
                g.push_back(x);
        return g;
    }
};
