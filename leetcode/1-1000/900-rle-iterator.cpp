class RLEIterator {
    int rem;
    vector<int>::iterator head, tail;
public:
    RLEIterator(vector<int>& encoding) {
        rem = encoding.front();
        head = encoding.begin() + 1;
        tail = encoding.end();
    }

    int next(int n) {
        while(n > 0 && head != tail) {
            if(!rem) {
                if((++head) == tail)
                    break;
                rem = *(head++);
            }
            int tmp = min(n, rem);
            n -= tmp;
            rem -= tmp;
        }
        return head != tail ? *head : -1;
    }
};

/**
 * Your RLEIterator object will be instantiated and called as such:
 * RLEIterator* obj = new RLEIterator(encoding);
 * int param_1 = obj->next(n);
 */
