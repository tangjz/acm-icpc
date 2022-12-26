class Allocator {
    vector<int> idx;
public:
    Allocator(int n) {
        idx.resize(n);
    }

    int allocate(int size, int mID) {
        int n = idx.size();
        for(int i = 0; i < n; ++i) {
            if(idx[i] || (i > 0 && !idx[i - 1]))
                continue;
            int j = i;
            for( ; j < n && j - i < size && !idx[j]; ++j);
            if(j - i == size) {
                for(j = 0; j < size; ++j)
                    idx[i + j] = mID;
                return i;
            }
        }
        return -1;
    }

    int free(int mID) {
        int n = idx.size(), ctr = 0;
        for(int i = 0; i < n; ++i)
            if(idx[i] == mID) {
                ++ctr;
                idx[i] = 0;
            }
        return ctr;
    }
};

/**
 * Your Allocator object will be instantiated and called as such:
 * Allocator* obj = new Allocator(n);
 * int param_1 = obj->allocate(size,mID);
 * int param_2 = obj->free(mID);
 */
