class LUPrefix {
    int mex;
    vector<bool> vis;
public:
    LUPrefix(int n) {
        mex = 0;
        vis.assign(n + 1, false);
    }
    
    void upload(int video) {
        vis[--video] = 1;
        for( ; vis[mex]; ++mex);
    }
    
    int longest() {
        return mex;
    }
};

/**
 * Your LUPrefix object will be instantiated and called as such:
 * LUPrefix* obj = new LUPrefix(n);
 * obj->upload(video);
 * int param_2 = obj->longest();
 */
