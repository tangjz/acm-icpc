class SmallestInfiniteSet {
    int mex;
    unordered_set<int> rem;
public:
    SmallestInfiniteSet() {
        mex = 1;
    }
    
    int popSmallest() {
        int ret = mex;
        rem.insert(mex);
        for(++mex; rem.count(mex); ++mex);
        return ret;
    }
    
    void addBack(int num) {
        if(rem.count(num)) {
            rem.erase(num);
            mex = min(mex, num);
        }
    }
};

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */
