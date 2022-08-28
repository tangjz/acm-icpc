class Robot {
    int len, idx;
    vector<pair<vector<int>, string> > cand;
public:
    Robot(int w, int h) {
        vector<pair<vector<int>, string> >().swap(cand);
        for(int i = 0; i < w; ++i) {
            cand.push_back({{i, 0}, "East"});
        }
        for(int i = 1; i < h; ++i) {
            cand.push_back({{w - 1, i}, "North"});
        }
        for(int i = w - 2; i >= 0; --i) {
            cand.push_back({{i, h - 1}, "West"});
        }
        for(int i = h - 2; i > 0; --i) {
            cand.push_back({{0, i}, "South"});
        }
        idx = 0;
        len = cand.size();
    }
    
    void move(int num) {
        if(idx + num >= len) {
            cand.front().second = "South";
        }
        idx = (idx + num) % len;
    }
    
    vector<int> getPos() {
        return cand[idx].first;
    }
    
    string getDir() {
        return cand[idx].second;
    }
};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->move(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */
