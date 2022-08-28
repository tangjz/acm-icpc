class ZigzagIterator {
    int turn, pA, pB;
    vector<int> A, B;
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        A = move(v1);
        B = move(v2);
        pA = pB = 0;
        turn = pA == A.size();
    }

    int next() {
        int x = turn ? B[pB++] : A[pA++];
        if(turn ? pA < A.size() : pB < B.size())
            turn = !turn;
        return x;
    }

    bool hasNext() {
        return pA < A.size() || pB < B.size();
    }
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */
