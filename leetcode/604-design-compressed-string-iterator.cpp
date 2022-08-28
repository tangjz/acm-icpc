class StringIterator {
    int ctr;
    char ch;
    string::iterator head, tail;
    string buf;
    void fetch() {
        if(head == tail) {
            ch = ' ';
            ctr = INT_MAX;
            return;
        }
        ch = *(head++);
        for(ctr = 0; head != tail && *head >= '0' && *head <= '9'; ++head)
            ctr = ctr * 10 + (*head - '0');
    }
public:
    StringIterator(string compressedString) {
        buf = move(compressedString);
        head = buf.begin();
        tail = buf.end();
        fetch();
    }
    
    char next() {
        char ret = ch;
        if(!(--ctr))
            fetch();
        return ret;
    }
    
    bool hasNext() {
        return (ch != ' ' && ctr > 0) || head != tail;
    }
};

/**
 * Your StringIterator object will be instantiated and called as such:
 * StringIterator* obj = new StringIterator(compressedString);
 * char param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
