/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/

class Solution {
    Node *dfs(int sz, int xL, int yL, vector<vector<int> > &grid) {
        Node *rt = new Node(grid[xL][yL] == 1, true);
        if(sz == 1)
            return rt;
        int half = sz / 2, pos = 0;
        vector<Node **> sub = {&(rt -> topLeft), &(rt -> topRight), &(rt -> bottomLeft), &(rt -> bottomRight)};
        for(Node **tp: sub) {
            *tp = dfs(half, xL + (pos & 2 ? half : 0), yL + (pos & 1 ? half : 0), grid);
            if(!((*tp) -> isLeaf && (*tp) -> val == rt -> val))
                rt -> isLeaf = 0;
            ++pos;
        }
        if(rt -> isLeaf)
            for(Node **tp: sub)
                *tp = nullptr;
        return rt;
    }
public:
    Node* construct(vector<vector<int>>& grid) {
        int n = grid.size();
        return dfs(n, 0, 0, grid);
    }
};
