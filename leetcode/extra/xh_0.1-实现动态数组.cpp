class LCArray {
    static const int lowCap = 15;
    int cap, len, *arr;

    void rescale(int newCap) {
        int *newArr = new int[newCap];
        memcpy(newArr, arr, len * sizeof(int));
        delete[] arr;
        arr = newArr;
        cap = newCap;
    }
public:
    LCArray() {
        cap = lowCap;
        len = 0;
        arr = new int[cap];
    }

    ~LCArray() {
        delete[] arr;
    }

    void push_back(int n) {
        if(len == cap)
            rescale(cap + max(cap >> 1, 1));
        arr[len++] = n;
    }

    void pop_back() {
        if(len > 0)
            --len;
        if(len > lowCap && len + len < cap)
            rescale(cap >> 1);
    }

    int size() {
        return len;
    }

    int index(int idx) {
        return idx < len ? arr[idx] : -1;
    }
};

/**
 * Your LCArray object will be instantiated and called as such:
 * LCArray* obj = new LCArray();
 * obj->push_back(n);
 * obj->pop_back();
 * int param_3 = obj->size();
 * int param_4 = obj->index(idx);
 */
