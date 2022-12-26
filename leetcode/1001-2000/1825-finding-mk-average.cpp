class MKAverage {
    typedef long long LL;
    int tot, sz, pos;
    vector<int> seq;
    LL sumM;
    multiset<int> L, M, R;
public:
    MKAverage(int m, int k) {
        tot = m;
        sz = k;
        pos = 0;
        vector<int>(tot).swap(seq);
        sumM = 0;
    }

    void addElement(int num) {
        if(seq[pos] > 0) {
            assert(sumM > 0);
            int old = seq[pos];
            if(old <= *L.rbegin()) {
                // printf("del %d\n", *M.begin());
                L.erase(L.find(old));
                L.insert(*M.begin());
                sumM -= *M.begin();
                M.erase(M.begin());
            } else if(old >= *R.begin()) {
                // printf("del %d\n", *M.rbegin());
                R.erase(R.find(old));
                R.insert(*M.rbegin());
                sumM -= *M.rbegin();
                M.erase(--M.end());
            } else {
                // printf("del %d\n", old);
                sumM -= old;
                M.erase(M.find(old));
            }
            if(num <= *L.rbegin()) {
                // printf("add %d\n", *L.rbegin());
                sumM += *L.rbegin();
                M.insert(*L.rbegin());
                L.erase(--L.end());
                L.insert(num);
            } else if(num >= *R.begin()) {
                // printf("add %d\n", *R.begin());
                sumM += *R.begin();
                M.insert(*R.begin());
                R.erase(R.begin());
                R.insert(num);
            } else {
                // printf("add %d\n", num);
                sumM += num;
                M.insert(num);
            }
        }
        seq[pos] = num;
        pos = (pos + 1) % tot;
        if(!sumM && seq[pos] > 0) {
            L.clear();
            M.clear();
            R.clear();
            for(int i = 0; i < tot; ++i) {
                // printf("add %d\n", seq[i]);
                M.insert(seq[i]);
                sumM += seq[i];
            }
            for(int i = 0; i < sz; ++i) {
                // printf("del %d\n", *M.begin());
                L.insert(*M.begin());
                sumM -= *M.begin();
                M.erase(M.begin());
                // printf("del %d\n", *M.rbegin());
                R.insert(*M.rbegin());
                sumM -= *M.rbegin();
                M.erase(--M.end());
            }
        }
        // printf("sumM %lld pos %d seq[pos] %d\n", sumM, pos, seq[pos]);
    }

    int calculateMKAverage() {
        return seq[pos] > 0 ? sumM / (tot - sz - sz) : -1;
    }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */
